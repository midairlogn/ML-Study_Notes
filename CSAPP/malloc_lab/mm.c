/*
 * mm-implicit.c
 * 
 * code is based on CSAPP 3e textbook section 9.9
 */

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "memlib.h"
#include "mm.h"

/* do not change the following! */
#ifdef DRIVER
/* create aliases for driver tests */
#define malloc mm_malloc
#define free mm_free
#define realloc mm_realloc
#define calloc mm_calloc
#endif /* def DRIVER */

/* Basic constants and macros */
#define WSIZE 4             /* Word and header/footer size (bytes) */
#define DSIZE 8             /* Double word size (bytes) */
#define CHUNKSIZE (1 << 12) /* Extend heap by this amount (bytes) */
#define MIN_BLOCK 16
#define NUM_CLASSES 14
#define SEARCH_LIMIT 6

#define MAX(x, y) ((x) > (y) ? (x) : (y))

/* Pack a size and allocated bit into a word */
#define PACK(size, prev_alloc, alloc) ((unsigned int)((size) | ((prev_alloc) << 1)) | (alloc))

/* Read and write a word at address p */
#define GET(p) (*(unsigned int *)(p))
#define PUT(p, val) (*(unsigned int *)(p) = (unsigned int)(val))

/* Read the size and allocated fields from address p */
#define GET_SIZE(p) ((size_t)GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)
#define GET_PREV_ALLOC(p) ((GET(p) & 0x2) >> 1)

/* Given block ptr bp, compute address of its header and footer */
#define HDRP(bp) ((char *)(bp)  - WSIZE)
#define FTRP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

/* Given block ptr bp, compute address of next and previous blocks */
#define NEXT_BLKP(bp) ((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE)))
#define PREV_BLKP(bp) ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE)))

static void *extend_heap(size_t words);
static void *coalesce(void *bp);
static void *find_fit(size_t asize);
static void place(void *bp, size_t asize);

static char * heap_listp;
static char * heap_base;
static unsigned int head0;
static unsigned int head1;
static unsigned int head2;
static unsigned int head3;
static unsigned int head4;
static unsigned int head5;
static unsigned int head6;
static unsigned int head7;
static unsigned int head8;
static unsigned int head9;
static unsigned int head10;
static unsigned int head11;
static unsigned int head12;
static unsigned int head13;

static int size_class(size_t size);
static void insert_free(void * bp);
static void remove_free(void * bp);
static void set_next_prev_alloc(void * bp, int prev_alloc);

static inline unsigned int * class_head(int k) {
    switch (k) {
    case 0: return & head0;
    case 1: return & head1;
    case 2: return & head2;
    case 3: return & head3;
    case 4: return & head4;
    case 5: return & head5;
    case 6: return & head6;
    case 7: return & head7;
    case 8: return & head8;
    case 9: return & head9;
    case 10: return & head10;
    case 11: return & head11;
    case 12: return & head12;
    default: return & head13;
    }
}

#define PRED_PTR(bp) ((unsigned int *)(bp))
#define SUCC_PTR(bp) ((unsigned int *)((char *)(bp) + WSIZE))
#define GET_PRED(bp) (off_to_ptr(*PRED_PTR(bp)))
#define GET_SUCC(bp) (off_to_ptr(*SUCC_PTR(bp)))
#define SET_PRED(bp, p) (*PRED_PTR(bp) = ptr_to_off(p))
#define SET_SUCC(bp, p) (*SUCC_PTR(bp) = ptr_to_off(p))

static void * off_to_ptr(unsigned int offset) {
    if(!offset) {
        return NULL;
    }
    return (void *)(heap_base + offset);
}

static unsigned int ptr_to_off(void * p) {
    if(!p) {
        return 0;
    }
    return (unsigned int)((char *)p - heap_base);
}

static int size_class(size_t size) {
    if (size <= 16) {
        return 0;
    }
    if (size <= 24) {
        return 1;
    }
    if (size <= 32) {
        return 2;
    }
    if (size <= 64) {
        return 3;
    }
    if (size <= 128) {
        return 4;
    }
    if (size <= 256) {
        return 5;
    }
    if (size <= 512) {
        return 6;
    }
    if (size <= 1024) {
        return 7;
    }
    if (size <= 2048) {
        return 8;
    }
    if (size <= 4096) {
        return 9;
    }
    if (size <= 8192) {
        return 10;
    }
    if (size <= 16384) {
        return 11;
    }
    if (size <= 32768) {
        return 12;
    }
    return 13;
}

static void insert_free(void * bp) {
    int k = size_class(GET_SIZE(HDRP(bp)));
    void * head = off_to_ptr(* class_head(k));
    SET_PRED(bp, NULL);
    SET_SUCC(bp, head);
    if(head) {
        SET_PRED(head, bp);
    }
    * class_head(k) = ptr_to_off(bp);
}

static void remove_free(void * bp) {
    int k = size_class(GET_SIZE(HDRP(bp)));
    void * pred = GET_PRED(bp);
    void * succ = GET_SUCC(bp);
    if(pred) {
        SET_SUCC(pred, succ);
    }
    else {
        * class_head(k) = ptr_to_off(succ);
    }
    if (succ) {
        SET_PRED(succ, pred);
    }
}

static void set_next_prev_alloc(void * bp, int prev_alloc) {
    void * next = NEXT_BLKP(bp);
    unsigned int hdr = GET(HDRP(next));
    if (prev_alloc) {
        hdr |= 0x2;
    }
    else {
        hdr &= ~0x2u;
    }
    PUT(HDRP(next), hdr);
    if (GET_SIZE(HDRP(next)) > 0 && !GET_ALLOC(HDRP(next))) {
        PUT(FTRP(next), hdr);
    }
}

/*
 * mm_init
 */
int mm_init(void) {
    size_t info_bytes = WSIZE + DSIZE + WSIZE;
    if((heap_base = mem_sbrk(info_bytes)) == (void * )-1) {
        return -1;
    }
    for (int i = 0; i < NUM_CLASSES; ++ i) {
        PUT(class_head(i), 0);
    }
    char * p = heap_base;
    PUT(p, 0);
    PUT(p + WSIZE, PACK(DSIZE, 1, 1));
    PUT(p + WSIZE + WSIZE, PACK(DSIZE, 1, 1));
    PUT(p + 3 * WSIZE, PACK(0, 1, 1));
    heap_listp = p + DSIZE;
    return 0;
}

static size_t adjust_size(size_t size) {
    size_t asize = size + WSIZE;
    asize = (asize + (DSIZE - 1)) & ~((size_t) (DSIZE - 1));
    if (asize < MIN_BLOCK) {
        asize = MIN_BLOCK;
    }
    return asize;
}

/*
 * malloc
 */
void *malloc(size_t size) {
    if (!size) {
        return NULL;
    }
    if (!heap_listp) {
        if (mm_init() < 0) {
            return NULL;
        }
    }
    size_t asize = adjust_size(size);
    void * bp = find_fit(asize);
    if (!bp) {
        size_t extend = asize;
        if (!(bp = extend_heap(extend / WSIZE))) {
            return NULL;
        }
    }
    place(bp, asize);
    return bp;
}

/*
 * free
 */
void free(void * ptr) {
    if(!ptr) {
        return;
    }
    if(!heap_listp) {
        return;
    }
    size_t size = GET_SIZE(HDRP(ptr));
    int prev_alloc = GET_PREV_ALLOC(HDRP(ptr));
    PUT(HDRP(ptr), PACK(size, prev_alloc, 0));
    PUT(FTRP(ptr), PACK(size, prev_alloc, 0));
    set_next_prev_alloc(ptr, 0);
    coalesce(ptr);
}

/*
 * realloc
 */
void * realloc(void * oldptr, size_t size) {
    if (!size) {
        free(oldptr);
        return NULL;
    }
    if (!oldptr) {
        return malloc(size);
    }
    size_t oldsize = GET_SIZE(HDRP(oldptr));
    size_t asize = adjust_size(size);
    int prev_alloc = GET_PREV_ALLOC(HDRP(oldptr));
    if (oldsize >= asize) {
        if ((oldsize - asize) >= MIN_BLOCK) {
            PUT(HDRP(oldptr), PACK(asize, prev_alloc, 1));
            void * rem = NEXT_BLKP(oldptr);
            PUT(HDRP(rem), PACK(oldsize - asize, 1, 0));
            PUT(FTRP(rem), PACK(oldsize - asize, 1, 0));
            set_next_prev_alloc(rem, 0);
            coalesce(rem);
        }
        return oldptr;
    }
    void * next = NEXT_BLKP(oldptr);
    size_t next_size = GET_SIZE(HDRP(next));
    int next_alloc = GET_ALLOC(HDRP(next));
    if (!next_alloc && (oldsize + next_size) >= asize) {
        size_t combined = oldsize + next_size;
        remove_free(next);
        if ((combined - asize) >= MIN_BLOCK) {
            PUT(HDRP(oldptr), PACK(asize, prev_alloc, 1));
            void * rem = NEXT_BLKP(oldptr);
            PUT(HDRP(rem), PACK(combined - asize, 1, 0));
            PUT(FTRP(rem), PACK(combined - asize, 1, 0));
            set_next_prev_alloc(rem, 0);
            insert_free(rem);
        }
        else {
            PUT(HDRP(oldptr), PACK(combined, prev_alloc, 1));
            set_next_prev_alloc(oldptr, 1);
        }
        return oldptr;
    }
    if (!next_size) {
        size_t need = asize - oldsize;
        size_t ext = MAX(need, CHUNKSIZE);
        if (ext % DSIZE) ext = (ext + DSIZE - 1) & ~((size_t)(DSIZE - 1));
        if (mem_sbrk(ext) == (void *)-1) {
            return NULL;
        }
        size_t new_size = oldsize + ext;
        PUT(HDRP(oldptr), PACK(new_size, prev_alloc, 1));
        PUT(HDRP(NEXT_BLKP(oldptr)), PACK(0, 1, 1));
        if ((new_size - asize) >= MIN_BLOCK) {
            PUT(HDRP(oldptr), PACK(asize, prev_alloc, 1));
            void * rem = NEXT_BLKP(oldptr);
            PUT(HDRP(rem), PACK(new_size - asize, 1, 0));
            PUT(FTRP(rem), PACK(new_size - asize, 1, 0));
            set_next_prev_alloc(rem, 0);
            insert_free(rem);
        }
        return oldptr;
    }
    void * newptr = malloc(size);
    if (!newptr) {
        return NULL;
    }
    size_t copy = oldsize - WSIZE;
    if (copy > size) {
        copy = size;
    }
    memcpy(newptr, oldptr, copy);
    free(oldptr);
    return newptr;
}

/*
 * calloc
 */
void *calloc(size_t nmemb, size_t size) {
    size_t bytes = nmemb * size;
    void * newptr = malloc(bytes);
    if (newptr) {
        memset(newptr, 0, bytes);
    }
    return newptr;
}

/*
 * mm_checkheap
 */
bool mm_checkheap(int lineno) {
    (void) lineno;
    char * prol = heap_listp;
    if (GET_SIZE(HDRP(prol)) != DSIZE || !GET_ALLOC(HDRP(prol))) {
        fprintf(stderr, "[%d] bad prologue header\n", lineno);
        return false;
    }
    if (GET_SIZE(FTRP(prol)) != DSIZE || !GET_ALLOC(FTRP(prol))) {
        fprintf(stderr, "[%d] bad prologue footer\n", lineno);
        return false;
    }
    size_t free_count_heap = 0;
    int last_alloc = 1;
    char * bp;
    for (bp = NEXT_BLKP(prol); GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) {
        if (((uintptr_t)bp & 0x7)) {
            fprintf(stderr, "[%d] payload %p not 8-aligned\n", lineno, bp);
            return false;
        }
        size_t sz = GET_SIZE(HDRP(bp));
        if (sz < MIN_BLOCK || (sz & 0x7)) {
            fprintf(stderr, "[%d] bad size %zu at %p\n", lineno, sz, bp);
            return false;
        }
        int pa = GET_PREV_ALLOC(HDRP(bp));
        if (pa != last_alloc) {
            fprintf(stderr, "[%d] prev_alloc mismatch at %p: bit=%d real=%d\n",
                    lineno, bp, pa, last_alloc);
            return false;
        }
        if (!GET_ALLOC(HDRP(bp))) {
            if (GET(HDRP(bp)) != GET(FTRP(bp))) {
                fprintf(stderr, "[%d] hdr/ftr mismatch at %p\n", lineno, bp);
                return false;
            }
            if (!last_alloc) {
                fprintf(stderr, "[%d] uncoalesced free at %p\n", lineno, bp);
                return false;
            }
            free_count_heap++;
        }
        last_alloc = GET_ALLOC(HDRP(bp));
    }
    if (GET_SIZE(HDRP(bp)) || !GET_ALLOC(HDRP(bp))) {
        fprintf(stderr, "[%d] bad epilogue\n", lineno);
        return false;
    }
    size_t free_count_lists = 0;
    for (int k = 0; k < NUM_CLASSES; k++) {
        void * p = off_to_ptr(*class_head(k));
        void * prev = NULL;
        while (p != NULL) {
            if ((char *)p < heap_base ||
                (char *)p > (char *)mem_heap_hi()) {
                fprintf(stderr, "[%d] free-list ptr %p out of heap\n", lineno, p);
                return false;
            }
            if (GET_ALLOC(HDRP(p))) {
                fprintf(stderr, "[%d] allocated block %p on free list %d\n", lineno, p, k);
                return false;
            }
            if (size_class(GET_SIZE(HDRP(p))) != k) {
                fprintf(stderr, "[%d] block %p size %zu in wrong class %d\n", lineno, p, GET_SIZE(HDRP(p)), k);
                return false;
            }
            if (GET_PRED(p) != prev) {
                fprintf(stderr, "[%d] bad pred link at %p\n", lineno, p);
                return false;
            }
            prev = p;
            p = GET_SUCC(p);
            free_count_lists++;
        }
    }
    if (free_count_heap != free_count_lists) {
        fprintf(stderr, "[%d] free count mismatch: heap=%zu lists=%zu\n", lineno, free_count_heap, free_count_lists);
        return false;
    }
    return true;
}

/* 
 * extend_heap
 * Extend the heap by `words` words. Return a pointer to the new free block on
 * success. Otherwise return NULL.
*/
// HINT: Make sure the heap size is properly aligned. Don't forget to coalesce
// free blocks.
static void * extend_heap(size_t words) {
    char * bp;
    size_t size = (words % 2) ? ((words + 1) * WSIZE) : (words * WSIZE);
    if (size < MIN_BLOCK) {
        size = MIN_BLOCK;
    }
    if((bp = mem_sbrk(size)) == (void *)-1) {
        return NULL;
    }
    unsigned int old_epi = GET(HDRP(bp));
    int prev_alloc = (old_epi & 0x2) >> 1;
    PUT(HDRP(bp), PACK(size, prev_alloc, 0));
    PUT(FTRP(bp), PACK(size, prev_alloc, 0));
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 0, 1));
    return coalesce(bp);
}

/*
 * coalesce
 * Merge two adjacent free memory chunks, return the merged block.
*/
static void * coalesce(void * bp) {
    size_t prev_alloc = GET_PREV_ALLOC(HDRP(bp));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t size = GET_SIZE(HDRP(bp));
    if (prev_alloc && next_alloc) {
        PUT(HDRP(bp), PACK(size, 1, 0));
        PUT(FTRP(bp), PACK(size, 1, 0));
        set_next_prev_alloc(bp, 0);
    }
    else if (prev_alloc && !next_alloc) {
        void * next = NEXT_BLKP(bp);
        remove_free(next);
        size += GET_SIZE(HDRP(next));
        PUT(HDRP(bp), PACK(size, 1, 0));
        PUT(FTRP(bp), PACK(size, 1, 0));
        set_next_prev_alloc(bp, 0);
    }
    else if (!prev_alloc && next_alloc) {
        void * prev = PREV_BLKP(bp);
        remove_free(prev);
        size += GET_SIZE(HDRP(prev));
        int pp_alloc = GET_PREV_ALLOC(HDRP(prev));
        PUT(HDRP(prev), PACK(size, pp_alloc, 0));
        PUT(FTRP(prev), PACK(size, pp_alloc, 0));
        bp = prev;
        set_next_prev_alloc(bp, 0);
    }
    else {
        void * prev = PREV_BLKP(bp);
        void * next = NEXT_BLKP(bp);
        remove_free(prev);
        remove_free(next);
        size += GET_SIZE(HDRP(prev)) + GET_SIZE(HDRP(next));
        int pp_alloc = GET_PREV_ALLOC(HDRP(prev));
        PUT(HDRP(prev), PACK(size, pp_alloc, 0));
        PUT(FTRP(prev), PACK(size, pp_alloc, 0));
        bp = prev;
        set_next_prev_alloc(bp, 0);
    }
    insert_free(bp);
    return bp;
}

/* First-fit search */
// Return the first fit block, if not find, return NULL
static void * find_fit(size_t asize) {
    int k = size_class(asize);
    for (; k < NUM_CLASSES; ++ k) {
        void * bp = off_to_ptr(* class_head(k));
        void * best = NULL;
        size_t best_size = (size_t)-1;
        int searched = 0;
        while (bp) {
            size_t size = GET_SIZE(HDRP(bp));
            if (size >= asize) {
                if (size == asize) {
                    return bp;
                }
                if (size < best_size) {
                    best = bp;
                    best_size = size;
                }
                if (++searched >= SEARCH_LIMIT) {
                    break;
                }
            }
            bp = GET_SUCC(bp);
        }
        if (best) {
            return best;
        }
    }
    return NULL;
}

// Place the block
static void place(void * bp, size_t asize) {
    size_t csize = GET_SIZE(HDRP(bp));
    int prev_alloc = GET_PREV_ALLOC(HDRP(bp));
    remove_free(bp);
    if((csize - asize) >= MIN_BLOCK) {
        PUT(HDRP(bp), PACK(asize, prev_alloc, 1));
        void * rem = NEXT_BLKP(bp);
        PUT(HDRP(rem), PACK(csize - asize, 1, 0));
        PUT(FTRP(rem), PACK(csize - asize, 1, 0));
        insert_free(rem);
    }
    else {
        PUT(HDRP(bp), PACK(csize, prev_alloc, 1));
        set_next_prev_alloc(bp, 1);
    }
}
