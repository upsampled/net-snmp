/*
 * Note: this file originally auto-generated by mib2c using
 *  $
 */

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include <net-snmp/agent/table_container.h>
#include "sctpLookupRemIPAddrTable.h"

static netsnmp_container *sctpLookupRemIPAddrTable_container;
static netsnmp_table_registration_info *table_info;

/** Initializes the sctpLookupRemIPAddrTable module */
void
init_sctpLookupRemIPAddrTable(void)
{
    /*
     * here we initialize all the tables we're planning on supporting 
     */
    initialize_table_sctpLookupRemIPAddrTable();
}

void
shutdown_sctpLookupRemIPAddrTable(void)
{
    shutdown_table_sctpLookupRemIPAddrTable();
}

/** Initialize the sctpLookupRemIPAddrTable table by defining its contents and how it's structured */
void
initialize_table_sctpLookupRemIPAddrTable(void)
{
    static oid      sctpLookupRemIPAddrTable_oid[] =
        { 1, 3, 6, 1, 2, 1, 104, 1, 10 };
    size_t          sctpLookupRemIPAddrTable_oid_len =
        OID_LENGTH(sctpLookupRemIPAddrTable_oid);
    netsnmp_handler_registration *reg = NULL;
    netsnmp_mib_handler *handler = NULL;
    netsnmp_container *container = NULL;

    reg =
        netsnmp_create_handler_registration("sctpLookupRemIPAddrTable",
                                            sctpLookupRemIPAddrTable_handler,
                                            sctpLookupRemIPAddrTable_oid,
                                            sctpLookupRemIPAddrTable_oid_len,
                                            HANDLER_CAN_RONLY);
    if (NULL == reg) {
        snmp_log(LOG_ERR,
                 "error creating handler registration for sctpLookupRemIPAddrTable\n");
        goto bail;
    }

    container =
        netsnmp_container_find("sctpLookupRemIPAddrTable:table_container");
    if (NULL == container) {
        snmp_log(LOG_ERR,
                 "error creating container for sctpLookupRemIPAddrTable\n");
        goto bail;
    }
    sctpLookupRemIPAddrTable_container = container;

    table_info = SNMP_MALLOC_TYPEDEF(netsnmp_table_registration_info);
    if (NULL == table_info) {
        snmp_log(LOG_ERR,
                 "error allocating table registration for sctpLookupRemIPAddrTable\n");
        goto bail;
    }
    netsnmp_table_helper_add_indexes(table_info, ASN_INTEGER,   /* index: sctpLookupRemIPAddrType */
                                     ASN_OCTET_STR,     /* index: sctpLookupRemIPAddr */
                                     ASN_UNSIGNED,      /* index: sctpAssocId */
                                     0);
    table_info->min_column = COLUMN_SCTPLOOKUPREMIPADDRSTARTTIME;
    table_info->max_column = COLUMN_SCTPLOOKUPREMIPADDRSTARTTIME;

    /*************************************************
     *
     * inject container_table helper
     */
    handler = netsnmp_container_table_handler_get(table_info, container,
                                                  TABLE_CONTAINER_KEY_NETSNMP_INDEX);
    if (NULL == handler) {
        snmp_log(LOG_ERR,
                 "error allocating table registration for sctpLookupRemIPAddrTable\n");
        goto bail;
    }
    if (SNMPERR_SUCCESS != netsnmp_inject_handler(reg, handler)) {
        snmp_log(LOG_ERR,
                 "error injecting container_table handler for sctpLookupRemIPAddrTable\n");
        goto bail;
    }
    handler = NULL;             /* reg has it, will reuse below */

    /*
     * register the table
     */
    if (SNMPERR_SUCCESS != netsnmp_register_table(reg, table_info)) {
        snmp_log(LOG_ERR,
                 "error registering table handler for sctpLookupRemIPAddrTable\n");
        goto bail;
    }

    return;                     /* ok */

    /*
     * Some error occurred during registration. Clean up and bail.
     */
  bail:                        /* not ok */

    if (handler)
        netsnmp_handler_free(handler);

    if (table_info)
        netsnmp_table_registration_info_free(table_info);

    if (container)
        CONTAINER_FREE(container);

    if (reg)
        netsnmp_handler_registration_free(reg);
}

void
shutdown_table_sctpLookupRemIPAddrTable(void)
{
    if (table_info) {
        netsnmp_table_registration_info_free(table_info);
	table_info = NULL;
    }
    sctpLookupRemIPAddrTable_container_clear
        (sctpLookupRemIPAddrTable_container);
}

/** handles requests for the sctpLookupRemIPAddrTable table */
int
sctpLookupRemIPAddrTable_handler(netsnmp_mib_handler *handler,
                                 netsnmp_handler_registration *reginfo,
                                 netsnmp_agent_request_info *reqinfo,
                                 netsnmp_request_info *requests)
{

    netsnmp_request_info *request;
    netsnmp_table_request_info *table_info;
    sctpLookupRemIPAddrTable_entry *table_entry;

    switch (reqinfo->mode) {
        /*
         * Read-support (also covers GetNext requests)
         */
    case MODE_GET:
        for (request = requests; request; request = request->next) {
            if (request->processed)
                continue;
            table_entry = (sctpLookupRemIPAddrTable_entry *)
                netsnmp_container_table_extract_context(request);
            table_info = netsnmp_extract_table_info(request);
            if ((NULL == table_entry) || (NULL == table_info)) {
                snmp_log(LOG_ERR,
                         "could not extract table entry or info for sctpLookupRemIPAddrTable\n");
                snmp_set_var_typed_value(request->requestvb,
                                         SNMP_ERR_GENERR, NULL, 0);
                continue;
            }

            switch (table_info->colnum) {
            case COLUMN_SCTPLOOKUPREMIPADDRSTARTTIME:
                if (!table_entry) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer(request->requestvb,
                                           ASN_TIMETICKS,
                                           table_entry->sctpLookupRemIPAddrStartTime);
                break;
            default:
                netsnmp_set_request_error(reqinfo, request,
                                          SNMP_NOSUCHOBJECT);
                break;
            }
        }
        break;

    }
    return SNMP_ERR_NOERROR;
}

sctpLookupRemIPAddrTable_entry *
sctpLookupRemIPAddrTable_entry_create(void)
{
    sctpLookupRemIPAddrTable_entry *entry =
        SNMP_MALLOC_TYPEDEF(sctpLookupRemIPAddrTable_entry);
    if (entry != NULL) {
        entry->oid_index.len = SCTP_LOOKUP_REM_IP_ADDR_TABLE_INDEX_SIZE;
        entry->oid_index.oids = entry->oid_tmp;
    }

    return entry;
}

int
sctpLookupRemIPAddrTable_entry_update_index(sctpLookupRemIPAddrTable_entry
                                            * entry)
{
    netsnmp_variable_list var_sctpAssocRemIPAddrType;
    netsnmp_variable_list var_sctpAssocRemIPAddr;
    netsnmp_variable_list var_sctpAssocId;
    int             err = 0;

    /*
     * prepare the value to be converted 
     */
    memset(&var_sctpAssocRemIPAddrType, 0,
           sizeof(var_sctpAssocRemIPAddrType));
    var_sctpAssocRemIPAddrType.type = ASN_UNSIGNED;
    var_sctpAssocRemIPAddrType.next_variable = &var_sctpAssocRemIPAddr;
    snmp_set_var_value(&var_sctpAssocRemIPAddrType,
                       (u_char *) & entry->sctpAssocRemAddrType,
                       sizeof(entry->sctpAssocRemAddrType));

    memset(&var_sctpAssocRemIPAddr, 0, sizeof(var_sctpAssocRemIPAddr));
    var_sctpAssocRemIPAddr.type = ASN_OCTET_STR;
    var_sctpAssocRemIPAddr.next_variable = &var_sctpAssocId;
    snmp_set_var_value(&var_sctpAssocRemIPAddr,
                       (u_char *) & entry->sctpAssocRemAddr,
                       entry->sctpAssocRemAddr_len);

    memset(&var_sctpAssocId, 0, sizeof(var_sctpAssocId));
    var_sctpAssocId.type = ASN_UNSIGNED;
    var_sctpAssocId.next_variable = NULL;
    snmp_set_var_value(&var_sctpAssocId, (u_char *) & entry->sctpAssocId,
                       sizeof(entry->sctpAssocId));

    /*
     * convert it 
     */
    err =
        build_oid_noalloc(entry->oid_index.oids, entry->oid_index.len,
                          &entry->oid_index.len, NULL, 0,
                          &var_sctpAssocRemIPAddrType);
    if (err)
        snmp_log(LOG_ERR, "error %d converting index to oid\n", err);

    /*
     * release any memory allocated during the conversion 
     */
    snmp_reset_var_buffers(&var_sctpAssocRemIPAddrType);

    return err;
}

void
sctpLookupRemIPAddrTable_entry_copy(sctpLookupRemIPAddrTable_entry * from,
                                    sctpLookupRemIPAddrTable_entry * to)
{
    memcpy(to, from, sizeof(sctpLookupRemIPAddrTable_entry));
    to->oid_index.oids = to->oid_tmp;
}


void
sctpLookupRemIPAddrTable_entry_free(sctpLookupRemIPAddrTable_entry * entry)
{
    SNMP_FREE(entry);
}

netsnmp_container *
sctpLookupRemIPAddrTable_get_container(void)
{
    return sctpLookupRemIPAddrTable_container;
}


static void
sctpLookupRemIPAddrTable_entry_clear(void *what, void *magic)
{
    sctpLookupRemIPAddrTable_entry_free(what);
}

void
sctpLookupRemIPAddrTable_container_clear(netsnmp_container *container)
{
    CONTAINER_CLEAR(container, sctpLookupRemIPAddrTable_entry_clear, NULL);
}
