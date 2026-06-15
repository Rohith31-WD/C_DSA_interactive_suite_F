#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"

/**
 * Unit tests for Doubly Circular Linked List (DCLL)
 * 
 * Test coverage:
 * - Initialization
 * - Insert operations (beginning, end, position)
 * - Delete operations (beginning, end, value, position)
 * - Search functionality
 * - Length tracking
 * - Memory management
 * - Edge cases (empty list, single node, etc.)
 */

/* Helper function to print test results */
static void print_test(const char* test_name, int passed)
{
    printf("%s: %s\n", test_name, passed ? "✓ PASSED" : "✗ FAILED");
}

/* Test 1: Initialization */
void test_dcll_init(void)
{
    dcll list;
    dcll_init(&list);
    
    assert(list.head == NULL);
    assert(list.tail == NULL);
    assert(list.length == 0);
    
    print_test("test_dcll_init", 1);
}

/* Test 2: Insert at beginning (single node) */
void test_dcll_insertAtBeginning_single(void)
{
    dcll list;
    dcll_init(&list);
    
    int result = dcll_insertAtBeginning(&list, 10);
    
    assert(result == 1);
    assert(list.head != NULL);
    assert(list.tail != NULL);
    assert(list.head == list.tail);
    assert(list.head->data == 10);
    assert(list.head->next == list.head);
    assert(list.head->prev == list.head);
    assert(list.length == 1);
    
    dcll_destroy(&list);
    print_test("test_dcll_insertAtBeginning_single", 1);
}

/* Test 3: Insert at beginning (multiple nodes) */
void test_dcll_insertAtBeginning_multiple(void)
{
    dcll list;
    dcll_init(&list);
    
    dcll_insertAtBeginning(&list, 20);
    dcll_insertAtBeginning(&list, 10);
    dcll_insertAtBeginning(&list, 5);
    
    assert(list.length == 3);
    assert(list.head->data == 5);
    assert(list.head->next->data == 10);
    assert(list.head->next->next->data == 20);
    assert(list.tail->data == 20);
    assert(list.tail->next == list.head);
    assert(list.head->prev == list.tail);
    
    dcll_destroy(&list);
    print_test("test_dcll_insertAtBeginning_multiple", 1);
}

/* Test 4: Insert at end */
void test_dcll_insertAtEnd(void)
{
    dcll list;
    dcll_init(&list);
    
    dcll_insertAtEnd(&list, 10);
    dcll_insertAtEnd(&list, 20);
    dcll_insertAtEnd(&list, 30);
    
    assert(list.length == 3);
    assert(list.head->data == 10);
    assert(list.tail->data == 30);
    assert(list.head->next->data == 20);
    assert(list.tail->prev->data == 20);
    assert(list.tail->next == list.head);
    assert(list.head->prev == list.tail);
    
    dcll_destroy(&list);
    print_test("test_dcll_insertAtEnd", 1);
}

/* Test 5: Insert at position */
void test_dcll_insertAtPosition(void)
{
    dcll list;
    dcll_init(&list);
    
    dcll_insertAtEnd(&list, 10);
    dcll_insertAtEnd(&list, 30);
    dcll_insertAtPosition(&list, 20, 1);
    
    assert(list.length == 3);
    assert(list.head->data == 10);
    assert(list.head->next->data == 20);
    assert(list.tail->data == 30);
    
    dcll_destroy(&list);
    print_test("test_dcll_insertAtPosition", 1);
}

/* Test 6: Delete at beginning */
void test_dcll_deleteAtBeginning(void)
{
    dcll list;
    dcll_init(&list);
    
    dcll_insertAtEnd(&list, 10);
    dcll_insertAtEnd(&list, 20);
    dcll_insertAtEnd(&list, 30);
    
    int result = dcll_deleteAtBeginning(&list);
    
    assert(result == 1);
    assert(list.length == 2);
    assert(list.head->data == 20);
    assert(list.tail->data == 30);
    
    dcll_destroy(&list);
    print_test("test_dcll_deleteAtBeginning", 1);
}

/* Test 7: Delete at end */
void test_dcll_deleteAtEnd(void)
{
    dcll list;
    dcll_init(&list);
    
    dcll_insertAtEnd(&list, 10);
    dcll_insertAtEnd(&list, 20);
    dcll_insertAtEnd(&list, 30);
    
    int result = dcll_deleteAtEnd(&list);
    
    assert(result == 1);
    assert(list.length == 2);
    assert(list.head->data == 10);
    assert(list.tail->data == 20);
    assert(list.tail->next == list.head);
    
    dcll_destroy(&list);
    print_test("test_dcll_deleteAtEnd", 1);
}

/* Test 8: Delete by value */
void test_dcll_deleteByValue(void)
{
    dcll list;
    dcll_init(&list);
    
    dcll_insertAtEnd(&list, 10);
    dcll_insertAtEnd(&list, 20);
    dcll_insertAtEnd(&list, 30);
    
    int result = dcll_deleteByValue(&list, 20);
    
    assert(result == 1);
    assert(list.length == 2);
    assert(list.head->data == 10);
    assert(list.head->next->data == 30);
    assert(list.tail->data == 30);
    
    dcll_destroy(&list);
    print_test("test_dcll_deleteByValue", 1);
}

/* Test 9: Delete at position */
void test_dcll_deleteAtPosition(void)
{
    dcll list;
    dcll_init(&list);
    
    dcll_insertAtEnd(&list, 10);
    dcll_insertAtEnd(&list, 20);
    dcll_insertAtEnd(&list, 30);
    
    int result = dcll_deleteAtPosition(&list, 1);
    
    assert(result == 1);
    assert(list.length == 2);
    assert(list.head->data == 10);
    assert(list.head->next->data == 30);
    
    dcll_destroy(&list);
    print_test("test_dcll_deleteAtPosition", 1);
}

/* Test 10: Search */
void test_dcll_search(void)
{
    dcll list;
    dcll_init(&list);
    
    dcll_insertAtEnd(&list, 10);
    dcll_insertAtEnd(&list, 20);
    dcll_insertAtEnd(&list, 30);
    
    int idx1 = dcll_search(&list, 10);
    int idx2 = dcll_search(&list, 20);
    int idx3 = dcll_search(&list, 30);
    int idx_not_found = dcll_search(&list, 99);
    
    assert(idx1 == 0);
    assert(idx2 == 1);
    assert(idx3 == 2);
    assert(idx_not_found == -1);
    
    dcll_destroy(&list);
    print_test("test_dcll_search", 1);
}

/* Test 11: Get length */
void test_dcll_getLength(void)
{
    dcll list;
    dcll_init(&list);
    
    assert(dcll_getLength(&list) == 0);
    
    dcll_insertAtEnd(&list, 10);
    assert(dcll_getLength(&list) == 1);
    
    dcll_insertAtEnd(&list, 20);
    dcll_insertAtEnd(&list, 30);
    assert(dcll_getLength(&list) == 3);
    
    dcll_deleteAtEnd(&list);
    assert(dcll_getLength(&list) == 2);
    
    dcll_destroy(&list);
    print_test("test_dcll_getLength", 1);
}

/* Test 12: Delete single node */
void test_dcll_delete_single_node(void)
{
    dcll list;
    dcll_init(&list);
    
    dcll_insertAtEnd(&list, 10);
    int result = dcll_deleteAtBeginning(&list);
    
    assert(result == 1);
    assert(list.head == NULL);
    assert(list.tail == NULL);
    assert(list.length == 0);
    
    dcll_destroy(&list);
    print_test("test_dcll_delete_single_node", 1);
}

/* Test 13: Delete from empty list */
void test_dcll_delete_empty_list(void)
{
    dcll list;
    dcll_init(&list);
    
    int result1 = dcll_deleteAtBeginning(&list);
    int result2 = dcll_deleteAtEnd(&list);
    
    assert(result1 == -1);
    assert(result2 == -1);
    
    dcll_destroy(&list);
    print_test("test_dcll_delete_empty_list", 1);
}

/* Test 14: Insert at invalid position */
void test_dcll_insertAtPosition_invalid(void)
{
    dcll list;
    dcll_init(&list);
    
    dcll_insertAtEnd(&list, 10);
    int result = dcll_insertAtPosition(&list, 20, 5);
    
    assert(result == -2);
    assert(list.length == 1);
    
    dcll_destroy(&list);
    print_test("test_dcll_insertAtPosition_invalid", 1);
}

/* Test 15: Circular property after operations */
void test_dcll_circular_property(void)
{
    dcll list;
    dcll_init(&list);
    
    dcll_insertAtEnd(&list, 10);
    dcll_insertAtEnd(&list, 20);
    dcll_insertAtEnd(&list, 30);
    
    // Verify forward circular
    dcll_Node* cur = list.head;
    for (int i = 0; i < list.length; i++)
        cur = cur->next;
    assert(cur == list.head);
    
    // Verify backward circular
    cur = list.tail;
    for (int i = 0; i < list.length; i++)
        cur = cur->prev;
    assert(cur == list.tail);
    
    dcll_destroy(&list);
    print_test("test_dcll_circular_property", 1);
}

/* Test 16: Delete by value not found */
void test_dcll_deleteByValue_not_found(void)
{
    dcll list;
    dcll_init(&list);
    
    dcll_insertAtEnd(&list, 10);
    dcll_insertAtEnd(&list, 20);
    
    int result = dcll_deleteByValue(&list, 99);
    
    assert(result == -1);
    assert(list.length == 2);
    
    dcll_destroy(&list);
    print_test("test_dcll_deleteByValue_not_found", 1);
}

/* Test 17: Search on empty list */
void test_dcll_search_empty(void)
{
    dcll list;
    dcll_init(&list);
    
    int result = dcll_search(&list, 10);
    
    assert(result == -1);
    
    dcll_destroy(&list);
    print_test("test_dcll_search_empty", 1);
}

/* Test 18: Large list operations */
void test_dcll_large_list(void)
{
    dcll list;
    dcll_init(&list);
    
    // Insert 100 elements
    for (int i = 1; i <= 100; i++)
    {
        int result = dcll_insertAtEnd(&list, i);
        assert(result == 1);
    }
    
    assert(list.length == 100);
    assert(list.head->data == 1);
    assert(list.tail->data == 100);
    
    // Search for elements
    assert(dcll_search(&list, 1) == 0);
    assert(dcll_search(&list, 50) == 49);
    assert(dcll_search(&list, 100) == 99);
    
    // Delete head and tail
    dcll_deleteAtBeginning(&list);
    dcll_deleteAtEnd(&list);
    
    assert(list.length == 98);
    assert(list.head->data == 2);
    assert(list.tail->data == 99);
    
    dcll_destroy(&list);
    print_test("test_dcll_large_list", 1);
}

/* Main test runner */
int main(void)
{
    printf("\n========================================\n");
    printf("DCLL Unit Tests\n");
    printf("========================================\n\n");
    
    test_dcll_init();
    test_dcll_insertAtBeginning_single();
    test_dcll_insertAtBeginning_multiple();
    test_dcll_insertAtEnd();
    test_dcll_insertAtPosition();
    test_dcll_deleteAtBeginning();
    test_dcll_deleteAtEnd();
    test_dcll_deleteByValue();
    test_dcll_deleteAtPosition();
    test_dcll_search();
    test_dcll_getLength();
    test_dcll_delete_single_node();
    test_dcll_delete_empty_list();
    test_dcll_insertAtPosition_invalid();
    test_dcll_circular_property();
    test_dcll_deleteByValue_not_found();
    test_dcll_search_empty();
    test_dcll_large_list();
    
    printf("\n========================================\n");
    printf("All tests completed!\n");
    printf("========================================\n\n");
    
    return 0;
}
