/****************************************************************/
/******* Author    : Mahmoud Abdelraouf Mahmoud *****************/
/******* Date      : 8 Apr 2023                 *****************/
/******* Version   : 0.1                        *****************/
/******* File Name : UserAPI_mm.h               *****************/
/****************************************************************/
#ifndef __UAPI_MM_H__
#define __UAPI_MM_H__
/**-----------------< Includes section -----------------*/
#include <stdint.h>

/**-----------------< Public functions interface section -----------------*/
/**
 * @brief Initializes the memory manager.
 * 
 * This function initializes the memory manager. It sets up necessary configurations
 * and parameters for memory management operations within the program. It specifically
 * determines the system page size using the `getpagesize()` system call and assigns
 * it to the global variable `SYSTEM_PAGE_SIZE`.
 * 
 * @note This function should be called before any memory management operations are performed
 *       within the program. It is typically called at the beginning of the program execution
 *       to ensure proper initialization of memory management functionalities.
 * 
 * @warning This function relies on the `getpagesize()` system call to determine the system page size.
 *           Therefore, it may not be portable across all platforms. It is primarily intended for use
 *           in Unix-like systems where `getpagesize()` is available.
 * 
 * @see man getpagesize()
 */
void mm_init();

/**
 * @brief Instantiates a new page family for a memory structure.
 * 
 * This function creates a new page family for a memory structure identified by its name
 * and size. It allocates memory for the page family and adds it to the existing virtual
 * memory pages if necessary. Each page family can contain multiple memory structures of
 * the same type.
 * 
 * @param struct_name The name of the memory structure.
 * @param struct_size The size of the memory structure.
 * 
 * @note If the size of the memory structure exceeds the system page size, an error message
 *       is printed, and the function returns without creating the page family.
 * 
 * @note This function maintains a linked list of virtual memory pages (`first_vm_page_for_families`)
 *       to store the page families. If there are no existing pages, it allocates a new page and
 *       initializes it with the first page family. If the existing pages are full, it allocates
 *       a new page and adds it to the beginning of the linked list.
 * 
 * @note If a page family with the same name already exists, an assertion error is triggered, indicating
 *       a conflict in page family instantiation.
 * 
 * @warning This function relies on the `mm_get_new_vm_page_from_kernel()` function to allocate
 *           memory from the kernel for the page family. Improper use or misuse of this function
 *           can lead to memory leaks or system instability.
 * 
 * @see mm_get_new_vm_page_from_kernel()
 */
void mm_instantiate_new_page_family (char *struct_name, uint32_t struct_size);

/**
 * @brief Prints all registered page families.
 * 
 * This function prints all page families that have been registered with the Linux Memory Manager.
 * It iterates over all virtual memory pages hosting page families and prints information about
 * each page family, including its name and size.
 * 
 * @note This function should be invoked after the application has performed registration for all
 *       its structures using the `MM_REG_STRUCT` macro. It relies on the `first_vm_page_for_families`
 *       global variable, which maintains a linked list of virtual memory pages containing page families.
 * 
 * @see MM_REG_STRUCT
 */
void mm_print_registered_page_families();

/**-----------------< Function-like macro section -----------------*/
/**
 * @brief Registers a memory structure for page family instantiation.
 * 
 * This macro facilitates the registration of a memory structure for page family instantiation
 * within the memory manager. It takes the name of the structure (`struct_name`) as a parameter
 * and uses the `#` operator to stringify it, which is then passed to the `mm_instantiate_new_page_family()`
 * function along with the size of the structure.
 * 
 * @param struct_name The name of the memory structure to be registered.
 * 
 * @note This macro should be used to register each memory structure before it is instantiated
 *       as a page family within the memory manager. It ensures proper initialization of the
 *       memory management system and enables efficient allocation and management of memory pages.
 * 
 * @see mm_instantiate_new_page_family()
 */
#define MM_REG_STRUCT(struct_name) \
    (mm_instantiate_new_page_family(#struct_name, sizeof(struct_name)))

#endif /**< __UAPI_MM_H__ */