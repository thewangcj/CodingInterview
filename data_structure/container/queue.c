#include "queue.h"
#include "linear_container.h"

// 队列与双向链表和动态数组没有任何关系，队列关心的只是 linear_container 这个接口，
// 如果调用者想换成单向链表，用单向链 表去实现 linear_container 接口就好了

// 队列/堆栈 -> container -> 双向链表/动态数组
struct _Queue
{
    LinearContainer *linear_container;
};

Queue *queue_create(LinearContainer *container)
{
    Queue *thiz = NULL;

    return_val_if_fail(container != NULL, NULL);

    thiz = (Queue *)malloc(sizeof(Queue));

    if (thiz != NULL) {
        thiz->linear_container = container;
    }

    return thiz;
}

Ret queue_head(Queue *thiz, void **data)
{
    return_val_if_fail(thiz != NULL && data != NULL, RET_INVALID_PARAMS);

    return linear_container_get_by_index(thiz->linear_container, 0, data);
}

Ret queue_push(Queue *thiz, void *data)
{
    return_val_if_fail(thiz != NULL, RET_INVALID_PARAMS);

    return linear_container_append(thiz->linear_container, data);
}

Ret queue_pop(Queue *thiz)
{
    return_val_if_fail(thiz != NULL, RET_INVALID_PARAMS);

    return linear_container_delete(thiz->linear_container, 0);
}

size_t queue_length(Queue *thiz)
{
    return_val_if_fail(thiz != NULL, 0);

    return linear_container_length(thiz->linear_container);
}

Ret queue_foreach(Queue *thiz, DataVisitFunc visit, void *ctx)
{
    return_val_if_fail(thiz != NULL && visit != NULL, RET_INVALID_PARAMS);

    return linear_container_foreach(thiz->linear_container, visit, ctx);
}

void queue_destroy(Queue *thiz)
{
    if (thiz != NULL) {
        linear_container_destroy(thiz->linear_container);
        thiz->linear_container = NULL;

        free(thiz);
    }

    return;
}

#ifdef QUEUE_TEST
#include "linear_container_dlist.h"
#include "test_helper.h"
int main(int argc, char *argv[])
{
    int i        = 0;
    int n        = 1000;
    int ret_data = 0;
    Queue *queue = queue_create(linear_container_dlist_create(NULL, NULL));

    for (i = 0; i < n; i++) {
        assert(queue_push(queue, (void *)i) == RET_OK);
        assert(queue_head(queue, (void **)&ret_data) == RET_OK);
        assert(queue_length(queue) == (i + 1));
    }

    queue_foreach(queue, print_int, NULL);

    for (i = 0; i < n; i++) {
        assert(queue_head(queue, (void **)&ret_data) == RET_OK);
        assert(ret_data == i);
        assert(queue_length(queue) == (n - i));
        assert(queue_pop(queue) == RET_OK);
    }

    queue_destroy(queue);
    return 0;
}
#endif /*QUEUE_TEST*/