/*
 * Note: this file originally auto-generated by mib2c using
 *       version : 14170 $ of $ 
 *
 * $Id:$
 */
/*
 * standard Net-SNMP includes 
 */
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-features.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

/*
 * include our parent header 
 */
#include "ipDefaultRouterTable.h"


#include "ipDefaultRouterTable_data_access.h"

netsnmp_feature_require(container_lifo);

/** @ingroup interface
 * @addtogroup data_access data_access: Routines to access data
 *
 * These routines are used to locate the data used to satisfy
 * requests.
 * 
 * @{
 */
/**********************************************************************
 **********************************************************************
 ***
 *** Table ipDefaultRouterTable
 ***
 **********************************************************************
 **********************************************************************/
/*
 * IP-MIB::ipDefaultRouterTable is subid 37 of ip.
 * Its status is Current.
 * OID: .1.3.6.1.2.1.4.37, length: 8
 */

/**
 * initialization for ipDefaultRouterTable data access
 *
 * This function is called during startup to allow you to
 * allocate any resources you need for the data table.
 *
 * @param ipDefaultRouterTable_reg
 *        Pointer to ipDefaultRouterTable_registration
 *
 * @retval MFD_SUCCESS : success.
 * @retval MFD_ERROR   : unrecoverable error.
 */
int
ipDefaultRouterTable_init_data(ipDefaultRouterTable_registration *
                               ipDefaultRouterTable_reg)
{
    DEBUGMSGTL(("verbose:ipDefaultRouterTable:ipDefaultRouterTable_init_data", "called\n"));

    /*
     * TODO:303:o: Initialize ipDefaultRouterTable data.
     */

    return MFD_SUCCESS;
}                               /* ipDefaultRouterTable_init_data */

/**
 * container overview
 *
 */

/**
 * container initialization
 *
 * @param container_ptr_ptr A pointer to a container pointer. If you
 *        create a custom container, use this parameter to return it
 *        to the MFD helper. If set to NULL, the MFD helper will
 *        allocate a container for you.
 * @param  cache A pointer to a cache structure. You can set the timeout
 *         and other cache flags using this pointer.
 *
 *  This function is called at startup to allow you to customize certain
 *  aspects of the access method. For the most part, it is for advanced
 *  users. The default code should suffice for most cases. If no custom
 *  container is allocated, the MFD code will create one for your.
 *
 *  This is also the place to set up cache behavior. The default, to
 *  simply set the cache timeout, will work well with the default
 *  container. If you are using a custom container, you may want to
 *  look at the cache helper documentation to see if there are any
 *  flags you want to set.
 *
 * @remark
 *  This would also be a good place to do any initialization needed
 *  for you data source. For example, opening a connection to another
 *  process that will supply the data, opening a database, etc.
 */
void
ipDefaultRouterTable_container_init(netsnmp_container ** container_ptr_ptr,
                                    netsnmp_cache * cache)
{
    DEBUGMSGTL(("verbose:ipDefaultRouterTable:ipDefaultRouterTable_container_init", "called\n"));

    if (NULL == container_ptr_ptr) {
        snmp_log(LOG_ERR,
                 "bad container param to ipDefaultRouterTable_container_init\n");
        return;
    }

    /*
     * For advanced users, you can use a custom container. If you
     * do not create one, one will be created for you.
     */
    *container_ptr_ptr = NULL;

    if (NULL == cache) {
        snmp_log(LOG_ERR,
                 "bad cache param to ipDefaultRouterTable_container_init\n");
        return;
    }

    /*
     * TODO:345:A: Set up ipDefaultRouterTable cache properties.
     *
     * Also for advanced users, you can set parameters for the
     * cache. Do not change the magic pointer, as it is used
     * by the MFD helper. To completely disable caching, set
     * cache->enabled to 0.
     */
    cache->timeout = IPDEFAULTROUTERTABLE_CACHE_TIMEOUT;        /* seconds */
}                               /* ipDefaultRouterTable_container_init */

/**
 * container shutdown
 *
 * @param container_ptr A pointer to the container.
 *
 *  This function is called at shutdown to allow you to customize certain
 *  aspects of the access method. For the most part, it is for advanced
 *  users. The default code should suffice for most cases.
 *
 *  This function is called before ipDefaultRouterTable_container_free().
 *
 * @remark
 *  This would also be a good place to do any cleanup needed
 *  for you data source. For example, closing a connection to another
 *  process that supplied the data, closing a database, etc.
 */
void
ipDefaultRouterTable_container_shutdown(netsnmp_container * container_ptr)
{
    DEBUGMSGTL(("verbose:ipDefaultRouterTable:ipDefaultRouterTable_container_shutdown", "called\n"));

    if (NULL == container_ptr) {
        snmp_log(LOG_ERR,
                 "bad params to ipDefaultRouterTable_container_shutdown\n");
        return;
    }

}                               /* ipDefaultRouterTable_container_shutdown */

/**
 * check entry for update
 */
static void
_check_entry_for_updates(ipDefaultRouterTable_rowreq_ctx * rowreq_ctx,
                         void **magic)
{
    netsnmp_container *defaultrouter_container = magic[0];
    netsnmp_container *to_delete = (netsnmp_container *) magic[1];

    /*
     * check for matching entry using secondary index.
     */
    netsnmp_defaultrouter_entry *defaultrouter_entry =
        CONTAINER_FIND(defaultrouter_container, rowreq_ctx->data);
    if (NULL == defaultrouter_entry) {
        DEBUGMSGTL(("ipDefaultRouterTable:access", "removing missing entry\n"));

        if (NULL == to_delete) {
            magic[1] = to_delete = netsnmp_container_find("lifo");
            if (NULL == to_delete)
                snmp_log(LOG_ERR, "couldn't create delete container\n");
        }
        if (NULL != to_delete)
            CONTAINER_INSERT(to_delete, rowreq_ctx);
    } else {
        DEBUGMSGTL(("ipDefaultRouterTable:access", "updating existing entry\n"));

        /*
         * Check for changes & update
         */
        netsnmp_access_defaultrouter_entry_update(rowreq_ctx->data,
                                                  defaultrouter_entry);

        /*
         * remove entry from ifcontainer
         */
        CONTAINER_REMOVE(defaultrouter_container, defaultrouter_entry);
        netsnmp_access_defaultrouter_entry_free(defaultrouter_entry);
    }
}

/**
 * add new entry
 */
static void
_add_new_entry(netsnmp_defaultrouter_entry *defaultrouter_entry,
               netsnmp_container *container)
{
    ipDefaultRouterTable_rowreq_ctx *rowreq_ctx;

    DEBUGMSGTL(("ipDefaultRouterTable:access", "creating new entry\n"));

    netsnmp_assert(NULL != defaultrouter_entry);
    netsnmp_assert(NULL != container);

    /*
     * allocate an row context and set the index(es)
     */
    rowreq_ctx = ipDefaultRouterTable_allocate_rowreq_ctx(defaultrouter_entry,
                                                          NULL);
    if ((NULL != rowreq_ctx) &&
            (MFD_SUCCESS ==
             ipDefaultRouterTable_indexes_set(rowreq_ctx,
                 defaultrouter_entry->dr_addresstype,
                 defaultrouter_entry->dr_address,
                 defaultrouter_entry->dr_address_len,
                 defaultrouter_entry->dr_if_index))) {
        if (CONTAINER_INSERT(container, rowreq_ctx) < 0) {
            DEBUGMSGTL(("ipAddressTable:access",
                         "container insert failed for new entry\n"));
            ipDefaultRouterTable_release_rowreq_ctx(rowreq_ctx);
            return;
        }
    } else {
        if (NULL != rowreq_ctx) {
            snmp_log(LOG_ERR, "error setting index while loading "
                    "ipDefaultRouterTable cache.\n");
            ipDefaultRouterTable_release_rowreq_ctx(rowreq_ctx);
        } else {
            snmp_log(LOG_ERR, "memory allocation failed while loading "
                     "ipDefaultRouterTable cache.\n");
            netsnmp_access_defaultrouter_entry_free(defaultrouter_entry);
        }

        return;
    }
}

/**
 * load initial data
 *
 * TODO:350:M: Implement ipDefaultRouterTable data load
 * This function will also be called by the cache helper to load
 * the container again (after the container free function has been
 * called to free the previous contents).
 *
 * @param container container to which items should be inserted
 *
 * @retval MFD_SUCCESS              : success.
 * @retval MFD_RESOURCE_UNAVAILABLE : Can't access data source
 * @retval MFD_ERROR                : other error.
 *
 *  This function is called to load the index(es) (and data, optionally)
 *  for the every row in the data set.
 *
 * @remark
 *  While loading the data, the only important thing is the indexes.
 *  If access to your data is cheap/fast (e.g. you have a pointer to a
 *  structure in memory), it would make sense to update the data here.
 *  If, however, the accessing the data involves more work (e.g. parsing
 *  some other existing data, or performing calculations to derive the data),
 *  then you can limit yourself to setting the indexes and saving any
 *  information you will need later. Then use the saved information in
 *  ipDefaultRouterTable_row_prep() for populating data.
 *
 * @note
 *  If you need consistency between rows (like you want statistics
 *  for each row to be from the same time frame), you should set all
 *  data here.
 *
 */
int
ipDefaultRouterTable_container_load(netsnmp_container * container)
{
    netsnmp_container *defaultrouter_container;
    void              *tmp_ptr[2];

    DEBUGMSGTL(("verbose:ipDefaultRouterTable:ipDefaultRouterTable_container_load", "called\n"));

    /*
     * TODO:351:M: |-> Load/update data in the ipDefaultRouterTable container.
     * loop over your ipDefaultRouterTable data, allocate a rowreq context,
     * set the index(es) [and data, optionally] and insert into
     * the container.
     */
    defaultrouter_container =
        netsnmp_access_defaultrouter_container_load(NULL,
                        NETSNMP_ACCESS_DEFAULTROUTER_LOAD_ADDL_IDX_BY_ADDR);

    if (NULL == defaultrouter_container)
        return MFD_RESOURCE_UNAVAILABLE;        /* msg already logged */

    /*
     * we just got a fresh copy of interface data. compare it to
     * what we've already got, and make any adjustments, saving
     * missing addresses to be deleted.
     */
    tmp_ptr[0] = defaultrouter_container->next;
    tmp_ptr[1] = NULL;
    CONTAINER_FOR_EACH(container,
                       (netsnmp_container_obj_func *) _check_entry_for_updates,
                       tmp_ptr);

    /*
     * now add any new interfaces
     */
    CONTAINER_FOR_EACH(defaultrouter_container,
                       (netsnmp_container_obj_func *) _add_new_entry,
                       container);

    /*
     * free the container. we've either claimed each entry, or released it,
     * so the access function doesn't need to clear the container.
     */
    netsnmp_access_defaultrouter_container_free(defaultrouter_container,
                NETSNMP_ACCESS_DEFAULTROUTER_FREE_DONT_CLEAR);

    /*
     * remove deleted addresses from table container
     */
    if (NULL != tmp_ptr[1]) {
        netsnmp_container *tmp_container =
            (netsnmp_container *) tmp_ptr[1];
        ipDefaultRouterTable_rowreq_ctx *tmp_ctx;

        /*
         * this works because the tmp_container is a linked list,
         * which can be used like a stack...
         */
        while (CONTAINER_SIZE(tmp_container)) {
            /*
             * get from delete list
             */
            tmp_ctx = CONTAINER_FIRST(tmp_container);

            /*
             * release context, delete from table container
             */
            CONTAINER_REMOVE(container, tmp_ctx);
            ipDefaultRouterTable_release_rowreq_ctx(tmp_ctx);

            /*
             * pop off delete list
             */
            CONTAINER_REMOVE(tmp_container, NULL);
        }
    }

    DEBUGMSGT(("verbose:ipDefaultRouterTable:ipDefaultRouterTable_container_load",
               "%" NETSNMP_PRIz "d records\n", CONTAINER_SIZE(container)));

    return MFD_SUCCESS;
}

/**
 * container clean up
 *
 * @param container container with all current items
 *
 *  This optional callback is called prior to all
 *  item's being removed from the container. If you
 *  need to do any processing before that, do it here.
 *
 * @note
 *  The MFD helper will take care of releasing all the row contexts.
 *
 */
void
ipDefaultRouterTable_container_free(netsnmp_container * container)
{
    DEBUGMSGTL(("verbose:ipDefaultRouterTable:ipDefaultRouterTable_container_free", "called\n"));

    /*
     * TODO:380:M: Free ipDefaultRouterTable container data.
     */
}                               /* ipDefaultRouterTable_container_free */

/**
 * prepare row for processing.
 *
 *  When the agent has located the row for a request, this function is
 *  called to prepare the row for processing. If you fully populated
 *  the data context during the index setup phase, you may not need to
 *  do anything.
 *
 * @param rowreq_ctx pointer to a context.
 *
 * @retval MFD_SUCCESS     : success.
 * @retval MFD_ERROR       : other error.
 */
int
ipDefaultRouterTable_row_prep(ipDefaultRouterTable_rowreq_ctx * rowreq_ctx)
{
    DEBUGMSGTL(("verbose:ipDefaultRouterTable:ipDefaultRouterTable_row_prep", "called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

    /*
     * TODO:390:o: Prepare row for request.
     * If populating row data was delayed, this is the place to
     * fill in the row for this request.
     */

    return MFD_SUCCESS;
}                               /* ipDefaultRouterTable_row_prep */

/** @} */
