#include "stdafx.h"

#include <assert.h>
#include <iostream>
#include <fstream>

#include "json/json.h"

#include "ConditionBuilder.h"
#include "allBaseConditionHeaders.h"
#include "alliFastConditionHeaders.h"

CConditionBuilder* CConditionBuilder::m_pInstance = NULL;

using namespace CND;

CConditionBuilder* CConditionBuilder::Instance()
{
    if (!m_pInstance)
	{   
		m_pInstance = new CConditionBuilder();
	}
		
    return m_pInstance;
}

CConditionObject* CConditionBuilder::GetCondition(long code, DString& strModuleName, DString& strLocale, DString& strClient, DString& strMarket, const DString& strDataFoldeerPath)
{
    CConditionObject* iFastIFastCondition = CreateIFastIFastConditionObject(code);
    if (NULL != iFastIFastCondition)
    {
        iFastIFastCondition->SetClientName(strClient);
        iFastIFastCondition->SetMarketName(strMarket);

        CheckForOverrides(iFastIFastCondition, strDataFoldeerPath);

        return iFastIFastCondition;
    }

    CConditionObject* iFastInfrastructureCondition = CreateIFastInfrastructureConditionObject(code);
    if (NULL != iFastInfrastructureCondition)
    {
        iFastInfrastructureCondition->SetClientName(strClient);
        iFastInfrastructureCondition->SetMarketName(strMarket);

        CheckForOverrides(iFastInfrastructureCondition, strDataFoldeerPath);

        return iFastInfrastructureCondition;
    }

    CConditionObject* baseIfdsCondition = CreateBaseIfdsConditionObject(code);
    if (NULL != baseIfdsCondition)
    {
        baseIfdsCondition->SetClientName(strClient);
        baseIfdsCondition->SetMarketName(strMarket);

        CheckForOverrides(baseIfdsCondition, strDataFoldeerPath);

        return baseIfdsCondition;
    }

    CConditionObject* baseInfrastructureCondition = CreateBaseInfrastructureConditionObject(code);
    if (NULL != baseInfrastructureCondition)
    {
        baseInfrastructureCondition->SetClientName(strClient);
        baseInfrastructureCondition->SetMarketName(strMarket);

        CheckForOverrides(baseInfrastructureCondition, strDataFoldeerPath);

        return baseInfrastructureCondition;
    }

    return NULL;
}

CConditionObject* CConditionBuilder::CreateBaseIfdsConditionObject(long conditionId) 
{
	CConditionObject* conditionObj = NULL;

	switch(conditionId)
	{
		case 1: /* BFBASE_CND_VERSION */
			conditionObj = new CBase_Ifds_bfbase_bfbase_cnd_version();
			break;
		case 2: /* ERR_FIELD_REQUIRED */
			conditionObj = new CBase_Ifds_bfbase_err_field_required();
			break;
		case 3: /* ERR_FIELD_REQUIRED_GUI */
			conditionObj = new CBase_Ifds_bfbase_err_field_required_gui();
			break;
		case 4: /* ERR_FIELD_VALUE_NOT_VALID */
			conditionObj = new CBase_Ifds_bfbase_err_field_value_not_valid();
			break;
		case 5: /* ERR_FIELD_VALUE_NOT_VALID_GUI */
			conditionObj = new CBase_Ifds_bfbase_err_field_value_not_valid_gui();
			break;
		case 6: /* ERR_INVALID_METHOD_CALL */
			conditionObj = new CBase_Ifds_bfbase_err_invalid_method_call();
			break;
		case 7: /* ERR_OBJ_REQUIRED */
			conditionObj = new CBase_Ifds_bfbase_err_obj_required();
			break;
		case 8: /* ERR_OBJ_REQUIRED_IN_LIST */
			conditionObj = new CBase_Ifds_bfbase_err_obj_required_in_list();
			break;
		case 9: /* ERR_UNKNOWN_EXCEPTION */
			conditionObj = new CBase_Ifds_bfbase_err_unknown_exception();
			break;
		case 100001: /* BFCONMGR_CND_VERSION */
			conditionObj = new CBase_Ifds_bfconmgr_bfconmgr_cnd_version();
			break;
		case 100002: /* ERR_HOST_CONNECTION_MGR_NOT_FOUND */
			conditionObj = new CBase_Ifds_bfconmgr_err_host_connection_mgr_not_found();
			break;
		case 100003: /* ERR_PRIVCONN_CONNECT_FAILED */
			conditionObj = new CBase_Ifds_bfconmgr_err_privconn_connect_failed();
			break;
		case 100005: /* ERR_PRIVCONN_DISCONNECT_FAILED */
			conditionObj = new CBase_Ifds_bfconmgr_err_privconn_disconnect_failed();
			break;
		case 100008: /* ERR_VM */
			conditionObj = new CBase_Ifds_bfconmgr_err_vm();
			break;
		case 100009: /* ERR_VMCONNECTION_CONNECT_FAILED */
			conditionObj = new CBase_Ifds_bfconmgr_err_vmconnection_connect_failed();
			break;
		case 100010: /* ERR_VMCONNECTION_CREATE_EVENT */
			conditionObj = new CBase_Ifds_bfconmgr_err_vmconnection_create_event();
			break;
		case 100011: /* ERR_VMCONNECTION_CREATE_FAILED */
			conditionObj = new CBase_Ifds_bfconmgr_err_vmconnection_create_failed();
			break;
		case 100012: /* ERR_VMCONNECTION_DISCONNECT_FAILED */
			conditionObj = new CBase_Ifds_bfconmgr_err_vmconnection_disconnect_failed();
			break;
		case 100013: /* ERR_VMCONNECTION_NOTIFY_FAILED */
			conditionObj = new CBase_Ifds_bfconmgr_err_vmconnection_notify_failed();
			break;
		case 100014: /* ERR_VMCONNECTION_REQUEST_FAILED */
			conditionObj = new CBase_Ifds_bfconmgr_err_vmconnection_request_failed();
			break;
		case 100015: /* ERR_VMCONNECTION_WAITEVENT_FAILED */
			conditionObj = new CBase_Ifds_bfconmgr_err_vmconnection_waitevent_failed();
			break;
		case 200001: /* BFDATA_CND_VERSION */
			conditionObj = new CBase_Ifds_bfdata_bfdata_cnd_version();
			break;
		case 200002: /* CND_BFDataFieldNotFoundException */
			conditionObj = new CBase_Ifds_bfdata_cnd_bfdatafieldnotfoundexception();
			break;
		case 200003: /* CND_BFDataFieldPropertiesException */
			conditionObj = new CBase_Ifds_bfdata_cnd_bfdatafieldpropertiesexception();
			break;
		case 200004: /* CND_BFDataIdOpException */
			conditionObj = new CBase_Ifds_bfdata_cnd_bfdataidopexception();
			break;
		case 200005: /* CND_BFDataIdUnknownException */
			conditionObj = new CBase_Ifds_bfdata_cnd_bfdataidunknownexception();
			break;
		case 200006: /* CND_BFDataInvalidOpException */
			conditionObj = new CBase_Ifds_bfdata_cnd_bfdatainvalidopexception();
			break;
		case 200007: /* CND_BFDataNotImplementedException */
			conditionObj = new CBase_Ifds_bfdata_cnd_bfdatanotimplementedexception();
			break;
		case 200008: /* CND_BFDataRepeatNotFoundException */
			conditionObj = new CBase_Ifds_bfdata_cnd_bfdatarepeatnotfoundexception();
			break;
		case 200009: /* CND_BFFieldIdOpException */
			conditionObj = new CBase_Ifds_bfdata_cnd_bffieldidopexception();
			break;
		case 200010: /* CND_BFFieldIdUnknownException */
			conditionObj = new CBase_Ifds_bfdata_cnd_bffieldidunknownexception();
			break;
		case 200011: /* CND_BFSubstitutionException */
			conditionObj = new CBase_Ifds_bfdata_cnd_bfsubstitutionexception();
			break;
		case 200012: /* CND_DigitOverflowException */
			conditionObj = new CBase_Ifds_bfdata_cnd_digitoverflowexception();
			break;
		case 200013: /* CND_InvalidCharacterException */
			conditionObj = new CBase_Ifds_bfdata_cnd_invalidcharacterexception();
			break;
		case 200014: /* CND_InvalidMaskException */
			conditionObj = new CBase_Ifds_bfdata_cnd_invalidmaskexception();
			break;
		case 300001: /* BFDBRKR_CND_VERSION */
			conditionObj = new CBase_Ifds_bfdbrkr_bfdbrkr_cnd_version();
			break;
		case 300004: /* ERR_MALFORMED_FILE_RESPONSE_BUFFER */
			conditionObj = new CBase_Ifds_bfdbrkr_err_malformed_file_response_buffer();
			break;
		case 300005: /* ERR_PRIVCONN_CREATE_EVENT */
			conditionObj = new CBase_Ifds_bfdbrkr_err_privconn_create_event();
			break;
		case 300006: /* ERR_PRIVCONN_CREATE_FAILED */
			conditionObj = new CBase_Ifds_bfdbrkr_err_privconn_create_failed();
			break;
		case 300008: /* ERR_PRIVCONN_NOTIFY_FAILED */
			conditionObj = new CBase_Ifds_bfdbrkr_err_privconn_notify_failed();
			break;
		case 300009: /* ERR_PRIVCONN_REQUEST_FAILED */
			conditionObj = new CBase_Ifds_bfdbrkr_err_privconn_request_failed();
			break;
		case 300010: /* ERR_PRIVCONN_WAITEVENT_FAILED */
			conditionObj = new CBase_Ifds_bfdbrkr_err_privconn_waitevent_failed();
			break;
		case 300012: /* MULTYBYTE_TO_UNICODE_CONVERSION_ERROR */
			conditionObj = new CBase_Ifds_bfdbrkr_multybyte_to_unicode_conversion_error();
			break;
		case 300013: /* UNICODE_TO_MULTYBYTE_CONVERSION_ERROR */
			conditionObj = new CBase_Ifds_bfdbrkr_unicode_to_multybyte_conversion_error();
			break;
		case 400001: /* BFUTIL_CND_VERSION */
			conditionObj = new CBase_Ifds_bfutil_bfutil_cnd_version();
			break;
		case 400002: /* BFUTIL_ENCODE_TO_CODEPAGE_FAILURE */
			conditionObj = new CBase_Ifds_bfutil_bfutil_encode_to_codepage_failure();
			break;
		case 400003: /* BFUTIL_NO_HOST_CODEPAGE */
			conditionObj = new CBase_Ifds_bfutil_bfutil_no_host_codepage();
			break;
		case 400004: /* BFUTILERR_UnsupportedLocaleException */
			conditionObj = new CBase_Ifds_bfutil_bfutilerr_unsupportedlocaleexception();
			break;
		case 500001: /* BP_ERR_CANNOT_SET_CBO */
			conditionObj = new CBase_Ifds_bpbase_bp_err_cannot_set_cbo();
			break;
		case 500002: /* BP_ERR_CBO_NOT_SET */
			conditionObj = new CBase_Ifds_bpbase_bp_err_cbo_not_set();
			break;
		case 500003: /* BP_ERR_COMMAND_NOT_FOUND */
			conditionObj = new CBase_Ifds_bpbase_bp_err_command_not_found();
			break;
		case 500004: /* BP_ERR_COULD_NOT_GET_SUBSESSION */
			conditionObj = new CBase_Ifds_bpbase_bp_err_could_not_get_subsession();
			break;
		case 500005: /* BP_ERR_DUPLICATE_DISPATCHER */
			conditionObj = new CBase_Ifds_bpbase_bp_err_duplicate_dispatcher();
			break;
		case 500006: /* BP_ERR_DUPLICATE_KEY_IN_FIELD_DETAILS */
			conditionObj = new CBase_Ifds_bpbase_bp_err_duplicate_key_in_field_details();
			break;
		case 500007: /* BP_ERR_FIELD_DEFINED_IN_LIST_AND_CBO */
			conditionObj = new CBase_Ifds_bpbase_bp_err_field_defined_in_list_and_cbo();
			break;
		case 500008: /* BP_ERR_FIELD_NOT_FOUND */
			conditionObj = new CBase_Ifds_bpbase_bp_err_field_not_found();
			break;
		case 500009: /* BP_ERR_GETFIELD_FAILED */
			conditionObj = new CBase_Ifds_bpbase_bp_err_getfield_failed();
			break;
		case 500010: /* BP_ERR_ID_OUT_OF_RANGE */
			conditionObj = new CBase_Ifds_bpbase_bp_err_id_out_of_range();
			break;
		case 500011: /* BP_ERR_ID_OUT_OF_RANGE_FOR_FIELD */
			conditionObj = new CBase_Ifds_bpbase_bp_err_id_out_of_range_for_field();
			break;
		case 500012: /* BP_ERR_INVALID_METHOD_CALL */
			conditionObj = new CBase_Ifds_bpbase_bp_err_invalid_method_call();
			break;
		case 500013: /* BP_ERR_ITEM_NOT_VALID */
			conditionObj = new CBase_Ifds_bpbase_bp_err_item_not_valid();
			break;
		case 500014: /* BP_ERR_LIST_NOT_FOUND */
			conditionObj = new CBase_Ifds_bpbase_bp_err_list_not_found();
			break;
		case 500015: /* BP_ERR_LIST_NOT_VALID */
			conditionObj = new CBase_Ifds_bpbase_bp_err_list_not_valid();
			break;
		case 500016: /* BP_ERR_MUST_RUN_MODAL */
			conditionObj = new CBase_Ifds_bpbase_bp_err_must_run_modal();
			break;
		case 500017: /* BP_ERR_MUST_RUN_MODELESS */
			conditionObj = new CBase_Ifds_bpbase_bp_err_must_run_modeless();
			break;
		case 500018: /* BP_ERR_NO_DATA_AREA */
			conditionObj = new CBase_Ifds_bpbase_bp_err_no_data_area();
			break;
		case 500019: /* BP_ERR_NO_FIELD_MATCH */
			conditionObj = new CBase_Ifds_bpbase_bp_err_no_field_match();
			break;
		case 500020: /* BP_ERR_NO_PARENT_EXISTS */
			conditionObj = new CBase_Ifds_bpbase_bp_err_no_parent_exists();
			break;
		case 500021: /* BP_ERR_SEH_EXCEPTION */
			conditionObj = new CBase_Ifds_bpbase_bp_err_seh_exception();
			break;
		case 500022: /* BP_ERR_SETFIELD_FAILED */
			conditionObj = new CBase_Ifds_bpbase_bp_err_setfield_failed();
			break;
		case 500023: /* BP_ERR_UNKNOWN_EXCEPTION */
			conditionObj = new CBase_Ifds_bpbase_bp_err_unknown_exception();
			break;
		case 500024: /* BP_ERR_USER_CHANGE_PASSWORD */
			conditionObj = new CBase_Ifds_bpbase_bp_err_user_change_password();
			break;
		case 500025: /* BP_NO_OF_DAYS_PRIOR_TO_CHANGE_PASSWORD */
			conditionObj = new CBase_Ifds_bpbase_bp_no_of_days_prior_to_change_password();
			break;
		case 500026: /* BPBASE_CND_VERSION */
			conditionObj = new CBase_Ifds_bpbase_bpbase_cnd_version();
			break;
		case 600001: /* DIAWD23_AWD_EXCEPTION */
			conditionObj = new CBase_Ifds_diawd23_diawd23_awd_exception();
			break;
		case 600004: /* DIAWD23_CONTAINER_ALREADY_OPEN */
			conditionObj = new CBase_Ifds_diawd23_diawd23_container_already_open();
			break;
		case 600005: /* DIAWD23_CONTAINER_CLOSE_FAIL */
			conditionObj = new CBase_Ifds_diawd23_diawd23_container_close_fail();
			break;
		case 600006: /* DIAWD23_CONTAINER_NOT_CLEAR */
			conditionObj = new CBase_Ifds_diawd23_diawd23_container_not_clear();
			break;
		case 600007: /* DIAWD23_CONTAINER_NOT_OPEN */
			conditionObj = new CBase_Ifds_diawd23_diawd23_container_not_open();
			break;
		case 600008: /* DIAWD23_CONTAINER_OPEN_FAIL */
			conditionObj = new CBase_Ifds_diawd23_diawd23_container_open_fail();
			break;
		case 600010: /* DIAWD23_CREATE_AWDSRC_FAIL */
			conditionObj = new CBase_Ifds_diawd23_diawd23_create_awdsrc_fail();
			break;
		case 600019: /* DIAWD23_UNKNOWN_AWD_EXCEPTION */
			conditionObj = new CBase_Ifds_diawd23_diawd23_unknown_awd_exception();
			break;
		case 700002: /* DIAWDI_LOAD_MODULE_FAIL */
			conditionObj = new CBase_Ifds_diawdi_diawdi_load_module_fail();
			break;
		case 700003: /* DIAWDI_LOAD_PROC_FAIL */
			conditionObj = new CBase_Ifds_diawdi_diawdi_load_proc_fail();
			break;
		case 700004: /* DIAWDI_LOGON_INVALID_NEW_PASSWORD */
			conditionObj = new CBase_Ifds_diawdi_diawdi_logon_invalid_new_password();
			break;
		case 700005: /* DIAWDI_LOGON_INVALID_OPID */
			conditionObj = new CBase_Ifds_diawdi_diawdi_logon_invalid_opid();
			break;
		case 700006: /* DIAWDI_LOGON_INVALID_PASSWORD */
			conditionObj = new CBase_Ifds_diawdi_diawdi_logon_invalid_password();
			break;
		case 700007: /* DIAWDI_LOGON_NEW_PASSWORD_SAMEAS_OLD */
			conditionObj = new CBase_Ifds_diawdi_diawdi_logon_new_password_sameas_old();
			break;
		case 700008: /* DIAWDI_LOGON_NO_ERROR */
			conditionObj = new CBase_Ifds_diawdi_diawdi_logon_no_error();
			break;
		case 700009: /* DIAWDI_LOGON_OTHER_ERROR */
			conditionObj = new CBase_Ifds_diawdi_diawdi_logon_other_error();
			break;
		case 700010: /* DIAWDI_LOGON_PASSWORD_EXPIRED */
			conditionObj = new CBase_Ifds_diawdi_diawdi_logon_password_expired();
			break;
		case 700011: /* DIAWDI_LOGON_USER_ALREADY_LOGGED_ON */
			conditionObj = new CBase_Ifds_diawdi_diawdi_logon_user_already_logged_on();
			break;
		case 700012: /* DIAWDI_LOGON_USER_DISABLED */
			conditionObj = new CBase_Ifds_diawdi_diawdi_logon_user_disabled();
			break;
		case 800003: /* ERR_CBE_LABEL_INVALID_FOR_UPDATE */
			conditionObj = new CBase_Ifds_dicbocore_err_cbe_label_invalid_for_update();
			break;
		case 800010: /* ERR_FIELD_MAX_LEN_EXCEEDED */
			conditionObj = new CBase_Ifds_dicbocore_err_field_max_len_exceeded();
			break;
		case 800011: /* ERR_FIELD_READ_ONLY */
			conditionObj = new CBase_Ifds_dicbocore_err_field_read_only();
			break;
		case 800014: /* ERR_FLD_NOT_VALIDATED */
			conditionObj = new CBase_Ifds_dicbocore_err_fld_not_validated();
			break;
		case 800015: /* ERR_FORMAT_NOT_RECOGNIZED */
			conditionObj = new CBase_Ifds_dicbocore_err_format_not_recognized();
			break;
		case 800016: /* ERR_HOLIDAY_FILE */
			conditionObj = new CBase_Ifds_dicbocore_err_holiday_file();
			break;
		case 800019: /* ERR_INDEX_OUT_OF_RANGE */
			conditionObj = new CBase_Ifds_dicbocore_err_index_out_of_range();
			break;
		case 800021: /* ERR_INVALID_FIELD_ID */
			conditionObj = new CBase_Ifds_dicbocore_err_invalid_field_id();
			break;
		case 800022: /* ERR_INVALID_FIELD_TAG */
			conditionObj = new CBase_Ifds_dicbocore_err_invalid_field_tag();
			break;
		case 800023: /* ERR_INVALID_FIELD_TYPE */
			conditionObj = new CBase_Ifds_dicbocore_err_invalid_field_type();
			break;
		case 800026: /* ERR_INVALID_OBJ_POINTER */
			conditionObj = new CBase_Ifds_dicbocore_err_invalid_obj_pointer();
			break;
		case 800027: /* ERR_INVALID_TIME */
			conditionObj = new CBase_Ifds_dicbocore_err_invalid_time();
			break;
		case 800030: /* ERR_MFDATE_INVALID */
			conditionObj = new CBase_Ifds_dicbocore_err_mfdate_invalid();
			break;
		case 800035: /* ERR_NO_REGISTERED_OBJECT */
			conditionObj = new CBase_Ifds_dicbocore_err_no_registered_object();
			break;
		case 800036: /* ERR_NO_UPDATES_TO_APPLY */
			conditionObj = new CBase_Ifds_dicbocore_err_no_updates_to_apply();
			break;
		case 800037: /* ERR_NO_VIEW_DATA_OBJECTS_REGISTERED */
			conditionObj = new CBase_Ifds_dicbocore_err_no_view_data_objects_registered();
			break;
		case 800038: /* ERR_NO_VIEW_DATA_REPEATS */
			conditionObj = new CBase_Ifds_dicbocore_err_no_view_data_repeats();
			break;
		case 800047: /* ERR_OBJECT_PTR_ACCESS_ONLY */
			conditionObj = new CBase_Ifds_dicbocore_err_object_ptr_access_only();
			break;
		case 800048: /* ERR_OBJECT_READ_ONLY */
			conditionObj = new CBase_Ifds_dicbocore_err_object_read_only();
			break;
		case 800050: /* ERR_RETREIVING_DATE */
			conditionObj = new CBase_Ifds_dicbocore_err_retreiving_date();
			break;
		case 800052: /* ERR_STRING_EXCEPTION */
			conditionObj = new CBase_Ifds_dicbocore_err_string_exception();
			break;
		case 800053: /* ERR_UNABLE_TO_RETRIEVE_LABEL_DATA */
			conditionObj = new CBase_Ifds_dicbocore_err_unable_to_retrieve_label_data();
			break;
		case 800055: /* ERR_VIEW_MGR */
			conditionObj = new CBase_Ifds_dicbocore_err_view_mgr();
			break;
		case 800056: /* ERR_WORKORDER_CBE_ALREADY_REGISTERED */
			conditionObj = new CBase_Ifds_dicbocore_err_workorder_cbe_already_registered();
			break;
		case 800057: /* ERR_WORKORDER_CBEKEY_DUPLICATED */
			conditionObj = new CBase_Ifds_dicbocore_err_workorder_cbekey_duplicated();
			break;
		case 800058: /* ERR_WORKORDER_CBEKEY_NOT_FOUND */
			conditionObj = new CBase_Ifds_dicbocore_err_workorder_cbekey_not_found();
			break;
		case 900001: /* BASE_ALLOC_FAIL */
			conditionObj = new CBase_Ifds_dicore_base_alloc_fail();
			break;
		case 900004: /* DICORE_CANNOT_PERSIST_UNDEFINED_MGR */
			conditionObj = new CBase_Ifds_dicore_dicore_cannot_persist_undefined_mgr();
			break;
		case 900005: /* DICORE_CANNOT_READ_DEFINITION */
			conditionObj = new CBase_Ifds_dicore_dicore_cannot_read_definition();
			break;
		case 900006: /* DICORE_DATAPATH_ENV_NOT_DEFINED */
			conditionObj = new CBase_Ifds_dicore_dicore_datapath_env_not_defined();
			break;
		case 900007: /* DICORE_DATAPATH_REG_NOT_DEFINED */
			conditionObj = new CBase_Ifds_dicore_dicore_datapath_reg_not_defined();
			break;
		case 900012: /* DICORE_DLL_LOAD_FAIL */
			conditionObj = new CBase_Ifds_dicore_dicore_dll_load_fail();
			break;
		case 900013: /* DICORE_EVENTSEM_CREATE_FAIL */
			conditionObj = new CBase_Ifds_dicore_dicore_eventsem_create_fail();
			break;
		case 900014: /* DICORE_EVENTSEM_OPEN_FAIL */
			conditionObj = new CBase_Ifds_dicore_dicore_eventsem_open_fail();
			break;
		case 900018: /* DICORE_FUNCTION_LOAD_FAIL */
			conditionObj = new CBase_Ifds_dicore_dicore_function_load_fail();
			break;
		case 900022: /* DICORE_LOCATION_NOT_DEFINED */
			conditionObj = new CBase_Ifds_dicore_dicore_location_not_defined();
			break;
		case 900027: /* DICORE_OPEN_INI_FILE_FAIL */
			conditionObj = new CBase_Ifds_dicore_dicore_open_ini_file_fail();
			break;
		case 900033: /* DICORE_PERSIST_REGISTRY_FAIL */
			conditionObj = new CBase_Ifds_dicore_dicore_persist_registry_fail();
			break;
		case 900036: /* DICORE_PROFILE_ALREAD_EXISTS */
			conditionObj = new CBase_Ifds_dicore_dicore_profile_alread_exists();
			break;
		case 900037: /* DICORE_READ_REGISTRY_FAIL */
			conditionObj = new CBase_Ifds_dicore_dicore_read_registry_fail();
			break;
		case 900053: /* DILOCAL_JNI_EXCEPTION_CREATEJVM */
			conditionObj = new CBase_Ifds_dicore_dilocal_jni_exception_createjvm();
			break;
		case 900054: /* DILOCAL_JNI_EXCEPTION_EXECUTE */
			conditionObj = new CBase_Ifds_dicore_dilocal_jni_exception_execute();
			break;
		case 900055: /* DILOCAL_JNI_EXCEPTION_LOCATE */
			conditionObj = new CBase_Ifds_dicore_dilocal_jni_exception_locate();
			break;
		case 900058: /* VIRTUAL_BASE_METHOD_NOT_SUPPORTED */
			conditionObj = new CBase_Ifds_dicore_virtual_base_method_not_supported();
			break;
		case 1000001: /* DIDBRKR_BAD_FORMAT_IN_STREAM_FILE */
			conditionObj = new CBase_Ifds_didbrkr_didbrkr_bad_format_in_stream_file();
			break;
		case 1000002: /* DIDBRKR_CANNOT_ASSIGN_DATA_OBJECTS */
			conditionObj = new CBase_Ifds_didbrkr_didbrkr_cannot_assign_data_objects();
			break;
		case 1000003: /* DIDBRKR_CANNOT_ASSIGN_DATAELEMENT_OBJECTS */
			conditionObj = new CBase_Ifds_didbrkr_didbrkr_cannot_assign_dataelement_objects();
			break;
		case 1000004: /* DIDBRKR_CANT_OPEN_PROPERTIES_FILE */
			conditionObj = new CBase_Ifds_didbrkr_didbrkr_cant_open_properties_file();
			break;
		case 1000005: /* DIDBRKR_CANT_SET_VALUES */
			conditionObj = new CBase_Ifds_didbrkr_didbrkr_cant_set_values();
			break;
		case 1000006: /* DIDBRKR_COMPONENT_NOT_FOUND */
			conditionObj = new CBase_Ifds_didbrkr_didbrkr_component_not_found();
			break;
		case 1000007: /* DIDBRKR_DATA_HAS_NO_REPEATS */
			conditionObj = new CBase_Ifds_didbrkr_didbrkr_data_has_no_repeats();
			break;
		case 1000008: /* DIDBRKR_DATASET_NOT_FOUND */
			conditionObj = new CBase_Ifds_didbrkr_didbrkr_dataset_not_found();
			break;
		case 1000009: /* DIDBRKR_DUPLICATE_PROPERTIES */
			conditionObj = new CBase_Ifds_didbrkr_didbrkr_duplicate_properties();
			break;
		case 1000010: /* DIDBRKR_ELEMENT_NOT_FOUND */
			conditionObj = new CBase_Ifds_didbrkr_didbrkr_element_not_found();
			break;
		case 1000011: /* DIDBRKR_ERROR_READING_STREAM_FILE */
			conditionObj = new CBase_Ifds_didbrkr_didbrkr_error_reading_stream_file();
			break;
		case 1000012: /* DIDBRKR_EXTRA_LINES_IN_PROPERTIES_FILE */
			conditionObj = new CBase_Ifds_didbrkr_didbrkr_extra_lines_in_properties_file();
			break;
		case 1000013: /* DIDBRKR_FILE_SEEK_FAILED */
			conditionObj = new CBase_Ifds_didbrkr_didbrkr_file_seek_failed();
			break;
		case 1000014: /* DIDBRKR_I18N_MASK_FORMAT_ERROR */
			conditionObj = new CBase_Ifds_didbrkr_didbrkr_i18n_mask_format_error();
			break;
		case 1000015: /* DIDBRKR_INDEX_OUT_OF_RANGE */
			conditionObj = new CBase_Ifds_didbrkr_didbrkr_index_out_of_range();
			break;
		case 1000016: /* DIDBRKR_INVALID_LINE_LENGTH */
			conditionObj = new CBase_Ifds_didbrkr_didbrkr_invalid_line_length();
			break;
		case 1000017: /* DIDBRKR_INVALID_PROPERTY_POINTER */
			conditionObj = new CBase_Ifds_didbrkr_didbrkr_invalid_property_pointer();
			break;
		case 1000018: /* DIDBRKR_INVALID_REDEFINE */
			conditionObj = new CBase_Ifds_didbrkr_didbrkr_invalid_redefine();
			break;
		case 1000019: /* DIDBRKR_KEY_NOT_FOUND */
			conditionObj = new CBase_Ifds_didbrkr_didbrkr_key_not_found();
			break;
		case 1000020: /* DIDBRKR_LOCALE_NOT_FOUND */
			conditionObj = new CBase_Ifds_didbrkr_didbrkr_locale_not_found();
			break;
		case 1000021: /* DIDBRKR_NO_PATH_TO_PROPERTIES_FILE */
			conditionObj = new CBase_Ifds_didbrkr_didbrkr_no_path_to_properties_file();
			break;
		case 1000022: /* DIDBRKR_NOT_A_DATA_OBJECT */
			conditionObj = new CBase_Ifds_didbrkr_didbrkr_not_a_data_object();
			break;
		case 1000023: /* DIDBRKR_NOT_A_DATAELEMENT_OBJECT */
			conditionObj = new CBase_Ifds_didbrkr_didbrkr_not_a_dataelement_object();
			break;
		case 1000024: /* DIDBRKR_NOT_REPEATABLE */
			conditionObj = new CBase_Ifds_didbrkr_didbrkr_not_repeatable();
			break;
		case 1000025: /* DIDBRKR_PROPERTIES_DONT_MATCH */
			conditionObj = new CBase_Ifds_didbrkr_didbrkr_properties_dont_match();
			break;
		case 1000026: /* DIDBRKR_PROPERTY_DOES_NOT_EXIST */
			conditionObj = new CBase_Ifds_didbrkr_didbrkr_property_does_not_exist();
			break;
		case 1000027: /* DIDBRKR_PROPERTY_DOES_NOT_EXIST_AT_INDEX */
			conditionObj = new CBase_Ifds_didbrkr_didbrkr_property_does_not_exist_at_index();
			break;
		case 1000029: /* DIDBRKR_REDEFINE_HAS_DUPLICATE */
			conditionObj = new CBase_Ifds_didbrkr_didbrkr_redefine_has_duplicate();
			break;
		case 1000032: /* DIDBRKR_REPEAT_COUNT_ELEMENT_NOT_FOUND */
			conditionObj = new CBase_Ifds_didbrkr_didbrkr_repeat_count_element_not_found();
			break;
		case 1000033: /* DIDBRKR_REPEAT_INDEX_OUT_OF_RANGE */
			conditionObj = new CBase_Ifds_didbrkr_didbrkr_repeat_index_out_of_range();
			break;
		case 1000035: /* DIDBRKR_UNEXPECTED_END_OF_STREAM_FILE */
			conditionObj = new CBase_Ifds_didbrkr_didbrkr_unexpected_end_of_stream_file();
			break;
		case 1100001: /* DIODBC_CONNECT_ERROR */
			conditionObj = new CBase_Ifds_disessn_diodbc_connect_error();
			break;
		case 1100003: /* DIODBC_INFO */
			conditionObj = new CBase_Ifds_disessn_diodbc_info();
			break;
		case 1200004: /* DITA2KDB_A58_REC_NOT_FOUND */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_a58_rec_not_found();
			break;
		case 1200012: /* DITA2KDB_AUDIT_FILE_BAD_OPEN */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_audit_file_bad_open();
			break;
		case 1200013: /* DITA2KDB_AUDIT_REC_NOT_WRITTEN */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_audit_rec_not_written();
			break;
		case 1200015: /* DITA2KDB_B06_REC_NOT_FOUND */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_b06_rec_not_found();
			break;
		case 1200026: /* DITA2KDB_CHANGED_BY_DIFF_OPER */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_changed_by_diff_oper();
			break;
		case 1200027: /* DITA2KDB_CHG_REC_NOT_FOUND */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_chg_rec_not_found();
			break;
		case 1200028: /* DITA2KDB_CURR_A79_NOT_DEL */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_curr_a79_not_del();
			break;
		case 1200029: /* DITA2KDB_DATA_NOT_FOUND */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_data_not_found();
			break;
		case 1200031: /* DITA2KDB_DEL_REC_NOT_FOUND */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_del_rec_not_found();
			break;
		case 1200033: /* DITA2KDB_END_OF_DATA */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_end_of_data();
			break;
		case 1200034: /* DITA2KDB_F16_REC_NOT_FOUND */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_f16_rec_not_found();
			break;
		case 1200035: /* DITA2KDB_F17_REC_NOT_FOUND */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_f17_rec_not_found();
			break;
		case 1200038: /* DITA2KDB_INVALID_ACCT_NUM */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_acct_num();
			break;
		case 1200039: /* DITA2KDB_INVALID_ACCUM_YEARS */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_accum_years();
			break;
		case 1200040: /* DITA2KDB_INVALID_ALPHA_CODE */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_alpha_code();
			break;
		case 1200041: /* DITA2KDB_INVALID_ARRAY_ROWS */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_array_rows();
			break;
		case 1200042: /* DITA2KDB_INVALID_BANK_MICR_ID */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_bank_micr_id();
			break;
		case 1200043: /* DITA2KDB_INVALID_BATCH_NUM */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_batch_num();
			break;
		case 1200045: /* DITA2KDB_INVALID_CERT_NUM */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_cert_num();
			break;
		case 1200050: /* DITA2KDB_INVALID_DATA_REQUEST */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_data_request();
			break;
		case 1200051: /* DITA2KDB_INVALID_DATE */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_date();
			break;
		case 1200053: /* DITA2KDB_INVALID_DEALER_BRANCH */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_dealer_branch();
			break;
		case 1200054: /* DITA2KDB_INVALID_DEALER_NUM */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_dealer_num();
			break;
		case 1200055: /* DITA2KDB_INVALID_DEBIT_CARD */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_debit_card();
			break;
		case 1200056: /* DITA2KDB_INVALID_DEBIT_TYPE */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_debit_type();
			break;
		case 1200057: /* DITA2KDB_INVALID_DLR_BR_SUMMARY */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_dlr_br_summary();
			break;
		case 1200058: /* DITA2KDB_INVALID_DLR_BRN_SEC */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_dlr_brn_sec();
			break;
		case 1200059: /* DITA2KDB_INVALID_DLR_SUMMARY */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_dlr_summary();
			break;
		case 1200060: /* DITA2KDB_INVALID_DSCS_APPREC */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_dscs_apprec();
			break;
		case 1200061: /* DITA2KDB_INVALID_EXCH_PUR_CANC */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_exch_pur_canc();
			break;
		case 1200062: /* DITA2KDB_INVALID_EXCH_RED_CANC */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_exch_red_canc();
			break;
		case 1200064: /* DITA2KDB_INVALID_FID_ACCOUNT */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_fid_account();
			break;
		case 1200065: /* DITA2KDB_INVALID_FRONT_END */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_front_end();
			break;
		case 1200067: /* DITA2KDB_INVALID_FUND_CODE */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_fund_code();
			break;
		case 1200071: /* DITA2KDB_INVALID_LOI_NUM */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_loi_num();
			break;
		case 1200074: /* DITA2KDB_INVALID_MONTHLY_ACCUM */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_monthly_accum();
			break;
		case 1200075: /* DITA2KDB_INVALID_NET_CHG */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_net_chg();
			break;
		case 1200077: /* DITA2KDB_INVALID_PAF_BUCKET */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_paf_bucket();
			break;
		case 1200079: /* DITA2KDB_INVALID_PRE_AGREEMENT */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_pre_agreement();
			break;
		case 1200080: /* DITA2KDB_INVALID_PRICE */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_price();
			break;
		case 1200081: /* DITA2KDB_INVALID_PST_AGREEMENT */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_pst_agreement();
			break;
		case 1200082: /* DITA2KDB_INVALID_PURCH_CANCEL */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_purch_cancel();
			break;
		case 1200084: /* DITA2KDB_INVALID_REDMPT_CANCEL */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_redmpt_cancel();
			break;
		case 1200085: /* DITA2KDB_INVALID_REIN_DOLLAR */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_rein_dollar();
			break;
		case 1200086: /* DITA2KDB_INVALID_REIN_SHARES */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_rein_shares();
			break;
		case 1200087: /* DITA2KDB_INVALID_REQUEST_CNT */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_request_cnt();
			break;
		case 1200088: /* DITA2KDB_INVALID_RES_STATE_CODE */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_res_state_code();
			break;
		case 1200090: /* DITA2KDB_INVALID_START_MONTH */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_start_month();
			break;
		case 1200091: /* DITA2KDB_INVALID_START_YEAR */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_start_year();
			break;
		case 1200092: /* DITA2KDB_INVALID_TAX_ID_NUM */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_tax_id_num();
			break;
		case 1200093: /* DITA2KDB_INVALID_TRANS_NUM */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_trans_num();
			break;
		case 1200094: /* DITA2KDB_INVALID_VIEW */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_view();
			break;
		case 1200095: /* DITA2KDB_INVALID_YIELD_DATE */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_invalid_yield_date();
			break;
		case 1200096: /* DITA2KDB_MAX_IO_LIMIT */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_max_io_limit();
			break;
		case 1200097: /* DITA2KDB_MGMT_CO_NOT_FOUND */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_mgmt_co_not_found();
			break;
		case 1200099: /* DITA2KDB_NO_A53_DUMMY_REC */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_no_a53_dummy_rec();
			break;
		case 1200100: /* DITA2KDB_NO_A53_FOR_VERIFY_DTE */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_no_a53_for_verify_dte();
			break;
		case 1200101: /* DITA2KDB_NO_A56_REC_FOUND */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_no_a56_rec_found();
			break;
		case 1200102: /* DITA2KDB_NO_A79_FOR_VERIFY_DTE */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_no_a79_for_verify_dte();
			break;
		case 1200106: /* DITA2KDB_NO_UPDATE_DETECTED */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_no_update_detected();
			break;
		case 1200107: /* DITA2KDB_NO_UPDATES_TO_APPLY */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_no_updates_to_apply();
			break;
		case 1200111: /* DITA2KDB_OPER_NOT_AUTH_DEALER */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_oper_not_auth_dealer();
			break;
		case 1200112: /* DITA2KDB_OPER_NOT_AUTH_DLR_BR */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_oper_not_auth_dlr_br();
			break;
		case 1200116: /* DITA2KDB_RECORD_ALREADY_EXIST */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_record_already_exist();
			break;
		case 1200123: /* DITA2KDB_S0_MASTER_NOT_FOUND */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_s0_master_not_found();
			break;
		case 1200125: /* DITA2KDB_STS_ERROR */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_sts_error();
			break;
		case 1200126: /* DITA2KDB_SYSTEM_DOWN */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_system_down();
			break;
		case 1200127: /* DITA2KDB_SYSTEM_ID_ERROR */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_system_id_error();
			break;
		case 1200132: /* DITA2KDB_TAF_NOT_EQUAL_MASTER */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_taf_not_equal_master();
			break;
		case 1200137: /* DITA2KDB_UPDATES_MFL_ONLY */
			conditionObj = new CBase_Ifds_dita2kdb_dita2kdb_updates_mfl_only();
			break;
		case 1400001: /* GUI_CND_VERSION */
			conditionObj = new CBase_Ifds_gui_gui_cnd_version();
			break;
		case 1400002: /* GUI_ENCORR_ALREADY_ACTIVE */
			conditionObj = new CBase_Ifds_gui_gui_encorr_already_active();
			break;
		case 1400003: /* GUI_ENCORR_ERROR_MALLOC */
			conditionObj = new CBase_Ifds_gui_gui_encorr_error_malloc();
			break;
		case 1400004: /* GUI_ENCORR_OLE_ERROR */
			conditionObj = new CBase_Ifds_gui_gui_encorr_ole_error();
			break;
		case 1400005: /* GUI_ERR_COMMAND_NOT_FOUND */
			conditionObj = new CBase_Ifds_gui_gui_err_command_not_found();
			break;
		case 1400006: /* GUI_ERR_DIALOG_CREATE_FAILED */
			conditionObj = new CBase_Ifds_gui_gui_err_dialog_create_failed();
			break;
		case 1400007: /* GUI_ERR_DOMODAL_FAILED */
			conditionObj = new CBase_Ifds_gui_gui_err_domodal_failed();
			break;
		case 1400008: /* GUI_ERR_UNKNOWN_EXCEPTION */
			conditionObj = new CBase_Ifds_gui_gui_err_unknown_exception();
			break;
		case 2100001: /* ERR_MAXIMUM_CONNECTIONS */
			conditionObj = new CBase_Ifds_srvbase_err_maximum_connections();
			break;
		case 2100002: /* SRVBASE_CND_VERSION */
			conditionObj = new CBase_Ifds_srvbase_srvbase_cnd_version();
			break;
		case 2300001: /* ERR_CBO_NOT_DEFINED */
			conditionObj = new CBase_Ifds_xparser_err_cbo_not_defined();
			break;
		case 2300002: /* ERR_CBO_NOT_FOUND_FOR_KEY */
			conditionObj = new CBase_Ifds_xparser_err_cbo_not_found_for_key();
			break;
		case 2300003: /* ERR_CREATE_PARSER */
			conditionObj = new CBase_Ifds_xparser_err_create_parser();
			break;
		case 2300004: /* ERR_DELETE_PARSER */
			conditionObj = new CBase_Ifds_xparser_err_delete_parser();
			break;
		case 2300005: /* ERR_ELEMENT_CANNOT_CONTAIN_CLASS */
			conditionObj = new CBase_Ifds_xparser_err_element_cannot_contain_class();
			break;
		case 2300006: /* ERR_ELEMENT_CLASS_ATTRIBUTE_NOT_SPECIFIED */
			conditionObj = new CBase_Ifds_xparser_err_element_class_attribute_not_specified();
			break;
		case 2300007: /* ERR_FIELD_NOT_DEFINED */
			conditionObj = new CBase_Ifds_xparser_err_field_not_defined();
			break;
		case 2300008: /* ERR_FIELDDETAILS_TAG */
			conditionObj = new CBase_Ifds_xparser_err_fielddetails_tag();
			break;
		case 2300009: /* ERR_INVALID_BOOLEAN_ATTRIBUTE */
			conditionObj = new CBase_Ifds_xparser_err_invalid_boolean_attribute();
			break;
		case 2300010: /* ERR_INVALID_CACHE_ATTRIBUTE */
			conditionObj = new CBase_Ifds_xparser_err_invalid_cache_attribute();
			break;
		case 2300011: /* ERR_INVALID_CBO_ACTION_ATTRIBUTE */
			conditionObj = new CBase_Ifds_xparser_err_invalid_cbo_action_attribute();
			break;
		case 2300012: /* ERR_INVALID_ELEMENT_CLASS_ATTRIBUTE */
			conditionObj = new CBase_Ifds_xparser_err_invalid_element_class_attribute();
			break;
		case 2300013: /* ERR_INVALID_PROCESS_ACTION_ATTRIBUTE */
			conditionObj = new CBase_Ifds_xparser_err_invalid_process_action_attribute();
			break;
		case 2300014: /* ERR_INVALID_RECORD_COUNT_ATTRIBUTE */
			conditionObj = new CBase_Ifds_xparser_err_invalid_record_count_attribute();
			break;
		case 2300015: /* ERR_INVALID_ROOT_ELEMENT_NAME */
			conditionObj = new CBase_Ifds_xparser_err_invalid_root_element_name();
			break;
		case 2300016: /* ERR_KEY_NOT_SPECIFIED_FOR_LIST */
			conditionObj = new CBase_Ifds_xparser_err_key_not_specified_for_list();
			break;
		case 2300017: /* ERR_KEY_SPECIFIED_FOR_NONLIST */
			conditionObj = new CBase_Ifds_xparser_err_key_specified_for_nonlist();
			break;
		case 2300018: /* ERR_MULTIPLE_KEYS_NOT_ALLOWED */
			conditionObj = new CBase_Ifds_xparser_err_multiple_keys_not_allowed();
			break;
		case 2300019: /* ERR_NEGATIVE_RECORD_COUNT_ATTRIBUTE */
			conditionObj = new CBase_Ifds_xparser_err_negative_record_count_attribute();
			break;
		case 2300020: /* ERR_NO_ACTION_TYPE */
			conditionObj = new CBase_Ifds_xparser_err_no_action_type();
			break;
		case 2300021: /* ERR_NO_REQUEST_NAME */
			conditionObj = new CBase_Ifds_xparser_err_no_request_name();
			break;
		case 2300022: /* ERR_NO_SUCH_ELEMENT */
			conditionObj = new CBase_Ifds_xparser_err_no_such_element();
			break;
		case 2300023: /* ERR_TOO_MANY_CNTID_TAGS */
			conditionObj = new CBase_Ifds_xparser_err_too_many_cntid_tags();
			break;
		case 2300024: /* ERR_TOO_MANY_FIELDKEY_TAGS */
			conditionObj = new CBase_Ifds_xparser_err_too_many_fieldkey_tags();
			break;
		case 2300025: /* ERR_TOO_MANY_USID_TAGS */
			conditionObj = new CBase_Ifds_xparser_err_too_many_usid_tags();
			break;
		case 2300026: /* ERR_TOO_MANY_WKSID_TAGS */
			conditionObj = new CBase_Ifds_xparser_err_too_many_wksid_tags();
			break;
		case 2300027: /* XP_REQUEST_UNPARSABLE */
			conditionObj = new CBase_Ifds_xparser_xp_request_unparsable();
			break;
		case 2300028: /* XP_SAX_PARSE_EXCEPTION */
			conditionObj = new CBase_Ifds_xparser_xp_sax_parse_exception();
			break;
		case 2300029: /* XP_UNKNOWN_EXCEPTION */
			conditionObj = new CBase_Ifds_xparser_xp_unknown_exception();
			break;
		case 2300030: /* XPARSER_CND_VERSION */
			conditionObj = new CBase_Ifds_xparser_xparser_cnd_version();
			break;
        default:
			//assert(0);
			break;
	}

	return conditionObj;
};

CConditionObject* CConditionBuilder::CreateBaseInfrastructureConditionObject(long conditionId) 
{
	CConditionObject* conditionObj = NULL;

	switch(conditionId)
	{
		case 1: /* BFBASE_CND_VERSION */
			conditionObj = new CBase_Infrastructure_bfbase_bfbase_cnd_version();
			break;
		case 3: /* ERR_FIELD_REQUIRED_GUI */
			conditionObj = new CBase_Infrastructure_bfbase_err_field_required_gui();
			break;
		case 4: /* ERR_FIELD_VALUE_NOT_VALID */
			conditionObj = new CBase_Infrastructure_bfbase_err_field_value_not_valid();
			break;
		case 5: /* ERR_FIELD_VALUE_NOT_VALID_GUI */
			conditionObj = new CBase_Infrastructure_bfbase_err_field_value_not_valid_gui();
			break;
		case 7: /* ERR_OBJ_REQUIRED */
			conditionObj = new CBase_Infrastructure_bfbase_err_obj_required();
			break;
		case 8: /* ERR_OBJ_REQUIRED_IN_LIST */
			conditionObj = new CBase_Infrastructure_bfbase_err_obj_required_in_list();
			break;
		case 100001: /* BFCONMGR_CND_VERSION */
			conditionObj = new CBase_Infrastructure_bfconmgr_bfconmgr_cnd_version();
			break;
		case 100003: /* ERR_PRIVCONN_CONNECT_FAILED */
			conditionObj = new CBase_Infrastructure_bfconmgr_err_privconn_connect_failed();
			break;
		case 100004: /* ERR_PRIVCONN_CREATE_EVENT */
			conditionObj = new CBase_Infrastructure_bfconmgr_err_privconn_create_event();
			break;
		case 100006: /* ERR_PRIVCONN_NOTIFY_FAILED */
			conditionObj = new CBase_Infrastructure_bfconmgr_err_privconn_notify_failed();
			break;
		case 100007: /* ERR_PRIVCONN_REQUEST_FAILED */
			conditionObj = new CBase_Infrastructure_bfconmgr_err_privconn_request_failed();
			break;
		case 100008: /* ERR_VM */
			conditionObj = new CBase_Infrastructure_bfconmgr_err_vm();
			break;
		case 100009: /* ERR_VMCONNECTION_CONNECT_FAILED */
			conditionObj = new CBase_Infrastructure_bfconmgr_err_vmconnection_connect_failed();
			break;
		case 100010: /* ERR_VMCONNECTION_CREATE_EVENT */
			conditionObj = new CBase_Infrastructure_bfconmgr_err_vmconnection_create_event();
			break;
		case 100011: /* ERR_VMCONNECTION_CREATE_FAILED */
			conditionObj = new CBase_Infrastructure_bfconmgr_err_vmconnection_create_failed();
			break;
		case 100012: /* ERR_VMCONNECTION_DISCONNECT_FAILED */
			conditionObj = new CBase_Infrastructure_bfconmgr_err_vmconnection_disconnect_failed();
			break;
		case 100013: /* ERR_VMCONNECTION_NOTIFY_FAILED */
			conditionObj = new CBase_Infrastructure_bfconmgr_err_vmconnection_notify_failed();
			break;
		case 100014: /* ERR_VMCONNECTION_REQUEST_FAILED */
			conditionObj = new CBase_Infrastructure_bfconmgr_err_vmconnection_request_failed();
			break;
		case 100015: /* ERR_VMCONNECTION_WAITEVENT_FAILED */
			conditionObj = new CBase_Infrastructure_bfconmgr_err_vmconnection_waitevent_failed();
			break;
		case 200001: /* BFDATA_CND_VERSION */
			conditionObj = new CBase_Infrastructure_bfdata_bfdata_cnd_version();
			break;
		case 200002: /* CND_BFDataFieldNotFoundException */
			conditionObj = new CBase_Infrastructure_bfdata_cnd_bfdatafieldnotfoundexception();
			break;
		case 200003: /* CND_BFDataFieldPropertiesException */
			conditionObj = new CBase_Infrastructure_bfdata_cnd_bfdatafieldpropertiesexception();
			break;
		case 200004: /* CND_BFDataIdOpException */
			conditionObj = new CBase_Infrastructure_bfdata_cnd_bfdataidopexception();
			break;
		case 200005: /* CND_BFDataIdUnknownException */
			conditionObj = new CBase_Infrastructure_bfdata_cnd_bfdataidunknownexception();
			break;
		case 200006: /* CND_BFDataInvalidOpException */
			conditionObj = new CBase_Infrastructure_bfdata_cnd_bfdatainvalidopexception();
			break;
		case 200007: /* CND_BFDataNotImplementedException */
			conditionObj = new CBase_Infrastructure_bfdata_cnd_bfdatanotimplementedexception();
			break;
		case 200008: /* CND_BFDataRepeatNotFoundException */
			conditionObj = new CBase_Infrastructure_bfdata_cnd_bfdatarepeatnotfoundexception();
			break;
		case 200009: /* CND_BFFieldIdOpException */
			conditionObj = new CBase_Infrastructure_bfdata_cnd_bffieldidopexception();
			break;
		case 200010: /* CND_BFFieldIdUnknownException */
			conditionObj = new CBase_Infrastructure_bfdata_cnd_bffieldidunknownexception();
			break;
		case 200011: /* CND_BFSubstitutionException */
			conditionObj = new CBase_Infrastructure_bfdata_cnd_bfsubstitutionexception();
			break;
		case 200012: /* CND_DigitOverflowException */
			conditionObj = new CBase_Infrastructure_bfdata_cnd_digitoverflowexception();
			break;
		case 200013: /* CND_InvalidCharacterException */
			conditionObj = new CBase_Infrastructure_bfdata_cnd_invalidcharacterexception();
			break;
		case 200014: /* CND_InvalidMaskException */
			conditionObj = new CBase_Infrastructure_bfdata_cnd_invalidmaskexception();
			break;
		case 300001: /* BFDBRKR_CND_VERSION */
			conditionObj = new CBase_Infrastructure_bfdbrkr_bfdbrkr_cnd_version();
			break;
		case 300002: /* ERR_HOST_CONNECTION_MGR_NOT_FOUND */
			conditionObj = new CBase_Infrastructure_bfdbrkr_err_host_connection_mgr_not_found();
			break;
		case 300004: /* ERR_MALFORMED_FILE_RESPONSE_BUFFER */
			conditionObj = new CBase_Infrastructure_bfdbrkr_err_malformed_file_response_buffer();
			break;
		case 300006: /* ERR_PRIVCONN_CREATE_FAILED */
			conditionObj = new CBase_Infrastructure_bfdbrkr_err_privconn_create_failed();
			break;
		case 300007: /* ERR_PRIVCONN_DISCONNECT_FAILED */
			conditionObj = new CBase_Infrastructure_bfdbrkr_err_privconn_disconnect_failed();
			break;
		case 300010: /* ERR_PRIVCONN_WAITEVENT_FAILED */
			conditionObj = new CBase_Infrastructure_bfdbrkr_err_privconn_waitevent_failed();
			break;
		case 300012: /* MULTYBYTE_TO_UNICODE_CONVERSION_ERROR */
			conditionObj = new CBase_Infrastructure_bfdbrkr_multybyte_to_unicode_conversion_error();
			break;
		case 300013: /* UNICODE_TO_MULTYBYTE_CONVERSION_ERROR */
			conditionObj = new CBase_Infrastructure_bfdbrkr_unicode_to_multybyte_conversion_error();
			break;
		case 300014: /* MISSMATCHING_VIEW_LAYOUT */
			conditionObj = new CBase_Ifds_bfdbrkr_err_missmatching_view_layout();
			break;
		case 400001: /* BFUTIL_CND_VERSION */
			conditionObj = new CBase_Infrastructure_bfutil_bfutil_cnd_version();
			break;
		case 400002: /* BFUTIL_ENCODE_TO_CODEPAGE_FAILURE */
			conditionObj = new CBase_Infrastructure_bfutil_bfutil_encode_to_codepage_failure();
			break;
		case 400003: /* BFUTIL_NO_HOST_CODEPAGE */
			conditionObj = new CBase_Infrastructure_bfutil_bfutil_no_host_codepage();
			break;
		case 400004: /* BFUTILERR_UnsupportedLocaleException */
			conditionObj = new CBase_Infrastructure_bfutil_bfutilerr_unsupportedlocaleexception();
			break;
		case 500001: /* BP_ERR_CANNOT_SET_CBO */
			conditionObj = new CBase_Infrastructure_bpbase_bp_err_cannot_set_cbo();
			break;
		case 500002: /* BP_ERR_CBO_NOT_SET */
			conditionObj = new CBase_Infrastructure_bpbase_bp_err_cbo_not_set();
			break;
		case 500003: /* BP_ERR_COMMAND_NOT_FOUND */
			conditionObj = new CBase_Infrastructure_bpbase_bp_err_command_not_found();
			break;
		case 500004: /* BP_ERR_COULD_NOT_GET_SUBSESSION */
			conditionObj = new CBase_Infrastructure_bpbase_bp_err_could_not_get_subsession();
			break;
		case 500005: /* BP_ERR_DUPLICATE_DISPATCHER */
			conditionObj = new CBase_Infrastructure_bpbase_bp_err_duplicate_dispatcher();
			break;
		case 500006: /* BP_ERR_DUPLICATE_KEY_IN_FIELD_DETAILS */
			conditionObj = new CBase_Infrastructure_bpbase_bp_err_duplicate_key_in_field_details();
			break;
		case 500007: /* BP_ERR_FIELD_DEFINED_IN_LIST_AND_CBO */
			conditionObj = new CBase_Infrastructure_bpbase_bp_err_field_defined_in_list_and_cbo();
			break;
		case 500008: /* BP_ERR_FIELD_NOT_FOUND */
			conditionObj = new CBase_Infrastructure_bpbase_bp_err_field_not_found();
			break;
		case 500009: /* BP_ERR_GETFIELD_FAILED */
			conditionObj = new CBase_Infrastructure_bpbase_bp_err_getfield_failed();
			break;
		case 500010: /* BP_ERR_ID_OUT_OF_RANGE */
			conditionObj = new CBase_Infrastructure_bpbase_bp_err_id_out_of_range();
			break;
		case 500011: /* BP_ERR_ID_OUT_OF_RANGE_FOR_FIELD */
			conditionObj = new CBase_Infrastructure_bpbase_bp_err_id_out_of_range_for_field();
			break;
		case 500012: /* BP_ERR_INVALID_METHOD_CALL */
			conditionObj = new CBase_Infrastructure_bpbase_bp_err_invalid_method_call();
			break;
		case 500013: /* BP_ERR_ITEM_NOT_VALID */
			conditionObj = new CBase_Infrastructure_bpbase_bp_err_item_not_valid();
			break;
		case 500014: /* BP_ERR_LIST_NOT_FOUND */
			conditionObj = new CBase_Infrastructure_bpbase_bp_err_list_not_found();
			break;
		case 500015: /* BP_ERR_LIST_NOT_VALID */
			conditionObj = new CBase_Infrastructure_bpbase_bp_err_list_not_valid();
			break;
		case 500016: /* BP_ERR_MUST_RUN_MODAL */
			conditionObj = new CBase_Infrastructure_bpbase_bp_err_must_run_modal();
			break;
		case 500017: /* BP_ERR_MUST_RUN_MODELESS */
			conditionObj = new CBase_Infrastructure_bpbase_bp_err_must_run_modeless();
			break;
		case 500018: /* BP_ERR_NO_DATA_AREA */
			conditionObj = new CBase_Infrastructure_bpbase_bp_err_no_data_area();
			break;
		case 500019: /* BP_ERR_NO_FIELD_MATCH */
			conditionObj = new CBase_Infrastructure_bpbase_bp_err_no_field_match();
			break;
		case 500020: /* BP_ERR_NO_PARENT_EXISTS */
			conditionObj = new CBase_Infrastructure_bpbase_bp_err_no_parent_exists();
			break;
		case 500021: /* BP_ERR_SEH_EXCEPTION */
			conditionObj = new CBase_Infrastructure_bpbase_bp_err_seh_exception();
			break;
		case 500022: /* BP_ERR_SETFIELD_FAILED */
			conditionObj = new CBase_Infrastructure_bpbase_bp_err_setfield_failed();
			break;
		case 500023: /* BP_ERR_UNKNOWN_EXCEPTION */
			conditionObj = new CBase_Infrastructure_bpbase_bp_err_unknown_exception();
			break;
		case 500024: /* BP_ERR_USER_CHANGE_PASSWORD */
			conditionObj = new CBase_Infrastructure_bpbase_bp_err_user_change_password();
			break;
		case 500025: /* BP_NO_OF_DAYS_PRIOR_TO_CHANGE_PASSWORD */
			conditionObj = new CBase_Infrastructure_bpbase_bp_no_of_days_prior_to_change_password();
			break;
		case 500026: /* BPBASE_CND_VERSION */
			conditionObj = new CBase_Infrastructure_bpbase_bpbase_cnd_version();
			break;
		case 600008: /* DIAWD23_CONTAINER_OPEN_FAIL */
			conditionObj = new CBase_Infrastructure_diawd23_diawd23_container_open_fail();
			break;
		case 600010: /* DIAWD23_CREATE_AWDSRC_FAIL */
			conditionObj = new CBase_Infrastructure_diawd23_diawd23_create_awdsrc_fail();
			break;
		case 600012: /* DIAWD23_LOGOFF_FAIL */
			conditionObj = new CBase_Infrastructure_diawd23_diawd23_logoff_fail();
			break;
		case 600013: /* DIAWD23_LOGON_FAIL */
			conditionObj = new CBase_Infrastructure_diawd23_diawd23_logon_fail();
			break;
		case 600016: /* DIAWD23_OLE_EXCEPTION */
			conditionObj = new CBase_Infrastructure_diawd23_diawd23_ole_exception();
			break;
		case 600019: /* DIAWD23_UNKNOWN_AWD_EXCEPTION */
			conditionObj = new CBase_Infrastructure_diawd23_diawd23_unknown_awd_exception();
			break;
		case 700003: /* DIAWDI_LOAD_PROC_FAIL */
			conditionObj = new CBase_Infrastructure_diawdi_diawdi_load_proc_fail();
			break;
		case 700006: /* DIAWDI_LOGON_INVALID_PASSWORD */
			conditionObj = new CBase_Infrastructure_diawdi_diawdi_logon_invalid_password();
			break;
		case 700007: /* DIAWDI_LOGON_NEW_PASSWORD_SAMEAS_OLD */
			conditionObj = new CBase_Infrastructure_diawdi_diawdi_logon_new_password_sameas_old();
			break;
		case 700008: /* DIAWDI_LOGON_NO_ERROR */
			conditionObj = new CBase_Infrastructure_diawdi_diawdi_logon_no_error();
			break;
		case 800002: /* DICORE_DATE_INVALID */
			conditionObj = new CBase_Infrastructure_dicbocore_dicore_date_invalid();
			break;
		case 800006: /* ERR_FIELD_CHECKPOINT_NOT_AVAILABLE */
			conditionObj = new CBase_Infrastructure_dicbocore_err_field_checkpoint_not_available();
			break;
		case 800008: /* ERR_FIELD_IS_OVER_MAXIMUM_ALLOWED */
			conditionObj = new CBase_Infrastructure_dicbocore_err_field_is_over_maximum_allowed();
			break;
		case 800012: /* ERR_FIELD_REQUIRED */
			conditionObj = new CBase_Infrastructure_dicbocore_err_field_required();
			break;
		case 800015: /* ERR_FORMAT_NOT_RECOGNIZED */
			conditionObj = new CBase_Infrastructure_dicbocore_err_format_not_recognized();
			break;
		case 800020: /* ERR_INVALID_BATCH_WORKORDER_EVENT */
			conditionObj = new CBase_Infrastructure_dicbocore_err_invalid_batch_workorder_event();
			break;
		case 800021: /* ERR_INVALID_FIELD_ID */
			conditionObj = new CBase_Infrastructure_dicbocore_err_invalid_field_id();
			break;
		case 800027: /* ERR_INVALID_TIME */
			conditionObj = new CBase_Infrastructure_dicbocore_err_invalid_time();
			break;
		case 800028: /* ERR_INVALID_USE_OF_OFFICIAL_GROUP */
			conditionObj = new CBase_Infrastructure_dicbocore_err_invalid_use_of_official_group();
			break;
		case 800029: /* ERR_KEY_NOT_FOUND */
			conditionObj = new CBase_Infrastructure_dicbocore_err_key_not_found();
			break;
		case 800030: /* ERR_MFDATE_INVALID */
			conditionObj = new CBase_Infrastructure_dicbocore_err_mfdate_invalid();
			break;
		case 800031: /* ERR_MIN_VALUE_GREATER_THAN_MAX */
			conditionObj = new CBase_Infrastructure_dicbocore_err_min_value_greater_than_max();
			break;
		case 800032: /* ERR_MULTIPLE_INIT_CALLS */
			conditionObj = new CBase_Infrastructure_dicbocore_err_multiple_init_calls();
			break;
		case 800034: /* ERR_NO_DELETE_OBJECT_ALLOWED */
			conditionObj = new CBase_Infrastructure_dicbocore_err_no_delete_object_allowed();
			break;
		case 800037: /* ERR_NO_VIEW_DATA_OBJECTS_REGISTERED */
			conditionObj = new CBase_Infrastructure_dicbocore_err_no_view_data_objects_registered();
			break;
		case 800038: /* ERR_NO_VIEW_DATA_REPEATS */
			conditionObj = new CBase_Infrastructure_dicbocore_err_no_view_data_repeats();
			break;
		case 800043: /* ERR_OBJECT_NOT_FOUND */
			conditionObj = new CBase_Infrastructure_dicbocore_err_object_not_found();
			break;
		case 800044: /* ERR_OBJECT_NOT_INITIALIZED */
			conditionObj = new CBase_Infrastructure_dicbocore_err_object_not_initialized();
			break;
		case 800046: /* ERR_OBJECT_PRIVATE_USE */
			conditionObj = new CBase_Infrastructure_dicbocore_err_object_private_use();
			break;
		case 800048: /* ERR_OBJECT_READ_ONLY */
			conditionObj = new CBase_Infrastructure_dicbocore_err_object_read_only();
			break;
		case 800050: /* ERR_RETREIVING_DATE */
			conditionObj = new CBase_Infrastructure_dicbocore_err_retreiving_date();
			break;
		case 800059: /* WRN_OBJECT_DOES_NOT_ALLOW_GROUPS */
			conditionObj = new CBase_Infrastructure_dicbocore_wrn_object_does_not_allow_groups();
			break;
		case 900001: /* BASE_ALLOC_FAIL */
			conditionObj = new CBase_Infrastructure_dicore_base_alloc_fail();
			break;
		case 900002: /* DICORE_BAD_PACKET */
			conditionObj = new CBase_Infrastructure_dicore_dicore_bad_packet();
			break;
		case 900006: /* DICORE_DATAPATH_ENV_NOT_DEFINED */
			conditionObj = new CBase_Infrastructure_dicore_dicore_datapath_env_not_defined();
			break;
		case 900008: /* DICORE_DATE_STRING_INVALID */
			conditionObj = new CBase_Infrastructure_dicore_dicore_date_string_invalid();
			break;
		case 900009: /* DICORE_DELETE_KEY_FAIL */
			conditionObj = new CBase_Infrastructure_dicore_dicore_delete_key_fail();
			break;
		case 900013: /* DICORE_EVENTSEM_CREATE_FAIL */
			conditionObj = new CBase_Infrastructure_dicore_dicore_eventsem_create_fail();
			break;
		case 900015: /* DICORE_EVENTSEM_RESET_FAIL */
			conditionObj = new CBase_Infrastructure_dicore_dicore_eventsem_reset_fail();
			break;
		case 900016: /* DICORE_EVENTSEM_SET_FAIL */
			conditionObj = new CBase_Infrastructure_dicore_dicore_eventsem_set_fail();
			break;
		case 900017: /* DICORE_EVENTSEM_WAIT_FAIL */
			conditionObj = new CBase_Infrastructure_dicore_dicore_eventsem_wait_fail();
			break;
		case 900018: /* DICORE_FUNCTION_LOAD_FAIL */
			conditionObj = new CBase_Infrastructure_dicore_dicore_function_load_fail();
			break;
		case 900019: /* DICORE_HOSTMASKS_NOT_DEFINED_IN_REGISTRY */
			conditionObj = new CBase_Infrastructure_dicore_dicore_hostmasks_not_defined_in_registry();
			break;
		case 900020: /* DICORE_IPC_SYNCH_FAIL */
			conditionObj = new CBase_Infrastructure_dicore_dicore_ipc_synch_fail();
			break;
		case 900022: /* DICORE_LOCATION_NOT_DEFINED */
			conditionObj = new CBase_Infrastructure_dicore_dicore_location_not_defined();
			break;
		case 900023: /* DICORE_MUTEXSEM_CREATE_FAIL */
			conditionObj = new CBase_Infrastructure_dicore_dicore_mutexsem_create_fail();
			break;
		case 900025: /* DICORE_MUTEXSEM_RELEASE_FAIL */
			conditionObj = new CBase_Infrastructure_dicore_dicore_mutexsem_release_fail();
			break;
		case 900026: /* DICORE_MUTEXSEM_WAIT_FAIL */
			conditionObj = new CBase_Infrastructure_dicore_dicore_mutexsem_wait_fail();
			break;
		case 900027: /* DICORE_OPEN_INI_FILE_FAIL */
			conditionObj = new CBase_Infrastructure_dicore_dicore_open_ini_file_fail();
			break;
		case 900028: /* DICORE_OVERSIZE_BUFFER */
			conditionObj = new CBase_Infrastructure_dicore_dicore_oversize_buffer();
			break;
		case 900029: /* DICORE_PARSE_IDI_MISSING_SEPARATOR */
			conditionObj = new CBase_Infrastructure_dicore_dicore_parse_idi_missing_separator();
			break;
		case 900030: /* DICORE_PARSE_IDI_MISSING_TAG_NAME */
			conditionObj = new CBase_Infrastructure_dicore_dicore_parse_idi_missing_tag_name();
			break;
		case 900031: /* DICORE_PARSE_IDI_MISSING_TERMINATOR */
			conditionObj = new CBase_Infrastructure_dicore_dicore_parse_idi_missing_terminator();
			break;
		case 900035: /* DICORE_PROCESS_CREATE_FAIL */
			conditionObj = new CBase_Infrastructure_dicore_dicore_process_create_fail();
			break;
		case 900036: /* DICORE_PROFILE_ALREAD_EXISTS */
			conditionObj = new CBase_Infrastructure_dicore_dicore_profile_alread_exists();
			break;
		case 900039: /* DICORE_SAVE_VALUE_FAIL */
			conditionObj = new CBase_Infrastructure_dicore_dicore_save_value_fail();
			break;
		case 900043: /* DICORE_VMDISCONNECT_FAIL */
			conditionObj = new CBase_Infrastructure_dicore_dicore_vmdisconnect_fail();
			break;
		case 900044: /* DICORE_VMNOTIFYSEM_FAIL */
			conditionObj = new CBase_Infrastructure_dicore_dicore_vmnotifysem_fail();
			break;
		case 900055: /* DILOCAL_JNI_EXCEPTION_LOCATE */
			conditionObj = new CBase_Infrastructure_dicore_dilocal_jni_exception_locate();
			break;
		case 1000003: /* DIDBRKR_CANNOT_ASSIGN_DATAELEMENT_OBJECTS */
			conditionObj = new CBase_Infrastructure_didbrkr_didbrkr_cannot_assign_dataelement_objects();
			break;
		case 1000011: /* DIDBRKR_ERROR_READING_STREAM_FILE */
			conditionObj = new CBase_Infrastructure_didbrkr_didbrkr_error_reading_stream_file();
			break;
		case 1000013: /* DIDBRKR_FILE_SEEK_FAILED */
			conditionObj = new CBase_Infrastructure_didbrkr_didbrkr_file_seek_failed();
			break;
		case 1000017: /* DIDBRKR_INVALID_PROPERTY_POINTER */
			conditionObj = new CBase_Infrastructure_didbrkr_didbrkr_invalid_property_pointer();
			break;
		case 1000021: /* DIDBRKR_NO_PATH_TO_PROPERTIES_FILE */
			conditionObj = new CBase_Infrastructure_didbrkr_didbrkr_no_path_to_properties_file();
			break;
		case 1000027: /* DIDBRKR_PROPERTY_DOES_NOT_EXIST_AT_INDEX */
			conditionObj = new CBase_Infrastructure_didbrkr_didbrkr_property_does_not_exist_at_index();
			break;
		case 1000028: /* DIDBRKR_READ_SIZE_FAILED */
			conditionObj = new CBase_Infrastructure_didbrkr_didbrkr_read_size_failed();
			break;
		case 1000031: /* DIDBRKR_REDEFINE_REPEATS_NOT_ALLOWED */
			conditionObj = new CBase_Infrastructure_didbrkr_didbrkr_redefine_repeats_not_allowed();
			break;
		case 1000035: /* DIDBRKR_UNEXPECTED_END_OF_STREAM_FILE */
			conditionObj = new CBase_Infrastructure_didbrkr_didbrkr_unexpected_end_of_stream_file();
			break;
		case 1100002: /* DIODBC_ERROR */
			conditionObj = new CBase_Infrastructure_disessn_diodbc_error();
			break;
		case 1100004: /* DISESSN_AWD_NOT_LOGGED_ON */
			conditionObj = new CBase_Infrastructure_disessn_disessn_awd_not_logged_on();
			break;
		case 1100005: /* DISESSN_AWD_WORK_CREATED */
			conditionObj = new CBase_Infrastructure_disessn_disessn_awd_work_created();
			break;
		case 1200003: /* DITA2KDB_A58_INFO_UNAVAIL */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_a58_info_unavail();
			break;
		case 1200005: /* DITA2KDB_A87_INFO_UNAVAIL */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_a87_info_unavail();
			break;
		case 1200010: /* DITA2KDB_AMT_GREATER_THAN_MAX */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_amt_greater_than_max();
			break;
		case 1200011: /* DITA2KDB_AMT_LESS_THAN_MIN */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_amt_less_than_min();
			break;
		case 1200014: /* DITA2KDB_AUTHORIZATION_FAILED */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_authorization_failed();
			break;
		case 1200016: /* DITA2KDB_B07_REC_NOT_FOUND */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_b07_rec_not_found();
			break;
		case 1200017: /* DITA2KDB_B08_RECORD_NOT_FOUND */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_b08_record_not_found();
			break;
		case 1200020: /* DITA2KDB_B83_INFO_UNAVAIL */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_b83_info_unavail();
			break;
		case 1200021: /* DITA2KDB_B83_REC_NOT_FOUND */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_b83_rec_not_found();
			break;
		case 1200022: /* DITA2KDB_C52_INFO_UNAVAIL */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_c52_info_unavail();
			break;
		case 1200024: /* DITA2KDB_CANT_OPEN_DAT_FILE */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_cant_open_dat_file();
			break;
		case 1200032: /* DITA2KDB_DLR_NOT_AUTHORIZED */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_dlr_not_authorized();
			break;
		case 1200034: /* DITA2KDB_F16_REC_NOT_FOUND */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_f16_rec_not_found();
			break;
		case 1200037: /* DITA2KDB_INVALID_ABA_NBR */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_invalid_aba_nbr();
			break;
		case 1200038: /* DITA2KDB_INVALID_ACCT_NUM */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_invalid_acct_num();
			break;
		case 1200039: /* DITA2KDB_INVALID_ACCUM_YEARS */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_invalid_accum_years();
			break;
		case 1200041: /* DITA2KDB_INVALID_ARRAY_ROWS */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_invalid_array_rows();
			break;
		case 1200042: /* DITA2KDB_INVALID_BANK_MICR_ID */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_invalid_bank_micr_id();
			break;
		case 1200043: /* DITA2KDB_INVALID_BATCH_NUM */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_invalid_batch_num();
			break;
		case 1200044: /* DITA2KDB_INVALID_BATCH_NUMBER */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_invalid_batch_number();
			break;
		case 1200046: /* DITA2KDB_INVALID_CORR_CODE */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_invalid_corr_code();
			break;
		case 1200047: /* DITA2KDB_INVALID_CUMDISC */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_invalid_cumdisc();
			break;
		case 1200048: /* DITA2KDB_INVALID_CUMDISC_PLAN */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_invalid_cumdisc_plan();
			break;
		case 1200050: /* DITA2KDB_INVALID_DATA_REQUEST */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_invalid_data_request();
			break;
		case 1200052: /* DITA2KDB_INVALID_DDA_NBR */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_invalid_dda_nbr();
			break;
		case 1200057: /* DITA2KDB_INVALID_DLR_BR_SUMMARY */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_invalid_dlr_br_summary();
			break;
		case 1200062: /* DITA2KDB_INVALID_EXCH_RED_CANC */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_invalid_exch_red_canc();
			break;
		case 1200063: /* DITA2KDB_INVALID_EXT_IST */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_invalid_ext_ist();
			break;
		case 1200067: /* DITA2KDB_INVALID_FUND_CODE */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_invalid_fund_code();
			break;
		case 1200068: /* DITA2KDB_INVALID_FUND_SPONSOR */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_invalid_fund_sponsor();
			break;
		case 1200069: /* DITA2KDB_INVALID_INT_IST */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_invalid_int_ist();
			break;
		case 1200070: /* DITA2KDB_INVALID_INVESTOR_GRP */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_invalid_investor_grp();
			break;
		case 1200072: /* DITA2KDB_INVALID_MF_TRAN_ID */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_invalid_mf_tran_id();
			break;
		case 1200073: /* DITA2KDB_INVALID_MGMT_CODE */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_invalid_mgmt_code();
			break;
		case 1200074: /* DITA2KDB_INVALID_MONTHLY_ACCUM */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_invalid_monthly_accum();
			break;
		case 1200078: /* DITA2KDB_INVALID_PASSWORD */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_invalid_password();
			break;
		case 1200079: /* DITA2KDB_INVALID_PRE_AGREEMENT */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_invalid_pre_agreement();
			break;
		case 1200080: /* DITA2KDB_INVALID_PRICE */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_invalid_price();
			break;
		case 1200081: /* DITA2KDB_INVALID_PST_AGREEMENT */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_invalid_pst_agreement();
			break;
		case 1200083: /* DITA2KDB_INVALID_REC_EEE_ID */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_invalid_rec_eee_id();
			break;
		case 1200085: /* DITA2KDB_INVALID_REIN_DOLLAR */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_invalid_rein_dollar();
			break;
		case 1200087: /* DITA2KDB_INVALID_REQUEST_CNT */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_invalid_request_cnt();
			break;
		case 1200089: /* DITA2KDB_INVALID_SEL_CRITERIA */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_invalid_sel_criteria();
			break;
		case 1200090: /* DITA2KDB_INVALID_START_MONTH */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_invalid_start_month();
			break;
		case 1200092: /* DITA2KDB_INVALID_TAX_ID_NUM */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_invalid_tax_id_num();
			break;
		case 1200094: /* DITA2KDB_INVALID_VIEW */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_invalid_view();
			break;
		case 1200097: /* DITA2KDB_MGMT_CO_NOT_FOUND */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_mgmt_co_not_found();
			break;
		case 1200098: /* DITA2KDB_MULTI_C52_STATES */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_multi_c52_states();
			break;
		case 1200102: /* DITA2KDB_NO_A79_FOR_VERIFY_DTE */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_no_a79_for_verify_dte();
			break;
		case 1200103: /* DITA2KDB_NO_D61_FUND_GROUP_FND */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_no_d61_fund_group_fnd();
			break;
		case 1200104: /* DITA2KDB_NO_EXPD_RED_ACCT */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_no_expd_red_acct();
			break;
		case 1200105: /* DITA2KDB_NO_SYSTEMS */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_no_systems();
			break;
		case 1200110: /* DITA2KDB_OPER_DISABLED */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_oper_disabled();
			break;
		case 1200120: /* DITA2KDB_RETURN_NASU_ACCT */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_return_nasu_acct();
			break;
		case 1200124: /* DITA2KDB_SEVERE_ERROR */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_severe_error();
			break;
		case 1200125: /* DITA2KDB_STS_ERROR */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_sts_error();
			break;
		case 1200126: /* DITA2KDB_SYSTEM_DOWN */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_system_down();
			break;
		case 1200127: /* DITA2KDB_SYSTEM_ID_ERROR */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_system_id_error();
			break;
		case 1200128: /* DITA2KDB_SYSTRAN_AGR_EXIST */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_systran_agr_exist();
			break;
		case 1200129: /* DITA2KDB_SYSTRAN_INSTR_EXIST */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_systran_instr_exist();
			break;
		case 1200131: /* DITA2KDB_SYSTRAN_SEVERE_ERROR */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_systran_severe_error();
			break;
		case 1200133: /* DITA2KDB_TRANS_BACKED_OUT */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_trans_backed_out();
			break;
		case 1200134: /* DITA2KDB_TRANS_NOT_AVL_FOR_DLT */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_trans_not_avl_for_dlt();
			break;
		case 1200135: /* DITA2KDB_UNKNOWN_ERROR */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_unknown_error();
			break;
		case 1200136: /* DITA2KDB_UNKNOWN_VIEW_ERROR */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_unknown_view_error();
			break;
		case 1200138: /* DITA2KDB_VM_ERROR */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_vm_error();
			break;
		case 1200139: /* DITA2KDB_VM_MORE_DATA */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_vm_more_data();
			break;
		case 1200140: /* DITA2KDB_VM_THREW */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_vm_threw();
			break;
		case 1200142: /* DITA2KDB_VMCONNECT_ERROR */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_vmconnect_error();
			break;
		case 1200144: /* DITA2KDB_VMNOTIFYSEM_ERROR */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_vmnotifysem_error();
			break;
		case 1200145: /* DITA2KDB_VMNOTIFYWIN_DUPLICATE */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_vmnotifywin_duplicate();
			break;
		case 1200146: /* DITA2KDB_VMNOTIFYWIN_MISSING */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_vmnotifywin_missing();
			break;
		case 1200147: /* DITA2KDB_VMREADRESPONSE_ERROR */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_vmreadresponse_error();
			break;
		case 1200148: /* DITA2KDB_VMREQ_FAILED */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_vmreq_failed();
			break;
		case 1200149: /* DITA2KDB_VMREQUEST_ERROR */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_vmrequest_error();
			break;
		case 1200153: /* DITA2KDB_WS00221C_AUTH_FUNCTIONS_DISABLED */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_auth_functions_disabled();
			break;
		case 1200154: /* DITA2KDB_WS00221C_CLOSE_FOR_FILE_NOT_OPENED */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_close_for_file_not_opened();
			break;
		case 1200155: /* DITA2KDB_WS00221C_CONNECT_AUTH_FAILURE */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_connect_auth_failure();
			break;
		case 1200162: /* DITA2KDB_WS00221C_DCB_CONFLICT_PRGM_TO_FILE */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_dcb_conflict_prgm_to_file();
			break;
		case 1200166: /* DITA2KDB_WS00221C_DUPLICATE_KEY */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_duplicate_key();
			break;
		case 1200167: /* DITA2KDB_WS00221C_DUPLICATE_KEY_ERROR */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_duplicate_key_error();
			break;
		case 1200168: /* DITA2KDB_WS00221C_DUPLICATE_KEY_OK */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_duplicate_key_ok();
			break;
		case 1200175: /* DITA2KDB_WS00221C_FILE_OK */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_file_ok();
			break;
		case 1200181: /* DITA2KDB_WS00221C_INVALID_UPDATE_FOREIGN_KEY */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_invalid_update_foreign_key();
			break;
		case 1200183: /* DITA2KDB_WS00221C_MISSING_DD_CARD */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_missing_dd_card();
			break;
		case 1200186: /* DITA2KDB_WS00221C_NO_RECORD_FOUND */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_no_record_found();
			break;
		case 1200187: /* DITA2KDB_WS00221C_NO_SPACE_AVAILABLE_1 */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_no_space_available_1();
			break;
		case 1200189: /* DITA2KDB_WS00221C_NON_OPTIONAL_FILE_NOT_PRES */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_non_optional_file_not_pres();
			break;
		case 1200190: /* DITA2KDB_WS00221C_NOT_PRECEDED_BY_GOOD_READ */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_not_preceded_by_good_read();
			break;
		case 1200191: /* DITA2KDB_WS00221C_NULL_VALUE_CANNOT_BE_ASSIGNED */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_null_value_cannot_be_assigned();
			break;
		case 1200198: /* DITA2KDB_WS00221C_PROGRAM_NAME_NOT_IN_PLAN */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_program_name_not_in_plan();
			break;
		case 1200200: /* DITA2KDB_WS00221C_REL_RECORD_NBR_TOO_LARGE */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_rel_record_nbr_too_large();
			break;
		case 1200203: /* DITA2KDB_WS00221C_RESP_ACCOUNT_IS_DIVMAIL */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_account_is_divmail();
			break;
		case 1200204: /* DITA2KDB_WS00221C_RESP_ACCOUNT_IS_PPA */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_account_is_ppa();
			break;
		case 1200205: /* DITA2KDB_WS00221C_RESP_ACCOUNT_IS_TIMER */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_account_is_timer();
			break;
		case 1200206: /* DITA2KDB_WS00221C_RESP_ACCT_CLOSED */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_acct_closed();
			break;
		case 1200211: /* DITA2KDB_WS00221C_RESP_ACCT_GRP_LIST_EXCEEDED */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_acct_grp_list_exceeded();
			break;
		case 1200212: /* DITA2KDB_WS00221C_RESP_ACCT_GRP_NOT_ALLOWED */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_acct_grp_not_allowed();
			break;
		case 1200213: /* DITA2KDB_WS00221C_RESP_ACCT_MARKED_ESCHEATMENT */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_acct_marked_escheatment();
			break;
		case 1200217: /* DITA2KDB_WS00221C_RESP_ACCT_MARKED_STOP_MAIL */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_acct_marked_stop_mail();
			break;
		case 1200218: /* DITA2KDB_WS00221C_RESP_ACCT_MARKED_STOP_PURCHASE */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_acct_marked_stop_purchase();
			break;
		case 1200223: /* DITA2KDB_WS00221C_RESP_ACCT_NOT_MARKED_ARS */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_acct_not_marked_ars();
			break;
		case 1200224: /* DITA2KDB_WS00221C_RESP_ACCT_NOT_MARKED_EXP_RED */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_acct_not_marked_exp_red();
			break;
		case 1200226: /* DITA2KDB_WS00221C_RESP_ACH_REDEEM_NOT_ALLOWED */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_ach_redeem_not_allowed();
			break;
		case 1200227: /* DITA2KDB_WS00221C_RESP_ACH_SPECIAL_REDEMPTION_NO */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_ach_special_redemption_no();
			break;
		case 1200228: /* DITA2KDB_WS00221C_RESP_ADDR_OF_RGSTR_CHANGED */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_addr_of_rgstr_changed();
			break;
		case 1200231: /* DITA2KDB_WS00221C_RESP_AMT_EXCEEDS_AVAILABLE */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_amt_exceeds_available();
			break;
		case 1200236: /* DITA2KDB_WS00221C_RESP_BAD_LINK_TO_CRTSTACK */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_bad_link_to_crtstack();
			break;
		case 1200237: /* DITA2KDB_WS00221C_RESP_BANK_ACCT_NBR_MISMATCH */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_bank_acct_nbr_mismatch();
			break;
		case 1200239: /* DITA2KDB_WS00221C_RESP_CHG_REC_NOT_FOUND */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_chg_rec_not_found();
			break;
		case 1200240: /* DITA2KDB_WS00221C_RESP_CHGD_BY_DIF_OPERATOR */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_chgd_by_dif_operator();
			break;
		case 1200241: /* DITA2KDB_WS00221C_RESP_COMM_SHARES_NOT_FOUND */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_comm_shares_not_found();
			break;
		case 1200243: /* DITA2KDB_WS00221C_RESP_COPY_EXCH_ATTEMPT_INVALID */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_copy_exch_attempt_invalid();
			break;
		case 1200247: /* DITA2KDB_WS00221C_RESP_COPY_PURCH_SSN_MISMATCH */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_copy_purch_ssn_mismatch();
			break;
		case 1200252: /* DITA2KDB_WS00221C_RESP_DFHRESP_DISABLED */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_disabled();
			break;
		case 1200256: /* DITA2KDB_WS00221C_RESP_DFHRESP_FILENOTFOUND */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_filenotfound();
			break;
		case 1200259: /* DITA2KDB_WS00221C_RESP_DFHRESP_IOERR */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_ioerr();
			break;
		case 1200261: /* DITA2KDB_WS00221C_RESP_DFHRESP_LENGERR */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_lengerr();
			break;
		case 1200267: /* DITA2KDB_WS00221C_RESP_DFHRESP_QIDERR */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_qiderr();
			break;
		case 1200272: /* DITA2KDB_WS00221C_RESP_DOL_TRAN_NOT_AUTHORIZED */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_dol_tran_not_authorized();
			break;
		case 1200276: /* DITA2KDB_WS00221C_RESP_EXCH_BANK_ONLY_FROM_SIDE */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_exch_bank_only_from_side();
			break;
		case 1200279: /* DITA2KDB_WS00221C_RESP_EXCH_MGMTS_NOT_EQUAL */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_exch_mgmts_not_equal();
			break;
		case 1200283: /* DITA2KDB_WS00221C_RESP_FULL_LIQDTN_NOT_ALLOWED */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_full_liqdtn_not_allowed();
			break;
		case 1200285: /* DITA2KDB_WS00221C_RESP_FUND_MARKED_NO_ACH_ACTIVY */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_fund_marked_no_ach_activy();
			break;
		case 1200287: /* DITA2KDB_WS00221C_RESP_FUND_NOT_AUTHORIZED */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_fund_not_authorized();
			break;
		case 1200288: /* DITA2KDB_WS00221C_RESP_INSUFF_COLLECTED_SHRS */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_insuff_collected_shrs();
			break;
		case 1200300: /* DITA2KDB_WS00221C_RESP_INVALID_ACTION_CODE */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_action_code();
			break;
		case 1200301: /* DITA2KDB_WS00221C_RESP_INVALID_ADD_MAL_ALRY_EX */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_add_mal_alry_ex();
			break;
		case 1200304: /* DITA2KDB_WS00221C_RESP_INVALID_ALPHA_CODE */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_alpha_code();
			break;
		case 1200308: /* DITA2KDB_WS00221C_RESP_INVALID_ARRAY_ROWS */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_array_rows();
			break;
		case 1200309: /* DITA2KDB_WS00221C_RESP_INVALID_ASSET_TARGET_RT */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_asset_target_rt();
			break;
		case 1200312: /* DITA2KDB_WS00221C_RESP_INVALID_BANK_ACCT_TYPE */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_bank_acct_type();
			break;
		case 1200317: /* DITA2KDB_WS00221C_RESP_INVALID_BATCH_NUM */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_batch_num();
			break;
		case 1200319: /* DITA2KDB_WS00221C_RESP_INVALID_BNF_RELATION */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_bnf_relation();
			break;
		case 1200321: /* DITA2KDB_WS00221C_RESP_INVALID_CAP_GAINS_CODE */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_cap_gains_code();
			break;
		case 1200322: /* DITA2KDB_WS00221C_RESP_INVALID_CASH_INST_TYPE */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_cash_inst_type();
			break;
		case 1200325: /* DITA2KDB_WS00221C_RESP_INVALID_CITY_ENTERED */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_city_entered();
			break;
		case 1200327: /* DITA2KDB_WS00221C_RESP_INVALID_CLIENT_ID */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_client_id();
			break;
		case 1200331: /* DITA2KDB_WS00221C_RESP_INVALID_CRUD_CODE */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_crud_code();
			break;
		case 1200333: /* DITA2KDB_WS00221C_RESP_INVALID_CUMDISC_PLAN */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_cumdisc_plan();
			break;
		case 1200337: /* DITA2KDB_WS00221C_RESP_INVALID_DEBIT_CARD */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_debit_card();
			break;
		case 1200341: /* DITA2KDB_WS00221C_RESP_INVALID_DLR_BRANCH */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_dlr_branch();
			break;
		case 1200348: /* DITA2KDB_WS00221C_RESP_INVALID_EXCH_PUR_CANC */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_exch_pur_canc();
			break;
		case 1200352: /* DITA2KDB_WS00221C_RESP_INVALID_FINS_ID */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_fins_id();
			break;
		case 1200354: /* DITA2KDB_WS00221C_RESP_INVALID_FIRM_NBR */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_firm_nbr();
			break;
		case 1200355: /* DITA2KDB_WS00221C_RESP_INVALID_FLD_CNT */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_fld_cnt();
			break;
		case 1200357: /* DITA2KDB_WS00221C_RESP_INVALID_FOREIGN_STATE */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_foreign_state();
			break;
		case 1200358: /* DITA2KDB_WS00221C_RESP_INVALID_FORGN_ADDR_CDE */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_forgn_addr_cde();
			break;
		case 1200365: /* DITA2KDB_WS00221C_RESP_INVALID_FUND_GRP_NBR */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_fund_grp_nbr();
			break;
		case 1200367: /* DITA2KDB_WS00221C_RESP_INVALID_FUND_RELATIONSHIP */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_fund_relationship();
			break;
		case 1200374: /* DITA2KDB_WS00221C_RESP_INVALID_LINE_CODE */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_line_code();
			break;
		case 1200375: /* DITA2KDB_WS00221C_RESP_INVALID_LOI_AGREE_AMT */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_loi_agree_amt();
			break;
		case 1200377: /* DITA2KDB_WS00221C_RESP_INVALID_LOI_NUMBER */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_loi_number();
			break;
		case 1200382: /* DITA2KDB_WS00221C_RESP_INVALID_MIN_AMT */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_min_amt();
			break;
		case 1200384: /* DITA2KDB_WS00221C_RESP_INVALID_MTHLY_INDS */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_mthly_inds();
			break;
		case 1200387: /* DITA2KDB_WS00221C_RESP_INVALID_NET_CHG */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_net_chg();
			break;
		case 1200395: /* DITA2KDB_WS00221C_RESP_INVALID_OUT_OF_BLC_LOW_RT */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_out_of_blc_low_rt();
			break;
		case 1200399: /* DITA2KDB_WS00221C_RESP_INVALID_PIN_SEC_METHOD */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_pin_sec_method();
			break;
		case 1200400: /* DITA2KDB_WS00221C_RESP_INVALID_PND_REDEMPTION */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_pnd_redemption();
			break;
		case 1200403: /* DITA2KDB_WS00221C_RESP_INVALID_PRG_ALW_CD */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_prg_alw_cd();
			break;
		case 1200404: /* DITA2KDB_WS00221C_RESP_INVALID_PRICE */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_price();
			break;
		case 1200408: /* DITA2KDB_WS00221C_RESP_INVALID_PRODUCT_ID */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_product_id();
			break;
		case 1200409: /* DITA2KDB_WS00221C_RESP_INVALID_PST_AGREEMENT */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_pst_agreement();
			break;
		case 1200410: /* DITA2KDB_WS00221C_RESP_INVALID_PTF_ROLE_TYPE_ID */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_ptf_role_type_id();
			break;
		case 1200417: /* DITA2KDB_WS00221C_RESP_INVALID_REP_NUMBER */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_rep_number();
			break;
		case 1200418: /* DITA2KDB_WS00221C_RESP_INVALID_REQUEST_CNT */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_request_cnt();
			break;
		case 1200420: /* DITA2KDB_WS00221C_RESP_INVALID_RRTTFR_CD */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_rrttfr_cd();
			break;
		case 1200421: /* DITA2KDB_WS00221C_RESP_INVALID_RULE_FLD_SEQ */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_rule_fld_seq();
			break;
		case 1200429: /* DITA2KDB_WS00221C_RESP_INVALID_SOURCE_SYSTEM_ID */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_source_system_id();
			break;
		case 1200431: /* DITA2KDB_WS00221C_RESP_INVALID_ST_COUNTRY_CD */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_st_country_cd();
			break;
		case 1200432: /* DITA2KDB_WS00221C_RESP_INVALID_ST_DS_APO_FPO_ZIP */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_st_ds_apo_fpo_zip();
			break;
		case 1200434: /* DITA2KDB_WS00221C_RESP_INVALID_START_MONTH */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_start_month();
			break;
		case 1200435: /* DITA2KDB_WS00221C_RESP_INVALID_START_YEAR */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_start_year();
			break;
		case 1200436: /* DITA2KDB_WS00221C_RESP_INVALID_STATE_UPD_CODE */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_state_upd_code();
			break;
		case 1200437: /* DITA2KDB_WS00221C_RESP_INVALID_STOCK_SPLIT_RATE */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_stock_split_rate();
			break;
		case 1200439: /* DITA2KDB_WS00221C_RESP_INVALID_SYS_AGR_ID */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_sys_agr_id();
			break;
		case 1200440: /* DITA2KDB_WS00221C_RESP_INVALID_SYS_AGREE_AMT */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_sys_agree_amt();
			break;
		case 1200443: /* DITA2KDB_WS00221C_RESP_INVALID_SYSTMTC_TYP */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_systmtc_typ();
			break;
		case 1200444: /* DITA2KDB_WS00221C_RESP_INVALID_TAX_ID_NUMBER */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_tax_id_number();
			break;
		case 1200446: /* DITA2KDB_WS00221C_RESP_INVALID_TERMINAL_ID */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_terminal_id();
			break;
		case 1200453: /* DITA2KDB_WS00221C_RESP_INVALID_TRAN_TYPE */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_tran_type();
			break;
		case 1200454: /* DITA2KDB_WS00221C_RESP_INVALID_TRXN_NUMBER */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_trxn_number();
			break;
		case 1200455: /* DITA2KDB_WS00221C_RESP_INVALID_UNISSUED_SHRS */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_unissued_shrs();
			break;
		case 1200458: /* DITA2KDB_WS00221C_RESP_INVALID_WITHH_AMT */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_withh_amt();
			break;
		case 1200470: /* DITA2KDB_WS00221C_RESP_NO_VERIFY_DTE */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_no_verify_dte();
			break;
		case 1200472: /* DITA2KDB_WS00221C_RESP_NOT_SIGNED_ON */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_not_signed_on();
			break;
		case 1200477: /* DITA2KDB_WS00221C_RESP_PIN_INIT_NOT_ALLOWED */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_pin_init_not_allowed();
			break;
		case 1200480: /* DITA2KDB_WS00221C_RESP_PIN_NUMBER_ACTIVE */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_pin_number_active();
			break;
		case 1200481: /* DITA2KDB_WS00221C_RESP_PIN_NUMBER_BLOCKED */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_pin_number_blocked();
			break;
		case 1200482: /* DITA2KDB_WS00221C_RESP_PIN_NUMBER_DUPLICATE */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_pin_number_duplicate();
			break;
		case 1200486: /* DITA2KDB_WS00221C_RESP_PIN_NUMBER_MULTIPLE */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_pin_number_multiple();
			break;
		case 1200487: /* DITA2KDB_WS00221C_RESP_PIN_NUMBER_OFFENDER */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_pin_number_offender();
			break;
		case 1200489: /* DITA2KDB_WS00221C_RESP_PIN_UPDATE_NOT_ALLOWED */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_pin_update_not_allowed();
			break;
		case 1200495: /* DITA2KDB_WS00221C_RESP_RETURN_INFO_UNAVAIL */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_return_info_unavail();
			break;
		case 1200497: /* DITA2KDB_WS00221C_RESP_RETURN_SEVERE_ERROR */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_return_severe_error();
			break;
		case 1200500: /* DITA2KDB_WS00221C_RESP_SOCIAL_CODE_NOT_ALLOWED */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_social_code_not_allowed();
			break;
		case 1200501: /* DITA2KDB_WS00221C_RESP_SOCIAL_CODE_NOT_FOUND */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_social_code_not_found();
			break;
		case 1200502: /* DITA2KDB_WS00221C_RESP_SSN_CERTIF_MISSING */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_ssn_certif_missing();
			break;
		case 1200504: /* DITA2KDB_WS00221C_RESP_SUBROUTINE_ERROR */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_subroutine_error();
			break;
		case 1200506: /* DITA2KDB_WS00221C_RESP_TAF_NOT_EQUAL_MASTER */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_taf_not_equal_master();
			break;
		case 1200509: /* DITA2KDB_WS00221C_RESP_TRAN_SHRS_CONTAIN_UNCOLL */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_tran_shrs_contain_uncoll();
			break;
		case 1200512: /* DITA2KDB_WS00221C_RESP_UNABLE_TO_ASSGN_NXT_CUM_N */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_unable_to_assgn_nxt_cum_n();
			break;
		case 1200519: /* DITA2KDB_WS00221C_SUCCESSFUL_OPEN_OPTION_FILE */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_successful_open_option_file();
			break;
		case 1200523: /* DITA2KDB_WS00221C_UNKNOWN_ERROR_CODE */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_unknown_error_code();
			break;
		case 1200524: /* DITA2KDB_WS00221C_VSAM_LOGIC_ERROR */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_vsam_logic_error();
			break;
		case 1200526: /* DITA2KDB_WS00221C_WRONG_RECORD_LNGTH_ON_READ */
			conditionObj = new CBase_Infrastructure_dita2kdb_dita2kdb_ws00221c_wrong_record_lngth_on_read();
			break;
		case 1300003: /* ERR_FIELD_EMPTY */
			conditionObj = new CBase_Infrastructure_ditabuscore_err_field_empty();
			break;
		case 1300011: /* ERR_INVALID_FIELD_LENGTH */
			conditionObj = new CBase_Infrastructure_ditabuscore_err_invalid_field_length();
			break;
		case 1300012: /* ERR_INVALID_FORMAT_TYPE_CODE */
			conditionObj = new CBase_Infrastructure_ditabuscore_err_invalid_format_type_code();
			break;
		case 1300014: /* ERR_INVALID_NUMBER_OF_ADDRESS_LINES */
			conditionObj = new CBase_Infrastructure_ditabuscore_err_invalid_number_of_address_lines();
			break;
		case 1300016: /* ERR_INVALID_STATE_COUNTRY_CODE */
			conditionObj = new CBase_Infrastructure_ditabuscore_err_invalid_state_country_code();
			break;
		case 1300017: /* ERR_INVALID_ZIP_CODE */
			conditionObj = new CBase_Infrastructure_ditabuscore_err_invalid_zip_code();
			break;
		case 1300019: /* ERR_INVALID_ZIPCODE_FOR */
			conditionObj = new CBase_Infrastructure_ditabuscore_err_invalid_zipcode_for();
			break;
		case 1300024: /* ERR_ZIP_CODE_NOT_NUMERIC */
			conditionObj = new CBase_Infrastructure_ditabuscore_err_zip_code_not_numeric();
			break;
		case 1300025: /* ERR_ZIP_CODE_SUFFIX_NOT_ALLOWED */
			conditionObj = new CBase_Infrastructure_ditabuscore_err_zip_code_suffix_not_allowed();
			break;
		case 1300027: /* ERR_ZIP_DLVRY_OFFICE_CDE_NOT_ALLOWED */
			conditionObj = new CBase_Infrastructure_ditabuscore_err_zip_dlvry_office_cde_not_allowed();
			break;
		case 1300028: /* ERR_ZIP_DLVRY_OFFICE_CDE_REQUIRED */
			conditionObj = new CBase_Infrastructure_ditabuscore_err_zip_dlvry_office_cde_required();
			break;
		case 1300029: /* ERR_ZIP_DLVRY_SEQ_NBR_NOT_ALLOWED */
			conditionObj = new CBase_Infrastructure_ditabuscore_err_zip_dlvry_seq_nbr_not_allowed();
			break;
		case 1300030: /* ERR_ZIP_DLVRY_SEQ_NBR_REQUIRED */
			conditionObj = new CBase_Infrastructure_ditabuscore_err_zip_dlvry_seq_nbr_required();
			break;
		case 1300032: /* WRN_LINE_NUMBER */
			conditionObj = new CBase_Infrastructure_ditabuscore_wrn_line_number();
			break;
		case 1300033: /* WRN_S017PE_WRN */
			conditionObj = new CBase_Infrastructure_ditabuscore_wrn_s017pe_wrn();
			break;
		case 1400001: /* GUI_CND_VERSION */
			conditionObj = new CBase_Infrastructure_gui_gui_cnd_version();
			break;
		case 1400007: /* GUI_ERR_DOMODAL_FAILED */
			conditionObj = new CBase_Infrastructure_gui_gui_err_domodal_failed();
			break;
		case 1400008: /* GUI_ERR_UNKNOWN_EXCEPTION */
			conditionObj = new CBase_Infrastructure_gui_gui_err_unknown_exception();
			break;
		case 2100001: /* ERR_MAXIMUM_CONNECTIONS */
			conditionObj = new CBase_Infrastructure_srvbase_err_maximum_connections();
			break;
		case 2100002: /* SRVBASE_CND_VERSION */
			conditionObj = new CBase_Infrastructure_srvbase_srvbase_cnd_version();
			break;
		case 2300001: /* ERR_CBO_NOT_DEFINED */
			conditionObj = new CBase_Infrastructure_xparser_err_cbo_not_defined();
			break;
		case 2300002: /* ERR_CBO_NOT_FOUND_FOR_KEY */
			conditionObj = new CBase_Infrastructure_xparser_err_cbo_not_found_for_key();
			break;
		case 2300003: /* ERR_CREATE_PARSER */
			conditionObj = new CBase_Infrastructure_xparser_err_create_parser();
			break;
		case 2300004: /* ERR_DELETE_PARSER */
			conditionObj = new CBase_Infrastructure_xparser_err_delete_parser();
			break;
		case 2300005: /* ERR_ELEMENT_CANNOT_CONTAIN_CLASS */
			conditionObj = new CBase_Infrastructure_xparser_err_element_cannot_contain_class();
			break;
		case 2300006: /* ERR_ELEMENT_CLASS_ATTRIBUTE_NOT_SPECIFIED */
			conditionObj = new CBase_Infrastructure_xparser_err_element_class_attribute_not_specified();
			break;
		case 2300007: /* ERR_FIELD_NOT_DEFINED */
			conditionObj = new CBase_Infrastructure_xparser_err_field_not_defined();
			break;
		case 2300008: /* ERR_FIELDDETAILS_TAG */
			conditionObj = new CBase_Infrastructure_xparser_err_fielddetails_tag();
			break;
		case 2300009: /* ERR_INVALID_BOOLEAN_ATTRIBUTE */
			conditionObj = new CBase_Infrastructure_xparser_err_invalid_boolean_attribute();
			break;
		case 2300010: /* ERR_INVALID_CACHE_ATTRIBUTE */
			conditionObj = new CBase_Infrastructure_xparser_err_invalid_cache_attribute();
			break;
		case 2300011: /* ERR_INVALID_CBO_ACTION_ATTRIBUTE */
			conditionObj = new CBase_Infrastructure_xparser_err_invalid_cbo_action_attribute();
			break;
		case 2300012: /* ERR_INVALID_ELEMENT_CLASS_ATTRIBUTE */
			conditionObj = new CBase_Infrastructure_xparser_err_invalid_element_class_attribute();
			break;
		case 2300013: /* ERR_INVALID_PROCESS_ACTION_ATTRIBUTE */
			conditionObj = new CBase_Infrastructure_xparser_err_invalid_process_action_attribute();
			break;
		case 2300014: /* ERR_INVALID_RECORD_COUNT_ATTRIBUTE */
			conditionObj = new CBase_Infrastructure_xparser_err_invalid_record_count_attribute();
			break;
		case 2300015: /* ERR_INVALID_ROOT_ELEMENT_NAME */
			conditionObj = new CBase_Infrastructure_xparser_err_invalid_root_element_name();
			break;
		case 2300016: /* ERR_KEY_NOT_SPECIFIED_FOR_LIST */
			conditionObj = new CBase_Infrastructure_xparser_err_key_not_specified_for_list();
			break;
		case 2300017: /* ERR_KEY_SPECIFIED_FOR_NONLIST */
			conditionObj = new CBase_Infrastructure_xparser_err_key_specified_for_nonlist();
			break;
		case 2300018: /* ERR_MULTIPLE_KEYS_NOT_ALLOWED */
			conditionObj = new CBase_Infrastructure_xparser_err_multiple_keys_not_allowed();
			break;
		case 2300019: /* ERR_NEGATIVE_RECORD_COUNT_ATTRIBUTE */
			conditionObj = new CBase_Infrastructure_xparser_err_negative_record_count_attribute();
			break;
		case 2300020: /* ERR_NO_ACTION_TYPE */
			conditionObj = new CBase_Infrastructure_xparser_err_no_action_type();
			break;
		case 2300021: /* ERR_NO_REQUEST_NAME */
			conditionObj = new CBase_Infrastructure_xparser_err_no_request_name();
			break;
		case 2300022: /* ERR_NO_SUCH_ELEMENT */
			conditionObj = new CBase_Infrastructure_xparser_err_no_such_element();
			break;
		case 2300023: /* ERR_TOO_MANY_CNTID_TAGS */
			conditionObj = new CBase_Infrastructure_xparser_err_too_many_cntid_tags();
			break;
		case 2300024: /* ERR_TOO_MANY_FIELDKEY_TAGS */
			conditionObj = new CBase_Infrastructure_xparser_err_too_many_fieldkey_tags();
			break;
		case 2300025: /* ERR_TOO_MANY_USID_TAGS */
			conditionObj = new CBase_Infrastructure_xparser_err_too_many_usid_tags();
			break;
		case 2300026: /* ERR_TOO_MANY_WKSID_TAGS */
			conditionObj = new CBase_Infrastructure_xparser_err_too_many_wksid_tags();
			break;
		case 2300027: /* XP_REQUEST_UNPARSABLE */
			conditionObj = new CBase_Infrastructure_xparser_xp_request_unparsable();
			break;
		case 2300028: /* XP_SAX_PARSE_EXCEPTION */
			conditionObj = new CBase_Infrastructure_xparser_xp_sax_parse_exception();
			break;
		case 2300029: /* XP_UNKNOWN_EXCEPTION */
			conditionObj = new CBase_Infrastructure_xparser_xp_unknown_exception();
			break;
		case 2300030: /* XPARSER_CND_VERSION */
			conditionObj = new CBase_Infrastructure_xparser_xparser_cnd_version();
			break;
        default:
			//assert(0);
			break;
	}

	return conditionObj;
};

CConditionObject* CConditionBuilder::CreateIFastIFastConditionObject(long conditionId) 
{
	CConditionObject* conditionObj = NULL;

	switch(conditionId)
	{
		case 300003: /* ERR_INVALID_TRANS_STATUS */
			conditionObj = new CIFast_IFast_bfdbrkr_err_invalid_trans_status();
			break;
		case 300011: /* ERR_SWITCH_SETTLEMENT_ERROR */
			conditionObj = new CIFast_IFast_bfdbrkr_err_switch_settlement_error();
			break;
		case 600002: /* DIAWD23_COMMENT_FAIL */
			conditionObj = new CIFast_IFast_diawd23_diawd23_comment_fail();
			break;
		case 600003: /* DIAWD23_CONNECT_FAIL */
			conditionObj = new CIFast_IFast_diawd23_diawd23_connect_fail();
			break;
		case 600009: /* DIAWD23_CREATE_AWDOBJ_FAIL */
			conditionObj = new CIFast_IFast_diawd23_diawd23_create_awdobj_fail();
			break;
		case 600010: /* DIAWD23_CREATE_AWDSRC_FAIL */
			conditionObj = new CIFast_IFast_diawd23_diawd23_create_awdsrc_fail();
			break;
		case 600011: /* DIAWD23_INIT_COM_FAIL */
			conditionObj = new CIFast_IFast_diawd23_diawd23_init_com_fail();
			break;
		case 600012: /* DIAWD23_LOGOFF_FAIL */
			conditionObj = new CIFast_IFast_diawd23_diawd23_logoff_fail();
			break;
		case 600013: /* DIAWD23_LOGON_FAIL */
			conditionObj = new CIFast_IFast_diawd23_diawd23_logon_fail();
			break;
		case 600014: /* DIAWD23_OBJECT_LOCKED */
			conditionObj = new CIFast_IFast_diawd23_diawd23_object_locked();
			break;
		case 600015: /* DIAWD23_OLE_ARRAY_FAIL */
			conditionObj = new CIFast_IFast_diawd23_diawd23_ole_array_fail();
			break;
		case 600016: /* DIAWD23_OLE_EXCEPTION */
			conditionObj = new CIFast_IFast_diawd23_diawd23_ole_exception();
			break;
		case 600017: /* DIAWD23_RELATE_FAIL */
			conditionObj = new CIFast_IFast_diawd23_diawd23_relate_fail();
			break;
		case 600018: /* DIAWD23_RETRIEVE_AWDOBJ_FAIL */
			conditionObj = new CIFast_IFast_diawd23_diawd23_retrieve_awdobj_fail();
			break;
		case 600020: /* DIAWD23_UPDATE_AWDOBJ_FAIL */
			conditionObj = new CIFast_IFast_diawd23_diawd23_update_awdobj_fail();
			break;
		case 700001: /* DIAWDI_INVALID_DATE_TIME_PASSED */
			conditionObj = new CIFast_IFast_diawdi_diawdi_invalid_date_time_passed();
			break;
		case 700002: /* DIAWDI_LOAD_MODULE_FAIL */
			conditionObj = new CIFast_IFast_diawdi_diawdi_load_module_fail();
			break;
		case 700003: /* DIAWDI_LOAD_PROC_FAIL */
			conditionObj = new CIFast_IFast_diawdi_diawdi_load_proc_fail();
			break;
		case 700004: /* DIAWDI_LOGON_INVALID_NEW_PASSWORD */
			conditionObj = new CIFast_IFast_diawdi_diawdi_logon_invalid_new_password();
			break;
		case 700005: /* DIAWDI_LOGON_INVALID_OPID */
			conditionObj = new CIFast_IFast_diawdi_diawdi_logon_invalid_opid();
			break;
		case 700006: /* DIAWDI_LOGON_INVALID_PASSWORD */
			conditionObj = new CIFast_IFast_diawdi_diawdi_logon_invalid_password();
			break;
		case 700007: /* DIAWDI_LOGON_NEW_PASSWORD_SAMEAS_OLD */
			conditionObj = new CIFast_IFast_diawdi_diawdi_logon_new_password_sameas_old();
			break;
		case 700008: /* DIAWDI_LOGON_NO_ERROR */
			conditionObj = new CIFast_IFast_diawdi_diawdi_logon_no_error();
			break;
		case 700009: /* DIAWDI_LOGON_OTHER_ERROR */
			conditionObj = new CIFast_IFast_diawdi_diawdi_logon_other_error();
			break;
		case 700010: /* DIAWDI_LOGON_PASSWORD_EXPIRED */
			conditionObj = new CIFast_IFast_diawdi_diawdi_logon_password_expired();
			break;
		case 700011: /* DIAWDI_LOGON_USER_ALREADY_LOGGED_ON */
			conditionObj = new CIFast_IFast_diawdi_diawdi_logon_user_already_logged_on();
			break;
		case 700012: /* DIAWDI_LOGON_USER_DISABLED */
			conditionObj = new CIFast_IFast_diawdi_diawdi_logon_user_disabled();
			break;
		case 800001: /* DICORE_DATE_FORMAT_NOT_RECOGNIZED */
			conditionObj = new CIFast_IFast_dicbocore_dicore_date_format_not_recognized();
			break;
		case 800002: /* DICORE_DATE_INVALID */
			conditionObj = new CIFast_IFast_dicbocore_dicore_date_invalid();
			break;
		case 800003: /* ERR_CBE_LABEL_INVALID_FOR_UPDATE */
			conditionObj = new CIFast_IFast_dicbocore_err_cbe_label_invalid_for_update();
			break;
		case 800004: /* ERR_COPY_OBJECT_NOT_INITIALIZED */
			conditionObj = new CIFast_IFast_dicbocore_err_copy_object_not_initialized();
			break;
		case 800005: /* ERR_EVENT_MIXING_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_dicbocore_err_event_mixing_not_allowed();
			break;
		case 800006: /* ERR_FIELD_CHECKPOINT_NOT_AVAILABLE */
			conditionObj = new CIFast_IFast_dicbocore_err_field_checkpoint_not_available();
			break;
		case 800007: /* ERR_FIELD_GROUP_NOT_FOUND */
			conditionObj = new CIFast_IFast_dicbocore_err_field_group_not_found();
			break;
		case 800008: /* ERR_FIELD_IS_OVER_MAXIMUM_ALLOWED */
			conditionObj = new CIFast_IFast_dicbocore_err_field_is_over_maximum_allowed();
			break;
		case 800009: /* ERR_FIELD_IS_UNDER_MINIMUM_ALLOWED */
			conditionObj = new CIFast_IFast_dicbocore_err_field_is_under_minimum_allowed();
			break;
		case 800010: /* ERR_FIELD_MAX_LEN_EXCEEDED */
			conditionObj = new CIFast_IFast_dicbocore_err_field_max_len_exceeded();
			break;
		case 800011: /* ERR_FIELD_READ_ONLY */
			conditionObj = new CIFast_IFast_dicbocore_err_field_read_only();
			break;
		case 800012: /* ERR_FIELD_REQUIRED */
			conditionObj = new CIFast_IFast_dicbocore_err_field_required();
			break;
		case 800013: /* ERR_FIELD_VALUE_NOT_VALID */
			conditionObj = new CIFast_IFast_dicbocore_err_field_value_not_valid();
			break;
		case 800014: /* ERR_FLD_NOT_VALIDATED */
			conditionObj = new CIFast_IFast_dicbocore_err_fld_not_validated();
			break;
		case 800015: /* ERR_FORMAT_NOT_RECOGNIZED */
			conditionObj = new CIFast_IFast_dicbocore_err_format_not_recognized();
			break;
		case 800016: /* ERR_HOLIDAY_FILE */
			conditionObj = new CIFast_IFast_dicbocore_err_holiday_file();
			break;
		case 800017: /* ERR_IMPROPER_CLASS_FIELD_VALID_VALUES */
			conditionObj = new CIFast_IFast_dicbocore_err_improper_class_field_valid_values();
			break;
		case 800018: /* ERR_INCOMPATIBLE_REGISTERED_OBJECTS */
			conditionObj = new CIFast_IFast_dicbocore_err_incompatible_registered_objects();
			break;
		case 800019: /* ERR_INDEX_OUT_OF_RANGE */
			conditionObj = new CIFast_IFast_dicbocore_err_index_out_of_range();
			break;
		case 800020: /* ERR_INVALID_BATCH_WORKORDER_EVENT */
			conditionObj = new CIFast_IFast_dicbocore_err_invalid_batch_workorder_event();
			break;
		case 800021: /* ERR_INVALID_FIELD_ID */
			conditionObj = new CIFast_IFast_dicbocore_err_invalid_field_id();
			break;
		case 800022: /* ERR_INVALID_FIELD_TAG */
			conditionObj = new CIFast_IFast_dicbocore_err_invalid_field_tag();
			break;
		case 800023: /* ERR_INVALID_FIELD_TYPE */
			conditionObj = new CIFast_IFast_dicbocore_err_invalid_field_type();
			break;
		case 800024: /* ERR_INVALID_ITERATOR_POSITION */
			conditionObj = new CIFast_IFast_dicbocore_err_invalid_iterator_position();
			break;
		case 800025: /* ERR_INVALID_METHOD_CALL */
			conditionObj = new CIFast_IFast_dicbocore_err_invalid_method_call();
			break;
		case 800026: /* ERR_INVALID_OBJ_POINTER */
			conditionObj = new CIFast_IFast_dicbocore_err_invalid_obj_pointer();
			break;
		case 800027: /* ERR_INVALID_TIME */
			conditionObj = new CIFast_IFast_dicbocore_err_invalid_time();
			break;
		case 800028: /* ERR_INVALID_USE_OF_OFFICIAL_GROUP */
			conditionObj = new CIFast_IFast_dicbocore_err_invalid_use_of_official_group();
			break;
		case 800029: /* ERR_KEY_NOT_FOUND */
			conditionObj = new CIFast_IFast_dicbocore_err_key_not_found();
			break;
		case 800030: /* ERR_MFDATE_INVALID */
			conditionObj = new CIFast_IFast_dicbocore_err_mfdate_invalid();
			break;
		case 800031: /* ERR_MIN_VALUE_GREATER_THAN_MAX */
			conditionObj = new CIFast_IFast_dicbocore_err_min_value_greater_than_max();
			break;
		case 800032: /* ERR_MULTIPLE_INIT_CALLS */
			conditionObj = new CIFast_IFast_dicbocore_err_multiple_init_calls();
			break;
		case 800033: /* ERR_NO_ADDITIONAL_REPEAT_RECORDS */
			conditionObj = new CIFast_IFast_dicbocore_err_no_additional_repeat_records();
			break;
		case 800034: /* ERR_NO_DELETE_OBJECT_ALLOWED */
			conditionObj = new CIFast_IFast_dicbocore_err_no_delete_object_allowed();
			break;
		case 800035: /* ERR_NO_REGISTERED_OBJECT */
			conditionObj = new CIFast_IFast_dicbocore_err_no_registered_object();
			break;
		case 800036: /* ERR_NO_UPDATES_TO_APPLY */
			conditionObj = new CIFast_IFast_dicbocore_err_no_updates_to_apply();
			break;
		case 800037: /* ERR_NO_VIEW_DATA_OBJECTS_REGISTERED */
			conditionObj = new CIFast_IFast_dicbocore_err_no_view_data_objects_registered();
			break;
		case 800038: /* ERR_NO_VIEW_DATA_REPEATS */
			conditionObj = new CIFast_IFast_dicbocore_err_no_view_data_repeats();
			break;
		case 800039: /* ERR_OBJECT_COPY_ONLY */
			conditionObj = new CIFast_IFast_dicbocore_err_object_copy_only();
			break;
		case 800040: /* ERR_OBJECT_DOES_NOT_ALLOW_GROUPS */
			conditionObj = new CIFast_IFast_dicbocore_err_object_does_not_allow_groups();
			break;
		case 800041: /* ERR_OBJECT_INVALID_TYPE */
			conditionObj = new CIFast_IFast_dicbocore_err_object_invalid_type();
			break;
		case 800042: /* ERR_OBJECT_NOT_COPYABLE */
			conditionObj = new CIFast_IFast_dicbocore_err_object_not_copyable();
			break;
		case 800043: /* ERR_OBJECT_NOT_FOUND */
			conditionObj = new CIFast_IFast_dicbocore_err_object_not_found();
			break;
		case 800045: /* ERR_OBJECT_OWNED_BY_LIST */
			conditionObj = new CIFast_IFast_dicbocore_err_object_owned_by_list();
			break;
		case 800046: /* ERR_OBJECT_PRIVATE_USE */
			conditionObj = new CIFast_IFast_dicbocore_err_object_private_use();
			break;
		case 800047: /* ERR_OBJECT_PTR_ACCESS_ONLY */
			conditionObj = new CIFast_IFast_dicbocore_err_object_ptr_access_only();
			break;
		case 800048: /* ERR_OBJECT_READ_ONLY */
			conditionObj = new CIFast_IFast_dicbocore_err_object_read_only();
			break;
		case 800049: /* ERR_OBJECT_REQUIRED */
			conditionObj = new CIFast_IFast_dicbocore_err_object_required();
			break;
		case 800050: /* ERR_RETREIVING_DATE */
			conditionObj = new CIFast_IFast_dicbocore_err_retreiving_date();
			break;
		case 800051: /* ERR_SEARCH_NOT_FOUND */
			conditionObj = new CIFast_IFast_dicbocore_err_search_not_found();
			break;
		case 800052: /* ERR_STRING_EXCEPTION */
			conditionObj = new CIFast_IFast_dicbocore_err_string_exception();
			break;
		case 800053: /* ERR_UNABLE_TO_RETRIEVE_LABEL_DATA */
			conditionObj = new CIFast_IFast_dicbocore_err_unable_to_retrieve_label_data();
			break;
		case 800054: /* ERR_UNKNOWN_EXCEPTION */
			conditionObj = new CIFast_IFast_dicbocore_err_unknown_exception();
			break;
		case 800055: /* ERR_VIEW_MGR */
			conditionObj = new CIFast_IFast_dicbocore_err_view_mgr();
			break;
		case 800056: /* ERR_WORKORDER_CBE_ALREADY_REGISTERED */
			conditionObj = new CIFast_IFast_dicbocore_err_workorder_cbe_already_registered();
			break;
		case 800057: /* ERR_WORKORDER_CBEKEY_DUPLICATED */
			conditionObj = new CIFast_IFast_dicbocore_err_workorder_cbekey_duplicated();
			break;
		case 800058: /* ERR_WORKORDER_CBEKEY_NOT_FOUND */
			conditionObj = new CIFast_IFast_dicbocore_err_workorder_cbekey_not_found();
			break;
		case 800059: /* WRN_OBJECT_DOES_NOT_ALLOW_GROUPS */
			conditionObj = new CIFast_IFast_dicbocore_wrn_object_does_not_allow_groups();
			break;
		case 900001: /* BASE_ALLOC_FAIL */
			conditionObj = new CIFast_IFast_dicore_base_alloc_fail();
			break;
		case 900003: /* DICORE_BUFFER_SIZE_TOO_SMALL */
			conditionObj = new CIFast_IFast_dicore_dicore_buffer_size_too_small();
			break;
		case 900008: /* DICORE_DATE_STRING_INVALID */
			conditionObj = new CIFast_IFast_dicore_dicore_date_string_invalid();
			break;
		case 900009: /* DICORE_DELETE_KEY_FAIL */
			conditionObj = new CIFast_IFast_dicore_dicore_delete_key_fail();
			break;
		case 900010: /* DICORE_DELETE_VALUE_FAIL */
			conditionObj = new CIFast_IFast_dicore_dicore_delete_value_fail();
			break;
		case 900011: /* DICORE_DIVIDE_BY_ZERO */
			conditionObj = new CIFast_IFast_dicore_dicore_divide_by_zero();
			break;
		case 900019: /* DICORE_HOSTMASKS_NOT_DEFINED_IN_REGISTRY */
			conditionObj = new CIFast_IFast_dicore_dicore_hostmasks_not_defined_in_registry();
			break;
		case 900021: /* DICORE_KEY_NOT_FOUND */
			conditionObj = new CIFast_IFast_dicore_dicore_key_not_found();
			break;
		case 900029: /* DICORE_PARSE_IDI_MISSING_SEPARATOR */
			conditionObj = new CIFast_IFast_dicore_dicore_parse_idi_missing_separator();
			break;
		case 900030: /* DICORE_PARSE_IDI_MISSING_TAG_NAME */
			conditionObj = new CIFast_IFast_dicore_dicore_parse_idi_missing_tag_name();
			break;
		case 900031: /* DICORE_PARSE_IDI_MISSING_TERMINATOR */
			conditionObj = new CIFast_IFast_dicore_dicore_parse_idi_missing_terminator();
			break;
		case 900032: /* DICORE_PARSE_IDI_MISSING_VALUE */
			conditionObj = new CIFast_IFast_dicore_dicore_parse_idi_missing_value();
			break;
		case 900038: /* DICORE_SAVE_KEY_FAIL */
			conditionObj = new CIFast_IFast_dicore_dicore_save_key_fail();
			break;
		case 900039: /* DICORE_SAVE_VALUE_FAIL */
			conditionObj = new CIFast_IFast_dicore_dicore_save_value_fail();
			break;
		case 900041: /* DICORE_VMAPPREQUEST_TIMEOUT */
			conditionObj = new CIFast_IFast_dicore_dicore_vmapprequest_timeout();
			break;
		case 900045: /* DICORE_VMNOTIFYWIN_FAIL */
			conditionObj = new CIFast_IFast_dicore_dicore_vmnotifywin_fail();
			break;
		case 900047: /* DICORE_VMREQUEST_CALLBACK_CONDITIONEXCEPTION_THROWN */
			conditionObj = new CIFast_IFast_dicore_dicore_vmrequest_callback_conditionexception_thrown();
			break;
		case 900048: /* DICORE_VMREQUEST_CALLBACK_ERROR_CONDITION */
			conditionObj = new CIFast_IFast_dicore_dicore_vmrequest_callback_error_condition();
			break;
		case 900049: /* DICORE_VMREQUEST_CALLBACK_UNKNOWN_EXCEPTION_THROWN */
			conditionObj = new CIFast_IFast_dicore_dicore_vmrequest_callback_unknown_exception_thrown();
			break;
		case 900057: /* ERR_KYC_DATA_NOT_FOUND */
			conditionObj = new CIFast_IFast_dicore_err_kyc_data_not_found();
			break;
		case 900058: /* VIRTUAL_BASE_METHOD_NOT_SUPPORTED */
			conditionObj = new CIFast_IFast_dicore_virtual_base_method_not_supported();
			break;
		case 900059: /* WARN_INPUTDATATYPE_EMPTY */
			conditionObj = new CIFast_IFast_dicore_warn_inputdatatype_empty();
			break;
		case 1000014: /* DIDBRKR_I18N_MASK_FORMAT_ERROR */
			conditionObj = new CIFast_IFast_didbrkr_didbrkr_i18n_mask_format_error();
			break;
		case 1000018: /* DIDBRKR_INVALID_REDEFINE */
			conditionObj = new CIFast_IFast_didbrkr_didbrkr_invalid_redefine();
			break;
		case 1000028: /* DIDBRKR_READ_SIZE_FAILED */
			conditionObj = new CIFast_IFast_didbrkr_didbrkr_read_size_failed();
			break;
		case 1000029: /* DIDBRKR_REDEFINE_HAS_DUPLICATE */
			conditionObj = new CIFast_IFast_didbrkr_didbrkr_redefine_has_duplicate();
			break;
		case 1000030: /* DIDBRKR_REDEFINE_LENGTH_MISMATCH */
			conditionObj = new CIFast_IFast_didbrkr_didbrkr_redefine_length_mismatch();
			break;
		case 1000031: /* DIDBRKR_REDEFINE_REPEATS_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_didbrkr_didbrkr_redefine_repeats_not_allowed();
			break;
		case 1000034: /* DIDBRKR_TARGET_LOCALE_MISSING */
			conditionObj = new CIFast_IFast_didbrkr_didbrkr_target_locale_missing();
			break;
		case 1100002: /* DIODBC_ERROR */
			conditionObj = new CIFast_IFast_disessn_diodbc_error();
			break;
		case 1100004: /* DISESSN_AWD_NOT_LOGGED_ON */
			conditionObj = new CIFast_IFast_disessn_disessn_awd_not_logged_on();
			break;
		case 1100005: /* DISESSN_AWD_WORK_CREATED */
			conditionObj = new CIFast_IFast_disessn_disessn_awd_work_created();
			break;
		case 1100006: /* DISESSN_CHILD_NOT_REMOVED */
			conditionObj = new CIFast_IFast_disessn_disessn_child_not_removed();
			break;
		case 1100007: /* DISESSN_DEFAULT_LABEL_USED */
			conditionObj = new CIFast_IFast_disessn_disessn_default_label_used();
			break;
		case 1100008: /* DISESSN_UNDEFINED_AWD_PARAMETER */
			conditionObj = new CIFast_IFast_disessn_disessn_undefined_awd_parameter();
			break;
		case 1200001: /* DITA2KDB_A52_INFO_UNAVAIL */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_a52_info_unavail();
			break;
		case 1200002: /* DITA2KDB_A52_REC_NOT_FOUND */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_a52_rec_not_found();
			break;
		case 1200003: /* DITA2KDB_A58_INFO_UNAVAIL */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_a58_info_unavail();
			break;
		case 1200004: /* DITA2KDB_A58_REC_NOT_FOUND */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_a58_rec_not_found();
			break;
		case 1200005: /* DITA2KDB_A87_INFO_UNAVAIL */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_a87_info_unavail();
			break;
		case 1200006: /* DITA2KDB_A87_REC_NOT_FOUND */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_a87_rec_not_found();
			break;
		case 1200007: /* DITA2KDB_A90_INFO_UNAVAIL */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_a90_info_unavail();
			break;
		case 1200008: /* DITA2KDB_A90_REC_NOT_FOUND */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_a90_rec_not_found();
			break;
		case 1200009: /* DITA2KDB_ALREADY_SIGNED_ON */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_already_signed_on();
			break;
		case 1200012: /* DITA2KDB_AUDIT_FILE_BAD_OPEN */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_audit_file_bad_open();
			break;
		case 1200013: /* DITA2KDB_AUDIT_REC_NOT_WRITTEN */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_audit_rec_not_written();
			break;
		case 1200014: /* DITA2KDB_AUTHORIZATION_FAILED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_authorization_failed();
			break;
		case 1200015: /* DITA2KDB_B06_REC_NOT_FOUND */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_b06_rec_not_found();
			break;
		case 1200016: /* DITA2KDB_B07_REC_NOT_FOUND */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_b07_rec_not_found();
			break;
		case 1200017: /* DITA2KDB_B08_RECORD_NOT_FOUND */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_b08_record_not_found();
			break;
		case 1200018: /* DITA2KDB_B15_INFO_UNAVAIL */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_b15_info_unavail();
			break;
		case 1200019: /* DITA2KDB_B15_REC_NOT_FOUND */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_b15_rec_not_found();
			break;
		case 1200023: /* DITA2KDB_CANT_INIT_VIEW_THREAD */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_cant_init_view_thread();
			break;
		case 1200025: /* DITA2KDB_CANT_READ_DATA_FILE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_cant_read_data_file();
			break;
		case 1200026: /* DITA2KDB_CHANGED_BY_DIFF_OPER */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_changed_by_diff_oper();
			break;
		case 1200027: /* DITA2KDB_CHG_REC_NOT_FOUND */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_chg_rec_not_found();
			break;
		case 1200028: /* DITA2KDB_CURR_A79_NOT_DEL */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_curr_a79_not_del();
			break;
		case 1200029: /* DITA2KDB_DATA_NOT_FOUND */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_data_not_found();
			break;
		case 1200030: /* DITA2KDB_DEFAULT_VALUE_USED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_default_value_used();
			break;
		case 1200031: /* DITA2KDB_DEL_REC_NOT_FOUND */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_del_rec_not_found();
			break;
		case 1200032: /* DITA2KDB_DLR_NOT_AUTHORIZED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_dlr_not_authorized();
			break;
		case 1200033: /* DITA2KDB_END_OF_DATA */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_end_of_data();
			break;
		case 1200034: /* DITA2KDB_F16_REC_NOT_FOUND */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_f16_rec_not_found();
			break;
		case 1200035: /* DITA2KDB_F17_REC_NOT_FOUND */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_f17_rec_not_found();
			break;
		case 1200036: /* DITA2KDB_FAILED_TO_CONNECT_WITH_LOGON_MGR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_failed_to_connect_with_logon_mgr();
			break;
		case 1200038: /* DITA2KDB_INVALID_ACCT_NUM */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_acct_num();
			break;
		case 1200039: /* DITA2KDB_INVALID_ACCUM_YEARS */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_accum_years();
			break;
		case 1200040: /* DITA2KDB_INVALID_ALPHA_CODE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_alpha_code();
			break;
		case 1200041: /* DITA2KDB_INVALID_ARRAY_ROWS */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_array_rows();
			break;
		case 1200043: /* DITA2KDB_INVALID_BATCH_NUM */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_batch_num();
			break;
		case 1200045: /* DITA2KDB_INVALID_CERT_NUM */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_cert_num();
			break;
		case 1200046: /* DITA2KDB_INVALID_CORR_CODE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_corr_code();
			break;
		case 1200047: /* DITA2KDB_INVALID_CUMDISC */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_cumdisc();
			break;
		case 1200048: /* DITA2KDB_INVALID_CUMDISC_PLAN */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_cumdisc_plan();
			break;
		case 1200049: /* DITA2KDB_INVALID_DATA */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_data();
			break;
		case 1200050: /* DITA2KDB_INVALID_DATA_REQUEST */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_data_request();
			break;
		case 1200051: /* DITA2KDB_INVALID_DATE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_date();
			break;
		case 1200053: /* DITA2KDB_INVALID_DEALER_BRANCH */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_dealer_branch();
			break;
		case 1200054: /* DITA2KDB_INVALID_DEALER_NUM */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_dealer_num();
			break;
		case 1200055: /* DITA2KDB_INVALID_DEBIT_CARD */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_debit_card();
			break;
		case 1200056: /* DITA2KDB_INVALID_DEBIT_TYPE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_debit_type();
			break;
		case 1200057: /* DITA2KDB_INVALID_DLR_BR_SUMMARY */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_dlr_br_summary();
			break;
		case 1200058: /* DITA2KDB_INVALID_DLR_BRN_SEC */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_dlr_brn_sec();
			break;
		case 1200059: /* DITA2KDB_INVALID_DLR_SUMMARY */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_dlr_summary();
			break;
		case 1200060: /* DITA2KDB_INVALID_DSCS_APPREC */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_dscs_apprec();
			break;
		case 1200061: /* DITA2KDB_INVALID_EXCH_PUR_CANC */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_exch_pur_canc();
			break;
		case 1200062: /* DITA2KDB_INVALID_EXCH_RED_CANC */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_exch_red_canc();
			break;
		case 1200064: /* DITA2KDB_INVALID_FID_ACCOUNT */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_fid_account();
			break;
		case 1200065: /* DITA2KDB_INVALID_FRONT_END */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_front_end();
			break;
		case 1200066: /* DITA2KDB_INVALID_FUNCTION_TYPE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_function_type();
			break;
		case 1200067: /* DITA2KDB_INVALID_FUND_CODE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_fund_code();
			break;
		case 1200071: /* DITA2KDB_INVALID_LOI_NUM */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_loi_num();
			break;
		case 1200072: /* DITA2KDB_INVALID_MF_TRAN_ID */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_mf_tran_id();
			break;
		case 1200073: /* DITA2KDB_INVALID_MGMT_CODE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_mgmt_code();
			break;
		case 1200074: /* DITA2KDB_INVALID_MONTHLY_ACCUM */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_monthly_accum();
			break;
		case 1200075: /* DITA2KDB_INVALID_NET_CHG */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_net_chg();
			break;
		case 1200076: /* DITA2KDB_INVALID_OPER_ID */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_oper_id();
			break;
		case 1200077: /* DITA2KDB_INVALID_PAF_BUCKET */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_paf_bucket();
			break;
		case 1200078: /* DITA2KDB_INVALID_PASSWORD */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_password();
			break;
		case 1200079: /* DITA2KDB_INVALID_PRE_AGREEMENT */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_pre_agreement();
			break;
		case 1200080: /* DITA2KDB_INVALID_PRICE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_price();
			break;
		case 1200081: /* DITA2KDB_INVALID_PST_AGREEMENT */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_pst_agreement();
			break;
		case 1200082: /* DITA2KDB_INVALID_PURCH_CANCEL */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_purch_cancel();
			break;
		case 1200084: /* DITA2KDB_INVALID_REDMPT_CANCEL */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_redmpt_cancel();
			break;
		case 1200085: /* DITA2KDB_INVALID_REIN_DOLLAR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_rein_dollar();
			break;
		case 1200086: /* DITA2KDB_INVALID_REIN_SHARES */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_rein_shares();
			break;
		case 1200087: /* DITA2KDB_INVALID_REQUEST_CNT */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_request_cnt();
			break;
		case 1200088: /* DITA2KDB_INVALID_RES_STATE_CODE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_res_state_code();
			break;
		case 1200090: /* DITA2KDB_INVALID_START_MONTH */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_start_month();
			break;
		case 1200091: /* DITA2KDB_INVALID_START_YEAR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_start_year();
			break;
		case 1200092: /* DITA2KDB_INVALID_TAX_ID_NUM */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_tax_id_num();
			break;
		case 1200093: /* DITA2KDB_INVALID_TRANS_NUM */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_trans_num();
			break;
		case 1200094: /* DITA2KDB_INVALID_VIEW */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_view();
			break;
		case 1200095: /* DITA2KDB_INVALID_YIELD_DATE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_invalid_yield_date();
			break;
		case 1200096: /* DITA2KDB_MAX_IO_LIMIT */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_max_io_limit();
			break;
		case 1200097: /* DITA2KDB_MGMT_CO_NOT_FOUND */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_mgmt_co_not_found();
			break;
		case 1200099: /* DITA2KDB_NO_A53_DUMMY_REC */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_no_a53_dummy_rec();
			break;
		case 1200100: /* DITA2KDB_NO_A53_FOR_VERIFY_DTE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_no_a53_for_verify_dte();
			break;
		case 1200101: /* DITA2KDB_NO_A56_REC_FOUND */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_no_a56_rec_found();
			break;
		case 1200102: /* DITA2KDB_NO_A79_FOR_VERIFY_DTE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_no_a79_for_verify_dte();
			break;
		case 1200105: /* DITA2KDB_NO_SYSTEMS */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_no_systems();
			break;
		case 1200106: /* DITA2KDB_NO_UPDATE_DETECTED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_no_update_detected();
			break;
		case 1200107: /* DITA2KDB_NO_UPDATES_TO_APPLY */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_no_updates_to_apply();
			break;
		case 1200108: /* DITA2KDB_NOT_AUTHORIZED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_not_authorized();
			break;
		case 1200109: /* DITA2KDB_NOT_SIGNED_ON */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_not_signed_on();
			break;
		case 1200110: /* DITA2KDB_OPER_DISABLED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_oper_disabled();
			break;
		case 1200111: /* DITA2KDB_OPER_NOT_AUTH_DEALER */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_oper_not_auth_dealer();
			break;
		case 1200112: /* DITA2KDB_OPER_NOT_AUTH_DLR_BR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_oper_not_auth_dlr_br();
			break;
		case 1200113: /* DITA2KDB_PASSWORD_EXPIRED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_password_expired();
			break;
		case 1200114: /* DITA2KDB_PASSWORD_TOO_SIMILAR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_password_too_similar();
			break;
		case 1200115: /* DITA2KDB_POTENTIAL_DUPLICATE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_potential_duplicate();
			break;
		case 1200116: /* DITA2KDB_RECORD_ALREADY_EXIST */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_record_already_exist();
			break;
		case 1200117: /* DITA2KDB_RECORD_UNAVAIL */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_record_unavail();
			break;
		case 1200118: /* DITA2KDB_RETURN_ACCT_EXISTS */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_return_acct_exists();
			break;
		case 1200119: /* DITA2KDB_RETURN_INFO_UNAVAIL */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_return_info_unavail();
			break;
		case 1200120: /* DITA2KDB_RETURN_NASU_ACCT */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_return_nasu_acct();
			break;
		case 1200121: /* DITA2KDB_RETURN_VIEW_ERROR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_return_view_error();
			break;
		case 1200122: /* DITA2KDB_RETURN_WITH_ERRORS */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_return_with_errors();
			break;
		case 1200123: /* DITA2KDB_S0_MASTER_NOT_FOUND */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_s0_master_not_found();
			break;
		case 1200124: /* DITA2KDB_SEVERE_ERROR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_severe_error();
			break;
		case 1200125: /* DITA2KDB_STS_ERROR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_sts_error();
			break;
		case 1200126: /* DITA2KDB_SYSTEM_DOWN */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_system_down();
			break;
		case 1200127: /* DITA2KDB_SYSTEM_ID_ERROR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_system_id_error();
			break;
		case 1200128: /* DITA2KDB_SYSTRAN_AGR_EXIST */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_systran_agr_exist();
			break;
		case 1200129: /* DITA2KDB_SYSTRAN_INSTR_EXIST */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_systran_instr_exist();
			break;
		case 1200130: /* DITA2KDB_SYSTRAN_NO_P47 */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_systran_no_p47();
			break;
		case 1200131: /* DITA2KDB_SYSTRAN_SEVERE_ERROR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_systran_severe_error();
			break;
		case 1200132: /* DITA2KDB_TAF_NOT_EQUAL_MASTER */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_taf_not_equal_master();
			break;
		case 1200133: /* DITA2KDB_TRANS_BACKED_OUT */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_trans_backed_out();
			break;
		case 1200135: /* DITA2KDB_UNKNOWN_ERROR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_unknown_error();
			break;
		case 1200136: /* DITA2KDB_UNKNOWN_VIEW_ERROR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_unknown_view_error();
			break;
		case 1200137: /* DITA2KDB_UPDATES_MFL_ONLY */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_updates_mfl_only();
			break;
		case 1200138: /* DITA2KDB_VM_ERROR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_vm_error();
			break;
		case 1200139: /* DITA2KDB_VM_MORE_DATA */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_vm_more_data();
			break;
		case 1200140: /* DITA2KDB_VM_THREW */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_vm_threw();
			break;
		case 1200141: /* DITA2KDB_VMAPPREQUEST_ERROR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_vmapprequest_error();
			break;
		case 1200142: /* DITA2KDB_VMCONNECT_ERROR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_vmconnect_error();
			break;
		case 1200143: /* DITA2KDB_VMDISCONNECT_ERROR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_vmdisconnect_error();
			break;
		case 1200144: /* DITA2KDB_VMNOTIFYSEM_ERROR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_vmnotifysem_error();
			break;
		case 1200145: /* DITA2KDB_VMNOTIFYWIN_DUPLICATE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_vmnotifywin_duplicate();
			break;
		case 1200146: /* DITA2KDB_VMNOTIFYWIN_MISSING */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_vmnotifywin_missing();
			break;
		case 1200147: /* DITA2KDB_VMREADRESPONSE_ERROR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_vmreadresponse_error();
			break;
		case 1200148: /* DITA2KDB_VMREQ_FAILED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_vmreq_failed();
			break;
		case 1200149: /* DITA2KDB_VMREQUEST_ERROR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_vmrequest_error();
			break;
		case 1200150: /* DITA2KDB_VMREQUEST_SEND_FAILED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_vmrequest_send_failed();
			break;
		case 1200151: /* DITA2KDB_VMREQUEST_SEND_FAILED2 */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_vmrequest_send_failed2();
			break;
		case 1200152: /* DITA2KDB_WS00221C_ACCESS_DENIED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_access_denied();
			break;
		case 1200153: /* DITA2KDB_WS00221C_AUTH_FUNCTIONS_DISABLED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_auth_functions_disabled();
			break;
		case 1200154: /* DITA2KDB_WS00221C_CLOSE_FOR_FILE_NOT_OPENED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_close_for_file_not_opened();
			break;
		case 1200155: /* DITA2KDB_WS00221C_CONNECT_AUTH_FAILURE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_connect_auth_failure();
			break;
		case 1200156: /* DITA2KDB_WS00221C_CONNECT_INTERNAL_ERROR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_connect_internal_error();
			break;
		case 1200157: /* DITA2KDB_WS00221C_CONNECT_LOST */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_connect_lost();
			break;
		case 1200158: /* DITA2KDB_WS00221C_CONNECT_NOT_ESTABLISHED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_connect_not_established();
			break;
		case 1200159: /* DITA2KDB_WS00221C_CONSTRAINT_NAME_RESTRICTS_DELT */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_constraint_name_restricts_delt();
			break;
		case 1200160: /* DITA2KDB_WS00221C_CUM_DISC_INV_BELOW_THRESHOLD */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_cum_disc_inv_below_threshold();
			break;
		case 1200161: /* DITA2KDB_WS00221C_DATA_SET_ID_ERROR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_data_set_id_error();
			break;
		case 1200162: /* DITA2KDB_WS00221C_DCB_CONFLICT_PRGM_TO_FILE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_dcb_conflict_prgm_to_file();
			break;
		case 1200163: /* DITA2KDB_WS00221C_DEADLOCK_ROLLED_BCK */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_deadlock_rolled_bck();
			break;
		case 1200164: /* DITA2KDB_WS00221C_DEADLOCK_TIMEOUT_ROLL_BCK */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_deadlock_timeout_roll_bck();
			break;
		case 1200165: /* DITA2KDB_WS00221C_DIFFERENT_RECORD_LENGTH */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_different_record_length();
			break;
		case 1200166: /* DITA2KDB_WS00221C_DUPLICATE_KEY */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_duplicate_key();
			break;
		case 1200167: /* DITA2KDB_WS00221C_DUPLICATE_KEY_ERROR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_duplicate_key_error();
			break;
		case 1200168: /* DITA2KDB_WS00221C_DUPLICATE_KEY_OK */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_duplicate_key_ok();
			break;
		case 1200169: /* DITA2KDB_WS00221C_EXCEPTION_ERROR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_exception_error();
			break;
		case 1200170: /* DITA2KDB_WS00221C_FILE_ACCESS_ERROR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_file_access_error();
			break;
		case 1200171: /* DITA2KDB_WS00221C_FILE_AT_END */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_file_at_end();
			break;
		case 1200172: /* DITA2KDB_WS00221C_FILE_INFO_MISSING */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_file_info_missing();
			break;
		case 1200173: /* DITA2KDB_WS00221C_FILE_NOT_CLOSED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_file_not_closed();
			break;
		case 1200174: /* DITA2KDB_WS00221C_FILE_NOT_ON_REEL */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_file_not_on_reel();
			break;
		case 1200175: /* DITA2KDB_WS00221C_FILE_OK */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_file_ok();
			break;
		case 1200176: /* DITA2KDB_WS00221C_FILE_TYPE_NOT_SUPPORTED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_file_type_not_supported();
			break;
		case 1200177: /* DITA2KDB_WS00221C_FUNCTION_DISABLED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_function_disabled();
			break;
		case 1200178: /* DITA2KDB_WS00221C_INVALID_AUTHORIZATION */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_invalid_authorization();
			break;
		case 1200179: /* DITA2KDB_WS00221C_INVALID_OPERATION_AUTHORITY_1 */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_invalid_operation_authority_1();
			break;
		case 1200180: /* DITA2KDB_WS00221C_INVALID_OPERATION_AUTHORITY_2 */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_invalid_operation_authority_2();
			break;
		case 1200181: /* DITA2KDB_WS00221C_INVALID_UPDATE_FOREIGN_KEY */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_invalid_update_foreign_key();
			break;
		case 1200182: /* DITA2KDB_WS00221C_LOAD_TIMESTAMP_DIFFERENT */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_load_timestamp_different();
			break;
		case 1200183: /* DITA2KDB_WS00221C_MISSING_DD_CARD */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_missing_dd_card();
			break;
		case 1200184: /* DITA2KDB_WS00221C_NLS_ERROR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_nls_error();
			break;
		case 1200185: /* DITA2KDB_WS00221C_NO_CRP_SET */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_no_crp_set();
			break;
		case 1200186: /* DITA2KDB_WS00221C_NO_RECORD_FOUND */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_no_record_found();
			break;
		case 1200187: /* DITA2KDB_WS00221C_NO_SPACE_AVAILABLE_1 */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_no_space_available_1();
			break;
		case 1200188: /* DITA2KDB_WS00221C_NO_SPACE_AVAILABLE_2 */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_no_space_available_2();
			break;
		case 1200189: /* DITA2KDB_WS00221C_NON_OPTIONAL_FILE_NOT_PRES */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_non_optional_file_not_pres();
			break;
		case 1200190: /* DITA2KDB_WS00221C_NOT_PRECEDED_BY_GOOD_READ */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_not_preceded_by_good_read();
			break;
		case 1200191: /* DITA2KDB_WS00221C_NULL_VALUE_CANNOT_BE_ASSIGNED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_null_value_cannot_be_assigned();
			break;
		case 1200192: /* DITA2KDB_WS00221C_OBJECT_DELETED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_object_deleted();
			break;
		case 1200193: /* DITA2KDB_WS00221C_OPEN_AFTER_CLOSE_WITH_LOCK */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_open_after_close_with_lock();
			break;
		case 1200194: /* DITA2KDB_WS00221C_OPEN_FOR_FILE_ALREADY_OPEN */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_open_for_file_already_open();
			break;
		case 1200195: /* DITA2KDB_WS00221C_PASSWORD_FAILURE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_password_failure();
			break;
		case 1200196: /* DITA2KDB_WS00221C_PERMANENT_IO_ERROR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_permanent_io_error();
			break;
		case 1200197: /* DITA2KDB_WS00221C_PERMANENT_SPACE_ERROR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_permanent_space_error();
			break;
		case 1200198: /* DITA2KDB_WS00221C_PROGRAM_NAME_NOT_IN_PLAN */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_program_name_not_in_plan();
			break;
		case 1200199: /* DITA2KDB_WS00221C_READ_WITHOUT_OPEN_FOR_IO */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_read_without_open_for_io();
			break;
		case 1200201: /* DITA2KDB_WS00221C_RESOURCE_LIMIT_EXCEEDED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resource_limit_exceeded();
			break;
		case 1200202: /* DITA2KDB_WS00221C_RESOURCE_NOT_AVAILABLE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resource_not_available();
			break;
		case 1200203: /* DITA2KDB_WS00221C_RESP_ACCOUNT_IS_DIVMAIL */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_account_is_divmail();
			break;
		case 1200204: /* DITA2KDB_WS00221C_RESP_ACCOUNT_IS_PPA */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_account_is_ppa();
			break;
		case 1200205: /* DITA2KDB_WS00221C_RESP_ACCOUNT_IS_TIMER */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_account_is_timer();
			break;
		case 1200206: /* DITA2KDB_WS00221C_RESP_ACCT_CLOSED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_closed();
			break;
		case 1200207: /* DITA2KDB_WS00221C_RESP_ACCT_CODED_BANK_CARD */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_coded_bank_card();
			break;
		case 1200208: /* DITA2KDB_WS00221C_RESP_ACCT_CODED_TELE_TRANS */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_coded_tele_trans();
			break;
		case 1200209: /* DITA2KDB_WS00221C_RESP_ACCT_DEALER_CONTROLLED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_dealer_controlled();
			break;
		case 1200210: /* DITA2KDB_WS00221C_RESP_ACCT_GRP_LIST_EMPTY */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_grp_list_empty();
			break;
		case 1200211: /* DITA2KDB_WS00221C_RESP_ACCT_GRP_LIST_EXCEEDED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_grp_list_exceeded();
			break;
		case 1200212: /* DITA2KDB_WS00221C_RESP_ACCT_GRP_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_grp_not_allowed();
			break;
		case 1200213: /* DITA2KDB_WS00221C_RESP_ACCT_MARKED_ESCHEATMENT */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_marked_escheatment();
			break;
		case 1200214: /* DITA2KDB_WS00221C_RESP_ACCT_MARKED_NO_ACH_ACTIVY */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_marked_no_ach_activy();
			break;
		case 1200215: /* DITA2KDB_WS00221C_RESP_ACCT_MARKED_NO_EXPD_EXCH */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_marked_no_expd_exch();
			break;
		case 1200216: /* DITA2KDB_WS00221C_RESP_ACCT_MARKED_NO_REDMP_CHKS */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_marked_no_redmp_chks();
			break;
		case 1200217: /* DITA2KDB_WS00221C_RESP_ACCT_MARKED_STOP_MAIL */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_marked_stop_mail();
			break;
		case 1200218: /* DITA2KDB_WS00221C_RESP_ACCT_MARKED_STOP_PURCHASE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_marked_stop_purchase();
			break;
		case 1200219: /* DITA2KDB_WS00221C_RESP_ACCT_MARKED_STOP_TRANSFER */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_marked_stop_transfer();
			break;
		case 1200220: /* DITA2KDB_WS00221C_RESP_ACCT_MARKED_SUBACCOUNT */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_marked_subaccount();
			break;
		case 1200221: /* DITA2KDB_WS00221C_RESP_ACCT_MKD_NO_MTHLY_PURCH */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_mkd_no_mthly_purch();
			break;
		case 1200222: /* DITA2KDB_WS00221C_RESP_ACCT_NON_DEALER_CONTROL */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_non_dealer_control();
			break;
		case 1200223: /* DITA2KDB_WS00221C_RESP_ACCT_NOT_MARKED_ARS */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_not_marked_ars();
			break;
		case 1200224: /* DITA2KDB_WS00221C_RESP_ACCT_NOT_MARKED_EXP_RED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_acct_not_marked_exp_red();
			break;
		case 1200225: /* DITA2KDB_WS00221C_RESP_ACCTS_NOT_RELATED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_accts_not_related();
			break;
		case 1200226: /* DITA2KDB_WS00221C_RESP_ACH_REDEEM_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_ach_redeem_not_allowed();
			break;
		case 1200227: /* DITA2KDB_WS00221C_RESP_ACH_SPECIAL_REDEMPTION_NO */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_ach_special_redemption_no();
			break;
		case 1200228: /* DITA2KDB_WS00221C_RESP_ADDR_OF_RGSTR_CHANGED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_addr_of_rgstr_changed();
			break;
		case 1200229: /* DITA2KDB_WS00221C_RESP_ALL_SHR_TRAN_REC_FOUND */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_all_shr_tran_rec_found();
			break;
		case 1200230: /* DITA2KDB_WS00221C_RESP_ALREADY_SIGNED_ON */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_already_signed_on();
			break;
		case 1200231: /* DITA2KDB_WS00221C_RESP_AMT_EXCEEDS_AVAILABLE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_amt_exceeds_available();
			break;
		case 1200232: /* DITA2KDB_WS00221C_RESP_AMT_GT_MAX_ALLOWED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_amt_gt_max_allowed();
			break;
		case 1200233: /* DITA2KDB_WS00221C_RESP_AMT_LT_MIN_REQUIRED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_amt_lt_min_required();
			break;
		case 1200234: /* DITA2KDB_WS00221C_RESP_AUTH_BUT_NO_DESC */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_auth_but_no_desc();
			break;
		case 1200235: /* DITA2KDB_WS00221C_RESP_BAD_LINK_TO_CRTCSERV */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_bad_link_to_crtcserv();
			break;
		case 1200236: /* DITA2KDB_WS00221C_RESP_BAD_LINK_TO_CRTSTACK */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_bad_link_to_crtstack();
			break;
		case 1200237: /* DITA2KDB_WS00221C_RESP_BANK_ACCT_NBR_MISMATCH */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_bank_acct_nbr_mismatch();
			break;
		case 1200238: /* DITA2KDB_WS00221C_RESP_CALCULATION_ERROR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_calculation_error();
			break;
		case 1200239: /* DITA2KDB_WS00221C_RESP_CHG_REC_NOT_FOUND */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_chg_rec_not_found();
			break;
		case 1200240: /* DITA2KDB_WS00221C_RESP_CHGD_BY_DIF_OPERATOR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_chgd_by_dif_operator();
			break;
		case 1200241: /* DITA2KDB_WS00221C_RESP_COMM_SHARES_NOT_FOUND */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_comm_shares_not_found();
			break;
		case 1200242: /* DITA2KDB_WS00221C_RESP_COMM_SHARES_REC_ERROR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_comm_shares_rec_error();
			break;
		case 1200243: /* DITA2KDB_WS00221C_RESP_COPY_EXCH_ATTEMPT_INVALID */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_copy_exch_attempt_invalid();
			break;
		case 1200244: /* DITA2KDB_WS00221C_RESP_COPY_EXCH_SSN_MISMATCH */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_copy_exch_ssn_mismatch();
			break;
		case 1200245: /* DITA2KDB_WS00221C_RESP_COPY_MGMTS_NOT_EQUAL */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_copy_mgmts_not_equal();
			break;
		case 1200246: /* DITA2KDB_WS00221C_RESP_COPY_PURCH_ATEMPT_INVALID */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_copy_purch_atempt_invalid();
			break;
		case 1200247: /* DITA2KDB_WS00221C_RESP_COPY_PURCH_SSN_MISMATCH */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_copy_purch_ssn_mismatch();
			break;
		case 1200248: /* DITA2KDB_WS00221C_RESP_CUM_DISC_ALRDY_EXIST */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_cum_disc_alrdy_exist();
			break;
		case 1200249: /* DITA2KDB_WS00221C_RESP_DATA_NOT_FND_ON_WS_TABLE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_data_not_fnd_on_ws_table();
			break;
		case 1200250: /* DITA2KDB_WS00221C_RESP_DATA_NOT_FOUND */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_data_not_found();
			break;
		case 1200251: /* DITA2KDB_WS00221C_RESP_DEL_REC_NOT_FOUND */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_del_rec_not_found();
			break;
		case 1200252: /* DITA2KDB_WS00221C_RESP_DFHRESP_DISABLED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_disabled();
			break;
		case 1200253: /* DITA2KDB_WS00221C_RESP_DFHRESP_DSNOTFOUND */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_dsnotfound();
			break;
		case 1200254: /* DITA2KDB_WS00221C_RESP_DFHRESP_DUPKEY */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_dupkey();
			break;
		case 1200255: /* DITA2KDB_WS00221C_RESP_DFHRESP_ENDFILE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_endfile();
			break;
		case 1200256: /* DITA2KDB_WS00221C_RESP_DFHRESP_FILENOTFOUND */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_filenotfound();
			break;
		case 1200257: /* DITA2KDB_WS00221C_RESP_DFHRESP_ILLOGIC */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_illogic();
			break;
		case 1200258: /* DITA2KDB_WS00221C_RESP_DFHRESP_INVREQ */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_invreq();
			break;
		case 1200259: /* DITA2KDB_WS00221C_RESP_DFHRESP_IOERR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_ioerr();
			break;
		case 1200260: /* DITA2KDB_WS00221C_RESP_DFHRESP_ISCINVREQ */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_iscinvreq();
			break;
		case 1200261: /* DITA2KDB_WS00221C_RESP_DFHRESP_LENGERR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_lengerr();
			break;
		case 1200262: /* DITA2KDB_WS00221C_RESP_DFHRESP_LOADING */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_loading();
			break;
		case 1200263: /* DITA2KDB_WS00221C_RESP_DFHRESP_NOTAUTH */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_notauth();
			break;
		case 1200264: /* DITA2KDB_WS00221C_RESP_DFHRESP_NOTFND */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_notfnd();
			break;
		case 1200265: /* DITA2KDB_WS00221C_RESP_DFHRESP_NOTOPEN */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_notopen();
			break;
		case 1200266: /* DITA2KDB_WS00221C_RESP_DFHRESP_PGMIDERR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_pgmiderr();
			break;
		case 1200267: /* DITA2KDB_WS00221C_RESP_DFHRESP_QIDERR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_qiderr();
			break;
		case 1200268: /* DITA2KDB_WS00221C_RESP_DFHRESP_ROLLEDBACK */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_rolledback();
			break;
		case 1200269: /* DITA2KDB_WS00221C_RESP_DFHRESP_SYSIDERR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_sysiderr();
			break;
		case 1200270: /* DITA2KDB_WS00221C_RESP_DFHRESP_TERMERR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_termerr();
			break;
		case 1200271: /* DITA2KDB_WS00221C_RESP_DFHRESP_USERIDERR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_useriderr();
			break;
		case 1200272: /* DITA2KDB_WS00221C_RESP_DOL_TRAN_NOT_AUTHORIZED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dol_tran_not_authorized();
			break;
		case 1200273: /* DITA2KDB_WS00221C_RESP_ERROR_IN_BINARY_SEARCH */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_error_in_binary_search();
			break;
		case 1200274: /* DITA2KDB_WS00221C_RESP_EXCESS_FUNDS_FOR_INV_NUM */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_excess_funds_for_inv_num();
			break;
		case 1200275: /* DITA2KDB_WS00221C_RESP_EXCESS_TABLE_DATA */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_excess_table_data();
			break;
		case 1200276: /* DITA2KDB_WS00221C_RESP_EXCH_BANK_ONLY_FROM_SIDE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_exch_bank_only_from_side();
			break;
		case 1200277: /* DITA2KDB_WS00221C_RESP_EXCH_BANKS_NOT_EQUAL */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_exch_banks_not_equal();
			break;
		case 1200278: /* DITA2KDB_WS00221C_RESP_EXCH_FUNDS_EQUAL */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_exch_funds_equal();
			break;
		case 1200279: /* DITA2KDB_WS00221C_RESP_EXCH_MGMTS_NOT_EQUAL */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_exch_mgmts_not_equal();
			break;
		case 1200280: /* DITA2KDB_WS00221C_RESP_EXR_ACTIVITY_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_exr_activity_not_allowed();
			break;
		case 1200281: /* DITA2KDB_WS00221C_RESP_EXR_ON_MATR_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_exr_on_matr_not_allowed();
			break;
		case 1200282: /* DITA2KDB_WS00221C_RESP_FACILITY_NOT_PASSED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_facility_not_passed();
			break;
		case 1200283: /* DITA2KDB_WS00221C_RESP_FULL_LIQDTN_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_full_liqdtn_not_allowed();
			break;
		case 1200284: /* DITA2KDB_WS00221C_RESP_FUND_CLOSED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_fund_closed();
			break;
		case 1200285: /* DITA2KDB_WS00221C_RESP_FUND_MARKED_NO_ACH_ACTIVY */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_fund_marked_no_ach_activy();
			break;
		case 1200286: /* DITA2KDB_WS00221C_RESP_FUND_MARKED_NO_REDMP_CHKS */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_fund_marked_no_redmp_chks();
			break;
		case 1200287: /* DITA2KDB_WS00221C_RESP_FUND_NOT_AUTHORIZED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_fund_not_authorized();
			break;
		case 1200288: /* DITA2KDB_WS00221C_RESP_INSUFF_COLLECTED_SHRS */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_insuff_collected_shrs();
			break;
		case 1200289: /* DITA2KDB_WS00221C_RESP_INVALID_ACCESS_METHOD */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_access_method();
			break;
		case 1200290: /* DITA2KDB_WS00221C_RESP_INVALID_ACCOUNT_NMBR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_account_nmbr();
			break;
		case 1200291: /* DITA2KDB_WS00221C_RESP_INVALID_ACCT_ALRDY_HS_LOI */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_acct_alrdy_hs_loi();
			break;
		case 1200292: /* DITA2KDB_WS00221C_RESP_INVALID_ACCT_GRP_CDE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_acct_grp_cde();
			break;
		case 1200293: /* DITA2KDB_WS00221C_RESP_INVALID_ACCT_OPTION */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_acct_option();
			break;
		case 1200294: /* DITA2KDB_WS00221C_RESP_INVALID_ACCT_RELATIONSHIP */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_acct_relationship();
			break;
		case 1200295: /* DITA2KDB_WS00221C_RESP_INVALID_ACCT_SHARE_LOT */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_acct_share_lot();
			break;
		case 1200296: /* DITA2KDB_WS00221C_RESP_INVALID_ACCUM_YEARS */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_accum_years();
			break;
		case 1200297: /* DITA2KDB_WS00221C_RESP_INVALID_ACH_DIVIDEND_CDE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_ach_dividend_cde();
			break;
		case 1200298: /* DITA2KDB_WS00221C_RESP_INVALID_ACH_SPEC_PURCH_CD */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_ach_spec_purch_cd();
			break;
		case 1200299: /* DITA2KDB_WS00221C_RESP_INVALID_ACH_SPEC_RDMPT_CD */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_ach_spec_rdmpt_cd();
			break;
		case 1200300: /* DITA2KDB_WS00221C_RESP_INVALID_ACTION_CODE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_action_code();
			break;
		case 1200301: /* DITA2KDB_WS00221C_RESP_INVALID_ADD_MAL_ALRY_EX */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_add_mal_alry_ex();
			break;
		case 1200302: /* DITA2KDB_WS00221C_RESP_INVALID_ADDRESS_ENTERED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_address_entered();
			break;
		case 1200303: /* DITA2KDB_WS00221C_RESP_INVALID_AGENT_FOR_FIRM */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_agent_for_firm();
			break;
		case 1200304: /* DITA2KDB_WS00221C_RESP_INVALID_ALPHA_CODE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_alpha_code();
			break;
		case 1200305: /* DITA2KDB_WS00221C_RESP_INVALID_AMOUNT */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_amount();
			break;
		case 1200306: /* DITA2KDB_WS00221C_RESP_INVALID_APO_FPO_CITY_CDE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_apo_fpo_city_cde();
			break;
		case 1200307: /* DITA2KDB_WS00221C_RESP_INVALID_APO_FPO_REG_FMT */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_apo_fpo_reg_fmt();
			break;
		case 1200308: /* DITA2KDB_WS00221C_RESP_INVALID_ARRAY_ROWS */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_array_rows();
			break;
		case 1200309: /* DITA2KDB_WS00221C_RESP_INVALID_ASSET_TARGET_RT */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_asset_target_rt();
			break;
		case 1200310: /* DITA2KDB_WS00221C_RESP_INVALID_AVAILABLE_SHARES */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_available_shares();
			break;
		case 1200311: /* DITA2KDB_WS00221C_RESP_INVALID_BANK_ACCT_NBR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_bank_acct_nbr();
			break;
		case 1200312: /* DITA2KDB_WS00221C_RESP_INVALID_BANK_ACCT_TYPE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_bank_acct_type();
			break;
		case 1200313: /* DITA2KDB_WS00221C_RESP_INVALID_BANK_MICR_ID */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_bank_micr_id();
			break;
		case 1200314: /* DITA2KDB_WS00221C_RESP_INVALID_BANK_NOT_ENTERED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_bank_not_entered();
			break;
		case 1200315: /* DITA2KDB_WS00221C_RESP_INVALID_BANK_OPTION */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_bank_option();
			break;
		case 1200316: /* DITA2KDB_WS00221C_RESP_INVALID_BANK_REG */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_bank_reg();
			break;
		case 1200317: /* DITA2KDB_WS00221C_RESP_INVALID_BATCH_NUM */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_batch_num();
			break;
		case 1200318: /* DITA2KDB_WS00221C_RESP_INVALID_BENEFICIARY_NAME */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_beneficiary_name();
			break;
		case 1200319: /* DITA2KDB_WS00221C_RESP_INVALID_BNF_RELATION */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_bnf_relation();
			break;
		case 1200320: /* DITA2KDB_WS00221C_RESP_INVALID_CALL */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_call();
			break;
		case 1200321: /* DITA2KDB_WS00221C_RESP_INVALID_CAP_GAINS_CODE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_cap_gains_code();
			break;
		case 1200322: /* DITA2KDB_WS00221C_RESP_INVALID_CASH_INST_TYPE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_cash_inst_type();
			break;
		case 1200323: /* DITA2KDB_WS00221C_RESP_INVALID_CDSC_SLS */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_cdsc_sls();
			break;
		case 1200324: /* DITA2KDB_WS00221C_RESP_INVALID_CERT_NUMBER */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_cert_number();
			break;
		case 1200325: /* DITA2KDB_WS00221C_RESP_INVALID_CITY_ENTERED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_city_entered();
			break;
		case 1200326: /* DITA2KDB_WS00221C_RESP_INVALID_CITY_NOT_APO_FPO */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_city_not_apo_fpo();
			break;
		case 1200327: /* DITA2KDB_WS00221C_RESP_INVALID_CLIENT_ID */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_client_id();
			break;
		case 1200328: /* DITA2KDB_WS00221C_RESP_INVALID_CNFRM_FREQ */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_cnfrm_freq();
			break;
		case 1200329: /* DITA2KDB_WS00221C_RESP_INVALID_CONTRIB_YEAR_CODE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_contrib_year_code();
			break;
		case 1200330: /* DITA2KDB_WS00221C_RESP_INVALID_CORR_CODE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_corr_code();
			break;
		case 1200331: /* DITA2KDB_WS00221C_RESP_INVALID_CRUD_CODE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_crud_code();
			break;
		case 1200332: /* DITA2KDB_WS00221C_RESP_INVALID_CUMDISC */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_cumdisc();
			break;
		case 1200333: /* DITA2KDB_WS00221C_RESP_INVALID_CUMDISC_PLAN */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_cumdisc_plan();
			break;
		case 1200334: /* DITA2KDB_WS00221C_RESP_INVALID_DATA_REQ */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_data_req();
			break;
		case 1200335: /* DITA2KDB_WS00221C_RESP_INVALID_DATE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_date();
			break;
		case 1200336: /* DITA2KDB_WS00221C_RESP_INVALID_DAY_CDE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_day_cde();
			break;
		case 1200337: /* DITA2KDB_WS00221C_RESP_INVALID_DEBIT_CARD */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_debit_card();
			break;
		case 1200338: /* DITA2KDB_WS00221C_RESP_INVALID_DEBIT_TYPE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_debit_type();
			break;
		case 1200339: /* DITA2KDB_WS00221C_RESP_INVALID_DIVIDEND_CDE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_dividend_cde();
			break;
		case 1200340: /* DITA2KDB_WS00221C_RESP_INVALID_DLR_BR_SUMMRY */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_dlr_br_summry();
			break;
		case 1200341: /* DITA2KDB_WS00221C_RESP_INVALID_DLR_BRANCH */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_dlr_branch();
			break;
		case 1200342: /* DITA2KDB_WS00221C_RESP_INVALID_DLR_BRN_SEC */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_dlr_brn_sec();
			break;
		case 1200343: /* DITA2KDB_WS00221C_RESP_INVALID_DLR_NUMBER */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_dlr_number();
			break;
		case 1200344: /* DITA2KDB_WS00221C_RESP_INVALID_DLR_SUMMARY */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_dlr_summary();
			break;
		case 1200345: /* DITA2KDB_WS00221C_RESP_INVALID_DSCS_APPREC */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_dscs_apprec();
			break;
		case 1200346: /* DITA2KDB_WS00221C_RESP_INVALID_EML_ADR_ENTERED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_eml_adr_entered();
			break;
		case 1200347: /* DITA2KDB_WS00221C_RESP_INVALID_ESCROW_SHRS */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_escrow_shrs();
			break;
		case 1200348: /* DITA2KDB_WS00221C_RESP_INVALID_EXCH_PUR_CANC */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_exch_pur_canc();
			break;
		case 1200349: /* DITA2KDB_WS00221C_RESP_INVALID_EXCH_RED_CANC */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_exch_red_canc();
			break;
		case 1200350: /* DITA2KDB_WS00221C_RESP_INVALID_EXIST_CDE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_exist_cde();
			break;
		case 1200351: /* DITA2KDB_WS00221C_RESP_INVALID_FID_ACCOUNT */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_fid_account();
			break;
		case 1200352: /* DITA2KDB_WS00221C_RESP_INVALID_FINS_ID */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_fins_id();
			break;
		case 1200353: /* DITA2KDB_WS00221C_RESP_INVALID_FIRM_ACCT_NBR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_firm_acct_nbr();
			break;
		case 1200354: /* DITA2KDB_WS00221C_RESP_INVALID_FIRM_NBR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_firm_nbr();
			break;
		case 1200355: /* DITA2KDB_WS00221C_RESP_INVALID_FLD_CNT */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_fld_cnt();
			break;
		case 1200356: /* DITA2KDB_WS00221C_RESP_INVALID_FLD_ID */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_fld_id();
			break;
		case 1200357: /* DITA2KDB_WS00221C_RESP_INVALID_FOREIGN_STATE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_foreign_state();
			break;
		case 1200358: /* DITA2KDB_WS00221C_RESP_INVALID_FORGN_ADDR_CDE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_forgn_addr_cde();
			break;
		case 1200359: /* DITA2KDB_WS00221C_RESP_INVALID_FREQ_FOR_BALANCE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_freq_for_balance();
			break;
		case 1200360: /* DITA2KDB_WS00221C_RESP_INVALID_FRONT_END */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_front_end();
			break;
		case 1200361: /* DITA2KDB_WS00221C_RESP_INVALID_FULL_CODE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_full_code();
			break;
		case 1200362: /* DITA2KDB_WS00221C_RESP_INVALID_FUNCTION_TYPE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_function_type();
			break;
		case 1200363: /* DITA2KDB_WS00221C_RESP_INVALID_FUND_AGREEMENT */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_fund_agreement();
			break;
		case 1200364: /* DITA2KDB_WS00221C_RESP_INVALID_FUND_CODE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_fund_code();
			break;
		case 1200365: /* DITA2KDB_WS00221C_RESP_INVALID_FUND_GRP_NBR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_fund_grp_nbr();
			break;
		case 1200366: /* DITA2KDB_WS00221C_RESP_INVALID_FUND_OPTION */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_fund_option();
			break;
		case 1200367: /* DITA2KDB_WS00221C_RESP_INVALID_FUND_RELATIONSHIP */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_fund_relationship();
			break;
		case 1200368: /* DITA2KDB_WS00221C_RESP_INVALID_HOUSE_ACCOUNT */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_house_account();
			break;
		case 1200369: /* DITA2KDB_WS00221C_RESP_INVALID_IDV_DMS_ADR_CD */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_idv_dms_adr_cd();
			break;
		case 1200370: /* DITA2KDB_WS00221C_RESP_INVALID_INDIVIDUAL_ID */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_individual_id();
			break;
		case 1200371: /* DITA2KDB_WS00221C_RESP_INVALID_INSTRUCTION_ID */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_instruction_id();
			break;
		case 1200372: /* DITA2KDB_WS00221C_RESP_INVALID_KEY_DATA */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_key_data();
			break;
		case 1200373: /* DITA2KDB_WS00221C_RESP_INVALID_KEY_SUFFIX */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_key_suffix();
			break;
		case 1200374: /* DITA2KDB_WS00221C_RESP_INVALID_LINE_CODE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_line_code();
			break;
		case 1200375: /* DITA2KDB_WS00221C_RESP_INVALID_LOI_AGREE_AMT */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_loi_agree_amt();
			break;
		case 1200376: /* DITA2KDB_WS00221C_RESP_INVALID_LOI_EFF_DTE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_loi_eff_dte();
			break;
		case 1200377: /* DITA2KDB_WS00221C_RESP_INVALID_LOI_NUMBER */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_loi_number();
			break;
		case 1200378: /* DITA2KDB_WS00221C_RESP_INVALID_LOT_VALUE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_lot_value();
			break;
		case 1200379: /* DITA2KDB_WS00221C_RESP_INVALID_MARITAL_STATUS */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_marital_status();
			break;
		case 1200380: /* DITA2KDB_WS00221C_RESP_INVALID_MAX_AMT */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_max_amt();
			break;
		case 1200381: /* DITA2KDB_WS00221C_RESP_INVALID_MGMT_CODE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_mgmt_code();
			break;
		case 1200382: /* DITA2KDB_WS00221C_RESP_INVALID_MIN_AMT */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_min_amt();
			break;
		case 1200383: /* DITA2KDB_WS00221C_RESP_INVALID_MONTHLY_ACCUM */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_monthly_accum();
			break;
		case 1200384: /* DITA2KDB_WS00221C_RESP_INVALID_MTHLY_INDS */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_mthly_inds();
			break;
		case 1200385: /* DITA2KDB_WS00221C_RESP_INVALID_NAV_CDE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_nav_cde();
			break;
		case 1200386: /* DITA2KDB_WS00221C_RESP_INVALID_NAV_PER_SHR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_nav_per_shr();
			break;
		case 1200388: /* DITA2KDB_WS00221C_RESP_INVALID_NO_ACCT_TO_UPD */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_no_acct_to_upd();
			break;
		case 1200389: /* DITA2KDB_WS00221C_RESP_INVALID_NO_SPC_CTYST_CD */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_no_spc_ctyst_cd();
			break;
		case 1200390: /* DITA2KDB_WS00221C_RESP_INVALID_NUM_ABBREV_ST */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_num_abbrev_st();
			break;
		case 1200391: /* DITA2KDB_WS00221C_RESP_INVALID_OPTION */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_option();
			break;
		case 1200392: /* DITA2KDB_WS00221C_RESP_INVALID_OPTION_REQUEST */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_option_request();
			break;
		case 1200393: /* DITA2KDB_WS00221C_RESP_INVALID_ORDER_NUMBER */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_order_number();
			break;
		case 1200394: /* DITA2KDB_WS00221C_RESP_INVALID_OUT_OF_BLC_HI_RT */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_out_of_blc_hi_rt();
			break;
		case 1200395: /* DITA2KDB_WS00221C_RESP_INVALID_OUT_OF_BLC_LOW_RT */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_out_of_blc_low_rt();
			break;
		case 1200396: /* DITA2KDB_WS00221C_RESP_INVALID_PAF_BUCKET */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_paf_bucket();
			break;
		case 1200397: /* DITA2KDB_WS00221C_RESP_INVALID_PARM_DATA */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_parm_data();
			break;
		case 1200398: /* DITA2KDB_WS00221C_RESP_INVALID_PIN_INACTIVE_CDE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_pin_inactive_cde();
			break;
		case 1200399: /* DITA2KDB_WS00221C_RESP_INVALID_PIN_SEC_METHOD */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_pin_sec_method();
			break;
		case 1200400: /* DITA2KDB_WS00221C_RESP_INVALID_PND_REDEMPTION */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_pnd_redemption();
			break;
		case 1200401: /* DITA2KDB_WS00221C_RESP_INVALID_PRE_AGREEMENT */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_pre_agreement();
			break;
		case 1200402: /* DITA2KDB_WS00221C_RESP_INVALID_PRE_EX_MAIL_CDE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_pre_ex_mail_cde();
			break;
		case 1200403: /* DITA2KDB_WS00221C_RESP_INVALID_PRG_ALW_CD */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_prg_alw_cd();
			break;
		case 1200404: /* DITA2KDB_WS00221C_RESP_INVALID_PRICE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_price();
			break;
		case 1200405: /* DITA2KDB_WS00221C_RESP_INVALID_PRICE_SCHED_CDE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_price_sched_cde();
			break;
		case 1200406: /* DITA2KDB_WS00221C_RESP_INVALID_PROCESS_CODE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_process_code();
			break;
		case 1200407: /* DITA2KDB_WS00221C_RESP_INVALID_PROCESS_TYPE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_process_type();
			break;
		case 1200408: /* DITA2KDB_WS00221C_RESP_INVALID_PRODUCT_ID */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_product_id();
			break;
		case 1200409: /* DITA2KDB_WS00221C_RESP_INVALID_PST_AGREEMENT */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_pst_agreement();
			break;
		case 1200410: /* DITA2KDB_WS00221C_RESP_INVALID_PTF_ROLE_TYPE_ID */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_ptf_role_type_id();
			break;
		case 1200411: /* DITA2KDB_WS00221C_RESP_INVALID_PURCH_CANCEL */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_purch_cancel();
			break;
		case 1200412: /* DITA2KDB_WS00221C_RESP_INVALID_RE_BLC_EXCL_CD */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_re_blc_excl_cd();
			break;
		case 1200413: /* DITA2KDB_WS00221C_RESP_INVALID_REDEMPT_OPT */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_redempt_opt();
			break;
		case 1200414: /* DITA2KDB_WS00221C_RESP_INVALID_REDMPT_CANCEL */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_redmpt_cancel();
			break;
		case 1200415: /* DITA2KDB_WS00221C_RESP_INVALID_REIN_DOLLAR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_rein_dollar();
			break;
		case 1200416: /* DITA2KDB_WS00221C_RESP_INVALID_REIN_SHARES */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_rein_shares();
			break;
		case 1200417: /* DITA2KDB_WS00221C_RESP_INVALID_REP_NUMBER */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_rep_number();
			break;
		case 1200418: /* DITA2KDB_WS00221C_RESP_INVALID_REQUEST_CNT */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_request_cnt();
			break;
		case 1200419: /* DITA2KDB_WS00221C_RESP_INVALID_RES_STATE_CD */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_res_state_cd();
			break;
		case 1200420: /* DITA2KDB_WS00221C_RESP_INVALID_RRTTFR_CD */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_rrttfr_cd();
			break;
		case 1200421: /* DITA2KDB_WS00221C_RESP_INVALID_RULE_FLD_SEQ */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_rule_fld_seq();
			break;
		case 1200422: /* DITA2KDB_WS00221C_RESP_INVALID_RULE_ID */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_rule_id();
			break;
		case 1200423: /* DITA2KDB_WS00221C_RESP_INVALID_SEC_ISS_ID */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_sec_iss_id();
			break;
		case 1200424: /* DITA2KDB_WS00221C_RESP_INVALID_SHAREOWNER_NAME */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_shareowner_name();
			break;
		case 1200425: /* DITA2KDB_WS00221C_RESP_INVALID_SHARES */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_shares();
			break;
		case 1200426: /* DITA2KDB_WS00221C_RESP_INVALID_SOC_SEC_NBR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_soc_sec_nbr();
			break;
		case 1200427: /* DITA2KDB_WS00221C_RESP_INVALID_SOCIAL_CODE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_social_code();
			break;
		case 1200428: /* DITA2KDB_WS00221C_RESP_INVALID_SORT_CODE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_sort_code();
			break;
		case 1200429: /* DITA2KDB_WS00221C_RESP_INVALID_SOURCE_SYSTEM_ID */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_source_system_id();
			break;
		case 1200430: /* DITA2KDB_WS00221C_RESP_INVALID_SS_CODE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_ss_code();
			break;
		case 1200431: /* DITA2KDB_WS00221C_RESP_INVALID_ST_COUNTRY_CD */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_st_country_cd();
			break;
		case 1200432: /* DITA2KDB_WS00221C_RESP_INVALID_ST_DS_APO_FPO_ZIP */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_st_ds_apo_fpo_zip();
			break;
		case 1200433: /* DITA2KDB_WS00221C_RESP_INVALID_START_DTE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_start_dte();
			break;
		case 1200434: /* DITA2KDB_WS00221C_RESP_INVALID_START_MONTH */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_start_month();
			break;
		case 1200436: /* DITA2KDB_WS00221C_RESP_INVALID_STATE_UPD_CODE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_state_upd_code();
			break;
		case 1200437: /* DITA2KDB_WS00221C_RESP_INVALID_STOCK_SPLIT_RATE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_stock_split_rate();
			break;
		case 1200438: /* DITA2KDB_WS00221C_RESP_INVALID_STOP_DTE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_stop_dte();
			break;
		case 1200439: /* DITA2KDB_WS00221C_RESP_INVALID_SYS_AGR_ID */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_sys_agr_id();
			break;
		case 1200440: /* DITA2KDB_WS00221C_RESP_INVALID_SYS_AGREE_AMT */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_sys_agree_amt();
			break;
		case 1200441: /* DITA2KDB_WS00221C_RESP_INVALID_SYST_TRANS_CDE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_syst_trans_cde();
			break;
		case 1200442: /* DITA2KDB_WS00221C_RESP_INVALID_SYSTEM_ID */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_system_id();
			break;
		case 1200443: /* DITA2KDB_WS00221C_RESP_INVALID_SYSTMTC_TYP */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_systmtc_typ();
			break;
		case 1200444: /* DITA2KDB_WS00221C_RESP_INVALID_TAX_ID_NUMBER */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_tax_id_number();
			break;
		case 1200445: /* DITA2KDB_WS00221C_RESP_INVALID_TBL_LD_OR_ST_POS */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_tbl_ld_or_st_pos();
			break;
		case 1200446: /* DITA2KDB_WS00221C_RESP_INVALID_TERMINAL_ID */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_terminal_id();
			break;
		case 1200447: /* DITA2KDB_WS00221C_RESP_INVALID_TIME_OF_DAY */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_time_of_day();
			break;
		case 1200448: /* DITA2KDB_WS00221C_RESP_INVALID_TIMESTAMP */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_timestamp();
			break;
		case 1200449: /* DITA2KDB_WS00221C_RESP_INVALID_TO_ACCT_NBR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_to_acct_nbr();
			break;
		case 1200450: /* DITA2KDB_WS00221C_RESP_INVALID_TO_FUND_CODE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_to_fund_code();
			break;
		case 1200451: /* DITA2KDB_WS00221C_RESP_INVALID_TO_MGMT_CODE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_to_mgmt_code();
			break;
		case 1200452: /* DITA2KDB_WS00221C_RESP_INVALID_TRADE_VALUE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_trade_value();
			break;
		case 1200453: /* DITA2KDB_WS00221C_RESP_INVALID_TRAN_TYPE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_tran_type();
			break;
		case 1200454: /* DITA2KDB_WS00221C_RESP_INVALID_TRXN_NUMBER */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_trxn_number();
			break;
		case 1200455: /* DITA2KDB_WS00221C_RESP_INVALID_UNISSUED_SHRS */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_unissued_shrs();
			break;
		case 1200456: /* DITA2KDB_WS00221C_RESP_INVALID_USER_STATUS */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_user_status();
			break;
		case 1200457: /* DITA2KDB_WS00221C_RESP_INVALID_VERSION */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_version();
			break;
		case 1200458: /* DITA2KDB_WS00221C_RESP_INVALID_WITHH_AMT */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_withh_amt();
			break;
		case 1200459: /* DITA2KDB_WS00221C_RESP_INVALID_WITHH_CNT */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_withh_cnt();
			break;
		case 1200460: /* DITA2KDB_WS00221C_RESP_INVALID_YIELD_DATE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_yield_date();
			break;
		case 1200461: /* DITA2KDB_WS00221C_RESP_INVALID_ZIP_CODE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_zip_code();
			break;
		case 1200462: /* DITA2KDB_WS00221C_RESP_INVALID_ZIP_FOR_STATE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_zip_for_state();
			break;
		case 1200463: /* DITA2KDB_WS00221C_RESP_LAST_ACCT_NUMBER_ASSIGNED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_last_acct_number_assigned();
			break;
		case 1200464: /* DITA2KDB_WS00221C_RESP_LAST_CUM_NBR_ASSIGN */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_last_cum_nbr_assign();
			break;
		case 1200465: /* DITA2KDB_WS00221C_RESP_NET_DLR_CODE_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_net_dlr_code_not_allowed();
			break;
		case 1200466: /* DITA2KDB_WS00221C_RESP_NO_PRE_AUTH_CHECKS */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_no_pre_auth_checks();
			break;
		case 1200467: /* DITA2KDB_WS00221C_RESP_NO_TWENTY_FOUR_HR_TRADING */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_no_twenty_four_hr_trading();
			break;
		case 1200468: /* DITA2KDB_WS00221C_RESP_NO_UPDATE_DETECTED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_no_update_detected();
			break;
		case 1200469: /* DITA2KDB_WS00221C_RESP_NO_UPDATES_TO_APPLY */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_no_updates_to_apply();
			break;
		case 1200470: /* DITA2KDB_WS00221C_RESP_NO_VERIFY_DTE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_no_verify_dte();
			break;
		case 1200471: /* DITA2KDB_WS00221C_RESP_NOT_AUTHORIZED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_not_authorized();
			break;
		case 1200472: /* DITA2KDB_WS00221C_RESP_NOT_SIGNED_ON */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_not_signed_on();
			break;
		case 1200473: /* DITA2KDB_WS00221C_RESP_OPERATOR_DISABLED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_operator_disabled();
			break;
		case 1200474: /* DITA2KDB_WS00221C_RESP_OPERATOR_NOT_ATH_DEALER */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_operator_not_ath_dealer();
			break;
		case 1200475: /* DITA2KDB_WS00221C_RESP_OPERATOR_NOT_ATH_DLR_BR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_operator_not_ath_dlr_br();
			break;
		case 1200476: /* DITA2KDB_WS00221C_RESP_OPERATOR_NOT_PASSED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_operator_not_passed();
			break;
		case 1200477: /* DITA2KDB_WS00221C_RESP_PIN_INIT_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_pin_init_not_allowed();
			break;
		case 1200478: /* DITA2KDB_WS00221C_RESP_PIN_MASK_INVALID */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_pin_mask_invalid();
			break;
		case 1200479: /* DITA2KDB_WS00221C_RESP_PIN_NBR_INVALID_CUSTOM */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_pin_nbr_invalid_custom();
			break;
		case 1200480: /* DITA2KDB_WS00221C_RESP_PIN_NUMBER_ACTIVE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_pin_number_active();
			break;
		case 1200481: /* DITA2KDB_WS00221C_RESP_PIN_NUMBER_BLOCKED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_pin_number_blocked();
			break;
		case 1200482: /* DITA2KDB_WS00221C_RESP_PIN_NUMBER_DUPLICATE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_pin_number_duplicate();
			break;
		case 1200483: /* DITA2KDB_WS00221C_RESP_PIN_NUMBER_HOLD */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_pin_number_hold();
			break;
		case 1200484: /* DITA2KDB_WS00221C_RESP_PIN_NUMBER_INACTIVE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_pin_number_inactive();
			break;
		case 1200485: /* DITA2KDB_WS00221C_RESP_PIN_NUMBER_INVALID */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_pin_number_invalid();
			break;
		case 1200486: /* DITA2KDB_WS00221C_RESP_PIN_NUMBER_MULTIPLE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_pin_number_multiple();
			break;
		case 1200487: /* DITA2KDB_WS00221C_RESP_PIN_NUMBER_OFFENDER */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_pin_number_offender();
			break;
		case 1200488: /* DITA2KDB_WS00221C_RESP_PIN_NUMBER_SUSPENDED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_pin_number_suspended();
			break;
		case 1200489: /* DITA2KDB_WS00221C_RESP_PIN_UPDATE_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_pin_update_not_allowed();
			break;
		case 1200490: /* DITA2KDB_WS00221C_RESP_PRC_RECORD_NOT_FND */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_prc_record_not_fnd();
			break;
		case 1200491: /* DITA2KDB_WS00221C_RESP_PROCESS_ERROR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_process_error();
			break;
		case 1200492: /* DITA2KDB_WS00221C_RESP_RECORD_BYPASSED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_record_bypassed();
			break;
		case 1200493: /* DITA2KDB_WS00221C_RESP_RED_AMT_GT_ACCT_VALUE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_red_amt_gt_acct_value();
			break;
		case 1200494: /* DITA2KDB_WS00221C_RESP_REQUEST_ON_UNINIT_TBL */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_request_on_uninit_tbl();
			break;
		case 1200495: /* DITA2KDB_WS00221C_RESP_RETURN_INFO_UNAVAIL */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_return_info_unavail();
			break;
		case 1200496: /* DITA2KDB_WS00221C_RESP_RETURN_NASU_ACCT */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_return_nasu_acct();
			break;
		case 1200497: /* DITA2KDB_WS00221C_RESP_RETURN_SEVERE_ERROR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_return_severe_error();
			break;
		case 1200498: /* DITA2KDB_WS00221C_RESP_RETURN_SYSTEM_DOWN */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_return_system_down();
			break;
		case 1200499: /* DITA2KDB_WS00221C_RESP_SHR_TRAN_NOT_AUTHORIZED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_shr_tran_not_authorized();
			break;
		case 1200500: /* DITA2KDB_WS00221C_RESP_SOCIAL_CODE_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_social_code_not_allowed();
			break;
		case 1200501: /* DITA2KDB_WS00221C_RESP_SOCIAL_CODE_NOT_FOUND */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_social_code_not_found();
			break;
		case 1200502: /* DITA2KDB_WS00221C_RESP_SSN_CERTIF_MISSING */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_ssn_certif_missing();
			break;
		case 1200503: /* DITA2KDB_WS00221C_RESP_STOCK_SPLIT_HST_NOT_FND */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_stock_split_hst_not_fnd();
			break;
		case 1200504: /* DITA2KDB_WS00221C_RESP_SUBROUTINE_ERROR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_subroutine_error();
			break;
		case 1200505: /* DITA2KDB_WS00221C_RESP_SYS_EXCH_REC_EXISTS */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_sys_exch_rec_exists();
			break;
		case 1200506: /* DITA2KDB_WS00221C_RESP_TAF_NOT_EQUAL_MASTER */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_taf_not_equal_master();
			break;
		case 1200507: /* DITA2KDB_WS00221C_RESP_TRAN_SHRS_CONTAIN_CERTS */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_tran_shrs_contain_certs();
			break;
		case 1200508: /* DITA2KDB_WS00221C_RESP_TRAN_SHRS_CONTAIN_ESCROW */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_tran_shrs_contain_escrow();
			break;
		case 1200509: /* DITA2KDB_WS00221C_RESP_TRAN_SHRS_CONTAIN_UNCOLL */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_tran_shrs_contain_uncoll();
			break;
		case 1200510: /* DITA2KDB_WS00221C_RESP_TRAN_TYPE_NOT_DEFINED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_tran_type_not_defined();
			break;
		case 1200511: /* DITA2KDB_WS00221C_RESP_UNABLE_TO_ASSGN_NEXT_ACCT */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_unable_to_assgn_next_acct();
			break;
		case 1200512: /* DITA2KDB_WS00221C_RESP_UNABLE_TO_ASSGN_NXT_CUM_N */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_unable_to_assgn_nxt_cum_n();
			break;
		case 1200513: /* DITA2KDB_WS00221C_RESP_ZERO_UNISSUED_SHARES */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_zero_unissued_shares();
			break;
		case 1200514: /* DITA2KDB_WS00221C_REWRITE_WITHOUT_OPEN_FOR_IO */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_rewrite_without_open_for_io();
			break;
		case 1200515: /* DITA2KDB_WS00221C_ROW_NOT_FOUND */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_row_not_found();
			break;
		case 1200516: /* DITA2KDB_WS00221C_SEQ_READ_AFTER_EOF */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_seq_read_after_eof();
			break;
		case 1200518: /* DITA2KDB_WS00221C_SEVERE_SQL_ERROR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_severe_sql_error();
			break;
		case 1200519: /* DITA2KDB_WS00221C_SUCCESSFUL_OPEN_OPTION_FILE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_successful_open_option_file();
			break;
		case 1200520: /* DITA2KDB_WS00221C_SYSTEM_ERROR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_system_error();
			break;
		case 1200521: /* DITA2KDB_WS00221C_UNAVAILABLE_RESOURCE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_unavailable_resource();
			break;
		case 1200522: /* DITA2KDB_WS00221C_UNEXPECTED_DATA_LENGTH_RETURNED */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_unexpected_data_length_returned();
			break;
		case 1200523: /* DITA2KDB_WS00221C_UNKNOWN_ERROR_CODE */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_unknown_error_code();
			break;
		case 1200524: /* DITA2KDB_WS00221C_VSAM_LOGIC_ERROR */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_vsam_logic_error();
			break;
		case 1200525: /* DITA2KDB_WS00221C_WRITE_WITHOUT_OPEN_FOR_IO */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_write_without_open_for_io();
			break;
		case 1200526: /* DITA2KDB_WS00221C_WRONG_RECORD_LNGTH_ON_READ */
			conditionObj = new CIFast_IFast_dita2kdb_dita2kdb_ws00221c_wrong_record_lngth_on_read();
			break;
		case 1200527: /* ERR_WARN_ACCOUNT_TYPE_DONT_MATCH_FOR_IN_KIND_TRANS */
			conditionObj = new CIFast_IFast_dita2kdb_err_warn_account_type_dont_match_for_in_kind_trans();
			break;
		case 1300001: /* ERR_CITY_NAME_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ditabuscore_err_city_name_not_allowed();
			break;
		case 1300002: /* ERR_CITY_NAME_REQUIRED */
			conditionObj = new CIFast_IFast_ditabuscore_err_city_name_required();
			break;
		case 1300003: /* ERR_FIELD_EMPTY */
			conditionObj = new CIFast_IFast_ditabuscore_err_field_empty();
			break;
		case 1300004: /* ERR_FIELD_MUSTBE_EMPTY */
			conditionObj = new CIFast_IFast_ditabuscore_err_field_mustbe_empty();
			break;
		case 1300005: /* ERR_FIELD_NOT_NUMERIC */
			conditionObj = new CIFast_IFast_ditabuscore_err_field_not_numeric();
			break;
		case 1300006: /* ERR_FIELD_VALUE_ZERO */
			conditionObj = new CIFast_IFast_ditabuscore_err_field_value_zero();
			break;
		case 1300007: /* ERR_FINALIST_ERR */
			conditionObj = new CIFast_IFast_ditabuscore_err_finalist_err();
			break;
		case 1300008: /* ERR_INVALID_ADDRESS_LINE */
			conditionObj = new CIFast_IFast_ditabuscore_err_invalid_address_line();
			break;
		case 1300009: /* ERR_INVALID_CERTIFICATION_STATUS_CODE */
			conditionObj = new CIFast_IFast_ditabuscore_err_invalid_certification_status_code();
			break;
		case 1300010: /* ERR_INVALID_CITY_NAME_WRT_STATE_CODE */
			conditionObj = new CIFast_IFast_ditabuscore_err_invalid_city_name_wrt_state_code();
			break;
		case 1300011: /* ERR_INVALID_FIELD_LENGTH */
			conditionObj = new CIFast_IFast_ditabuscore_err_invalid_field_length();
			break;
		case 1300012: /* ERR_INVALID_FORMAT_TYPE_CODE */
			conditionObj = new CIFast_IFast_ditabuscore_err_invalid_format_type_code();
			break;
		case 1300013: /* ERR_INVALID_MILITARY_LOCATION */
			conditionObj = new CIFast_IFast_ditabuscore_err_invalid_military_location();
			break;
		case 1300014: /* ERR_INVALID_NUMBER_OF_ADDRESS_LINES */
			conditionObj = new CIFast_IFast_ditabuscore_err_invalid_number_of_address_lines();
			break;
		case 1300015: /* ERR_INVALID_STATE_COUNTRY */
			conditionObj = new CIFast_IFast_ditabuscore_err_invalid_state_country();
			break;
		case 1300016: /* ERR_INVALID_STATE_COUNTRY_CODE */
			conditionObj = new CIFast_IFast_ditabuscore_err_invalid_state_country_code();
			break;
		case 1300017: /* ERR_INVALID_ZIP_CODE */
			conditionObj = new CIFast_IFast_ditabuscore_err_invalid_zip_code();
			break;
		case 1300018: /* ERR_INVALID_ZIPCODE */
			conditionObj = new CIFast_IFast_ditabuscore_err_invalid_zipcode();
			break;
		case 1300019: /* ERR_INVALID_ZIPCODE_FOR */
			conditionObj = new CIFast_IFast_ditabuscore_err_invalid_zipcode_for();
			break;
		case 1300020: /* ERR_MILITARY_LOCATION_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ditabuscore_err_military_location_not_allowed();
			break;
		case 1300021: /* ERR_POSTAL_ADDRESS_NOT_FORMATTED */
			conditionObj = new CIFast_IFast_ditabuscore_err_postal_address_not_formatted();
			break;
		case 1300022: /* ERR_S017PE_ERR */
			conditionObj = new CIFast_IFast_ditabuscore_err_s017pe_err();
			break;
		case 1300023: /* ERR_STATE_COUNTRY_CODE_REQUIRED */
			conditionObj = new CIFast_IFast_ditabuscore_err_state_country_code_required();
			break;
		case 1300024: /* ERR_ZIP_CODE_NOT_NUMERIC */
			conditionObj = new CIFast_IFast_ditabuscore_err_zip_code_not_numeric();
			break;
		case 1300025: /* ERR_ZIP_CODE_SUFFIX_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ditabuscore_err_zip_code_suffix_not_allowed();
			break;
		case 1300026: /* ERR_ZIP_CODE_SUFFIX_REQUIRED */
			conditionObj = new CIFast_IFast_ditabuscore_err_zip_code_suffix_required();
			break;
		case 1300027: /* ERR_ZIP_DLVRY_OFFICE_CDE_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ditabuscore_err_zip_dlvry_office_cde_not_allowed();
			break;
		case 1300028: /* ERR_ZIP_DLVRY_OFFICE_CDE_REQUIRED */
			conditionObj = new CIFast_IFast_ditabuscore_err_zip_dlvry_office_cde_required();
			break;
		case 1300029: /* ERR_ZIP_DLVRY_SEQ_NBR_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ditabuscore_err_zip_dlvry_seq_nbr_not_allowed();
			break;
		case 1300030: /* ERR_ZIP_DLVRY_SEQ_NBR_REQUIRED */
			conditionObj = new CIFast_IFast_ditabuscore_err_zip_dlvry_seq_nbr_required();
			break;
		case 1300031: /* WRN_FINALIST_WRN */
			conditionObj = new CIFast_IFast_ditabuscore_wrn_finalist_wrn();
			break;
		case 1300032: /* WRN_LINE_NUMBER */
			conditionObj = new CIFast_IFast_ditabuscore_wrn_line_number();
			break;
		case 1300033: /* WRN_S017PE_WRN */
			conditionObj = new CIFast_IFast_ditabuscore_wrn_s017pe_wrn();
			break;
		case 1500001: /* ERR_AWD_APPLICATION */
			conditionObj = new CIFast_IFast_ifastawd_err_awd_application();
			break;
		case 1500002: /* ERR_BUSINESS_WORKTYPE_STATUS */
			conditionObj = new CIFast_IFast_ifastawd_err_business_worktype_status();
			break;
		case 1500003: /* ERR_COMMENTS_MANDATORY */
			conditionObj = new CIFast_IFast_ifastawd_err_comments_mandatory();
			break;
		case 1500004: /* ERR_NO_AWD_OBJECT_CLONE */
			conditionObj = new CIFast_IFast_ifastawd_err_no_awd_object_clone();
			break;
		case 1500005: /* ERR_NO_AWD_SOURCE_IMAGE */
			conditionObj = new CIFast_IFast_ifastawd_err_no_awd_source_image();
			break;
		case 1500006: /* ERR_NO_COMMENTS */
			conditionObj = new CIFast_IFast_ifastawd_err_no_comments();
			break;
		case 1600001: /* BP_ERR_ACCOUNT_WAS_NOT_ACTIVE */
			conditionObj = new CIFast_IFast_ifastbp_bp_err_account_was_not_active();
			break;
		case 1600002: /* BP_ERR_AGGREGATED_ORDER_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastbp_bp_err_aggregated_order_not_found();
			break;
		case 1600003: /* BP_ERR_BROKER_EMPTY */
			conditionObj = new CIFast_IFast_ifastbp_bp_err_broker_empty();
			break;
		case 1600004: /* BP_ERR_BROKER_OR_BRANCH_EMPTY */
			conditionObj = new CIFast_IFast_ifastbp_bp_err_broker_or_branch_empty();
			break;
		case 1600005: /* BP_ERR_BROKER_OR_BRANCH_OR_SLSREP_EMPTY */
			conditionObj = new CIFast_IFast_ifastbp_bp_err_broker_or_branch_or_slsrep_empty();
			break;
		case 1600006: /* BP_ERR_CANNOT_DELETE_ACTIVE_INDEX */
			conditionObj = new CIFast_IFast_ifastbp_bp_err_cannot_delete_active_index();
			break;
		case 1600007: /* BP_ERR_CLASS_EMPTY */
			conditionObj = new CIFast_IFast_ifastbp_bp_err_class_empty();
			break;
		case 1600008: /* BP_ERR_CLIENT_SETTLE_INSTR_MANDATORY */
			conditionObj = new CIFast_IFast_ifastbp_bp_err_client_settle_instr_mandatory();
			break;
		case 1600009: /* BP_ERR_DATA_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastbp_bp_err_data_not_found();
			break;
		case 1600010: /* BP_ERR_DEMOGRAPHICS_DATA_REQUIRED */
			conditionObj = new CIFast_IFast_ifastbp_bp_err_demographics_data_required();
			break;
		case 1600011: /* BP_ERR_DOCUMENT_LIST_DATA_REQUIRED */
			conditionObj = new CIFast_IFast_ifastbp_bp_err_document_list_data_required();
			break;
		case 1600012: /* BP_ERR_EMPTY_FUND_GROUP */
			conditionObj = new CIFast_IFast_ifastbp_bp_err_empty_fund_group();
			break;
		case 1600013: /* BP_ERR_ENTITY_ADDRESS_LIST_INVALID */
			conditionObj = new CIFast_IFast_ifastbp_bp_err_entity_address_list_invalid();
			break;
		case 1600014: /* BP_ERR_FUND_EMPTY */
			conditionObj = new CIFast_IFast_ifastbp_bp_err_fund_empty();
			break;
		case 1600015: /* BP_ERR_INVALID_DATE_FORMAT */
			conditionObj = new CIFast_IFast_ifastbp_bp_err_invalid_date_format();
			break;
		case 1600016: /* BP_ERR_INVALID_FUND */
			conditionObj = new CIFast_IFast_ifastbp_bp_err_invalid_fund();
			break;
		case 1600017: /* BP_ERR_INVALID_FUND_AND_CLASS */
			conditionObj = new CIFast_IFast_ifastbp_bp_err_invalid_fund_and_class();
			break;
		case 1600018: /* BP_ERR_INVALID_FUND_GROUP */
			conditionObj = new CIFast_IFast_ifastbp_bp_err_invalid_fund_group();
			break;
		case 1600019: /* BP_ERR_INVALID_TRADE_TYPE */
			conditionObj = new CIFast_IFast_ifastbp_bp_err_invalid_trade_type();
			break;
		case 1600020: /* BP_ERR_MORE_THAN_ONE_RECORD_FOUND */
			conditionObj = new CIFast_IFast_ifastbp_bp_err_more_than_one_record_found();
			break;
		case 1600021: /* BP_ERR_MULTI_AGGREGATED_ORDER */
			conditionObj = new CIFast_IFast_ifastbp_bp_err_multi_aggregated_order();
			break;
		case 1600022: /* BP_ERR_MULTIMATCH_ACCOUNTNUMBER */
			conditionObj = new CIFast_IFast_ifastbp_bp_err_multimatch_accountnumber();
			break;
		case 1600023: /* BP_ERR_NO_SEARCH_CRITERIA */
			conditionObj = new CIFast_IFast_ifastbp_bp_err_no_search_criteria();
			break;
		case 1600024: /* BP_ERR_NOT_ALLOW_SETFOCUS */
			conditionObj = new CIFast_IFast_ifastbp_bp_err_not_allow_setfocus();
			break;
		case 1600025: /* BP_ERR_RESP_BENEFICIARY */
			conditionObj = new CIFast_IFast_ifastbp_bp_err_resp_beneficiary();
			break;
		case 1600026: /* BP_ERR_SEL_BROKER_BRANCH_FIRST */
			conditionObj = new CIFast_IFast_ifastbp_bp_err_sel_broker_branch_first();
			break;
		case 1600027: /* BP_ERR_SEL_BROKER_FIRST */
			conditionObj = new CIFast_IFast_ifastbp_bp_err_sel_broker_first();
			break;
		case 1600028: /* BP_NO_ACCESS_TO_ACCTDETAILS */
			conditionObj = new CIFast_IFast_ifastbp_bp_no_access_to_acctdetails();
			break;
		case 1600029: /* BP_WARN_DEMOGRAPHICS_DATA_REQUIRED */
			conditionObj = new CIFast_IFast_ifastbp_bp_warn_demographics_data_required();
			break;
		case 1600030: /* BP_WARN_DOCUMENT_LIST_DATA_REQUIRED */
			conditionObj = new CIFast_IFast_ifastbp_bp_warn_document_list_data_required();
			break;
		case 1600031: /* BP_WARN_SIBLING_ONLY_BLANK_OR_NO */
			conditionObj = new CIFast_IFast_ifastbp_bp_warn_sibling_only_blank_or_no();
			break;
		case 1600032: /* BP_WRN_MORE_THAN_ONE_RECORD_FOUND */
			conditionObj = new CIFast_IFast_ifastbp_bp_wrn_more_than_one_record_found();
			break;
		case 1600033: /* BP_WRN_NO_CLIENT_SETTLE_INSTR */
			conditionObj = new CIFast_IFast_ifastbp_bp_wrn_no_client_settle_instr();
			break;
		case 1600034: /* ERR_ACTIVE_BATCH */
			conditionObj = new CIFast_IFast_ifastbp_err_active_batch();
			break;
		case 1600035: /* ERR_AGENT_LIST_EMPTY */
			conditionObj = new CIFast_IFast_ifastbp_err_agent_list_empty();
			break;
		case 1600036: /* ERR_BRANCH_LIST_EMPTY */
			conditionObj = new CIFast_IFast_ifastbp_err_branch_list_empty();
			break;
		case 1600037: /* ERR_BROKER_LIST_EMPTY */
			conditionObj = new CIFast_IFast_ifastbp_err_broker_list_empty();
			break;
		case 1600038: /* ERR_BROKER_NAME_EMPTY */
			conditionObj = new CIFast_IFast_ifastbp_err_broker_name_empty();
			break;
		case 1600039: /* ERR_FAMILY_CODE_EMPTY */
			conditionObj = new CIFast_IFast_ifastbp_err_family_code_empty();
			break;
		case 1600040: /* ERR_FAMILY_CODE_OR_NAME_NOT_EXISTING */
			conditionObj = new CIFast_IFast_ifastbp_err_family_code_or_name_not_existing();
			break;
		case 1600041: /* ERR_FAMILY_NAME_EMPTY */
			conditionObj = new CIFast_IFast_ifastbp_err_family_name_empty();
			break;
		case 1600042: /* ERR_FUND_BROKER_CODE_EMPTY */
			conditionObj = new CIFast_IFast_ifastbp_err_fund_broker_code_empty();
			break;
		case 1600043: /* ERR_FUND_BROKER_NAME_EMPTY */
			conditionObj = new CIFast_IFast_ifastbp_err_fund_broker_name_empty();
			break;
		case 1600044: /* ERR_FUND_BROKER_NAME_NOT_EXISTING */
			conditionObj = new CIFast_IFast_ifastbp_err_fund_broker_name_not_existing();
			break;
		case 1600045: /* ERR_NO_VALID_SHAREHOLDER_OR_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastbp_err_no_valid_shareholder_or_account();
			break;
		case 1600046: /* ERR_RRIF_INFO_NOT_APPLICABLE */
			conditionObj = new CIFast_IFast_ifastbp_err_rrif_info_not_applicable();
			break;
		case 1600047: /* IFASTBP_CND_VERSION */
			conditionObj = new CIFast_IFast_ifastbp_ifastbp_cnd_version();
			break;
		case 1600048: /* ERR_RESULT_FROM_BROWSER_SCREEN */
			conditionObj = new CIFast_IFast_ifastbp_err_result_from_browser_screen();
			break;
		case 1600049: /* WARN_RESULT_FROM_BROWSER_SCREEN */
			conditionObj = new CIFast_IFast_ifastbp_warn_result_from_browser_screen();
			break;
		case 1700001: /* ACC_TAX_TYPE_NOT_MATCH */
			conditionObj = new CIFast_IFast_ifastcbo_acc_tax_type_not_match();
			break;
		case 1700002: /* AGENT_ERR_AGENT_NOT_ACTIVE */
			conditionObj = new CIFast_IFast_ifastcbo_agent_err_agent_not_active();
			break;
		case 1700003: /* AGENT_ERR_NASU_SLS_REP_LVL_NOT_MET */
			conditionObj = new CIFast_IFast_ifastcbo_agent_err_nasu_sls_rep_lvl_not_met();
			break;
		case 1700004: /* AGENT_ERR_PURCHASE_SLS_REP_LVL_NOT_MET */
			conditionObj = new CIFast_IFast_ifastcbo_agent_err_purchase_sls_rep_lvl_not_met();
			break;
		case 1700005: /* AGENT_WARN_NASU_SLS_REP_LVL_NOT_MET */
			conditionObj = new CIFast_IFast_ifastcbo_agent_warn_nasu_sls_rep_lvl_not_met();
			break;
		case 1700006: /* AGENT_WARN_PURCHASE_SLS_REP_LVL_NOT_MET */
			conditionObj = new CIFast_IFast_ifastcbo_agent_warn_purchase_sls_rep_lvl_not_met();
			break;
		case 1700007: /* AMS_ERR_CANNOT_ADD_GIC */
			conditionObj = new CIFast_IFast_ifastcbo_ams_err_cannot_add_gic();
			break;
		case 1700008: /* AMS_ERR_CANNOT_ADD_MPS */
			conditionObj = new CIFast_IFast_ifastcbo_ams_err_cannot_add_mps();
			break;
		case 1700009: /* AMS_ERR_CANNOT_PURCHASE_FUND_OUTSIDE_ALLOC */
			conditionObj = new CIFast_IFast_ifastcbo_ams_err_cannot_purchase_fund_outside_alloc();
			break;
		case 1700010: /* AMS_ERR_EXCHANGE_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_ams_err_exchange_not_allowed();
			break;
		case 1700011: /* AMS_ERR_TRADE_WIRE_ORDER_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_ams_err_trade_wire_order_not_allowed();
			break;
		case 1700012: /* AMS_ERR_USER_NO_PERMISSION_OVERRIDE_AMS_ALLOC */
			conditionObj = new CIFast_IFast_ifastcbo_ams_err_user_no_permission_override_ams_alloc();
			break;
		case 1700013: /* AMS_LMT_ERR_GRANDFATHERED_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_ams_lmt_err_grandfathered_date();
			break;
		case 1700014: /* AMS_LMT_ERR_MAX_REDEEM */
			conditionObj = new CIFast_IFast_ifastcbo_ams_lmt_err_max_redeem();
			break;
		case 1700015: /* AMS_LMT_ERR_MIN_PAC */
			conditionObj = new CIFast_IFast_ifastcbo_ams_lmt_err_min_pac();
			break;
		case 1700016: /* AMS_LMT_ERR_MIN_PURCHASE */
			conditionObj = new CIFast_IFast_ifastcbo_ams_lmt_err_min_purchase();
			break;
		case 1700017: /* AMS_LMT_ERR_MIN_SUB_PURCHASE */
			conditionObj = new CIFast_IFast_ifastcbo_ams_lmt_err_min_sub_purchase();
			break;
		case 1700018: /* AMS_LMT_ERR_MIN_SWP */
			conditionObj = new CIFast_IFast_ifastcbo_ams_lmt_err_min_swp();
			break;
		case 1700019: /* AMS_LMT_ERR_STOP_AT_IN */
			conditionObj = new CIFast_IFast_ifastcbo_ams_lmt_err_stop_at_in();
			break;
		case 1700020: /* AMS_LMT_ERR_STOP_AT_OUT */
			conditionObj = new CIFast_IFast_ifastcbo_ams_lmt_err_stop_at_out();
			break;
		case 1700021: /* AMS_LMT_ERR_STOP_PAC */
			conditionObj = new CIFast_IFast_ifastcbo_ams_lmt_err_stop_pac();
			break;
		case 1700022: /* AMS_LMT_ERR_STOP_PURCHASE */
			conditionObj = new CIFast_IFast_ifastcbo_ams_lmt_err_stop_purchase();
			break;
		case 1700023: /* AMS_LMT_ERR_STOP_REDEMPTION */
			conditionObj = new CIFast_IFast_ifastcbo_ams_lmt_err_stop_redemption();
			break;
		case 1700024: /* AMS_LMT_ERR_STOP_SWP */
			conditionObj = new CIFast_IFast_ifastcbo_ams_lmt_err_stop_swp();
			break;
		case 1700025: /* AMS_LMT_ERR_STOP_TRANSFER_IN */
			conditionObj = new CIFast_IFast_ifastcbo_ams_lmt_err_stop_transfer_in();
			break;
		case 1700026: /* AMS_LMT_ERR_STOP_TRANSFER_OUT */
			conditionObj = new CIFast_IFast_ifastcbo_ams_lmt_err_stop_transfer_out();
			break;
		case 1700027: /* AMS_LMT_WARN_GRANDFATHERED_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_ams_lmt_warn_grandfathered_date();
			break;
		case 1700028: /* AMS_LMT_WARN_MAX_REDEEM */
			conditionObj = new CIFast_IFast_ifastcbo_ams_lmt_warn_max_redeem();
			break;
		case 1700029: /* AMS_LMT_WARN_MIN_PAC */
			conditionObj = new CIFast_IFast_ifastcbo_ams_lmt_warn_min_pac();
			break;
		case 1700030: /* AMS_LMT_WARN_MIN_PURCHASE */
			conditionObj = new CIFast_IFast_ifastcbo_ams_lmt_warn_min_purchase();
			break;
		case 1700031: /* AMS_LMT_WARN_MIN_SUB_PURCHASE */
			conditionObj = new CIFast_IFast_ifastcbo_ams_lmt_warn_min_sub_purchase();
			break;
		case 1700032: /* AMS_LMT_WARN_MIN_SWP */
			conditionObj = new CIFast_IFast_ifastcbo_ams_lmt_warn_min_swp();
			break;
		case 1700033: /* AMS_LMT_WARN_STOP_AT_IN */
			conditionObj = new CIFast_IFast_ifastcbo_ams_lmt_warn_stop_at_in();
			break;
		case 1700034: /* AMS_LMT_WARN_STOP_AT_OUT */
			conditionObj = new CIFast_IFast_ifastcbo_ams_lmt_warn_stop_at_out();
			break;
		case 1700035: /* AMS_LMT_WARN_STOP_PAC */
			conditionObj = new CIFast_IFast_ifastcbo_ams_lmt_warn_stop_pac();
			break;
		case 1700036: /* AMS_LMT_WARN_STOP_PURCHASE */
			conditionObj = new CIFast_IFast_ifastcbo_ams_lmt_warn_stop_purchase();
			break;
		case 1700037: /* AMS_LMT_WARN_STOP_REDEMPTION */
			conditionObj = new CIFast_IFast_ifastcbo_ams_lmt_warn_stop_redemption();
			break;
		case 1700038: /* AMS_LMT_WARN_STOP_SWP */
			conditionObj = new CIFast_IFast_ifastcbo_ams_lmt_warn_stop_swp();
			break;
		case 1700039: /* AMS_LMT_WARN_STOP_TRANSFER_IN */
			conditionObj = new CIFast_IFast_ifastcbo_ams_lmt_warn_stop_transfer_in();
			break;
		case 1700040: /* AMS_LMT_WARN_STOP_TRANSFER_OUT */
			conditionObj = new CIFast_IFast_ifastcbo_ams_lmt_warn_stop_transfer_out();
			break;
		case 1700041: /* BP_ERR_NO_SEARCH_CRTITERIA */
			conditionObj = new CIFast_IFast_ifastcbo_bp_err_no_search_crtiteria();
			break;
		case 1700042: /* CONSOL_TYPE_MANDATORY */
			conditionObj = new CIFast_IFast_ifastcbo_consol_type_mandatory();
			break;
		case 1700043: /* EFT_PURCHASE_NOT_APPLICABLE_ALLOC_TRADE */
			conditionObj = new CIFast_IFast_ifastcbo_eft_purchase_not_applicable_alloc_trade();
			break;
		case 1700044: /* ERR_ACADEMIC_DAY_MUST_BE_01 */
			conditionObj = new CIFast_IFast_ifastcbo_err_academic_day_must_be_01();
			break;
		case 1700045: /* ERR_ACADEMIC_YEAR_LENGTH_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_academic_year_length_required();
			break;
		case 1700046: /* ERR_ACC_TAX_TYPE_NOT_MATCH */
			conditionObj = new CIFast_IFast_ifastcbo_err_acc_tax_type_not_match();
			break;
		case 1700047: /* ERR_ACCOUNT_ATTATCHED_TFR_NEED_TO_BE_STOPPED */
			conditionObj = new CIFast_IFast_ifastcbo_err_account_attatched_tfr_need_to_be_stopped();
			break;
		case 1700048: /* ERR_ACCOUNT_CODED_AS_ASSIGNED */
			conditionObj = new CIFast_IFast_ifastcbo_err_account_coded_as_assigned();
			break;
		case 1700049: /* ERR_ACCOUNT_DELETED */
			conditionObj = new CIFast_IFast_ifastcbo_err_account_deleted();
			break;
		case 1700050: /* ERR_ACCOUNT_DESIGNATION_MUST_SAME_AND_IS_NOT_1 */
			conditionObj = new CIFast_IFast_ifastcbo_err_account_designation_must_same_and_is_not_1();
			break;
		case 1700051: /* ERR_ACCOUNT_EMPTY */
			conditionObj = new CIFast_IFast_ifastcbo_err_account_empty();
			break;
		case 1700052: /* ERR_ACCOUNT_ESCROW_FLAG_IS_ACTIVE */
			conditionObj = new CIFast_IFast_ifastcbo_err_account_escrow_flag_is_active();
			break;
		case 1700053: /* ERR_ACCOUNT_FUND_NOT_PUEV_CAPABLE */
			conditionObj = new CIFast_IFast_ifastcbo_err_account_fund_not_puev_capable();
			break;
		case 1700054: /* ERR_ACCOUNT_IS_BEING_ACTIVATED */
			conditionObj = new CIFast_IFast_ifastcbo_err_account_is_being_activated();
			break;
		case 1700055: /* ERR_ACCOUNT_NOT_IN_REPOSITORY */
			conditionObj = new CIFast_IFast_ifastcbo_err_account_not_in_repository();
			break;
		case 1700056: /* ERR_ACCOUNT_NOTINALS_ARE_ZERO */
			conditionObj = new CIFast_IFast_ifastcbo_err_account_notinals_are_zero();
			break;
		case 1700057: /* ERR_ACCOUNT_NUM_CANNOT_BE_LEFT_EMPTY */
			conditionObj = new CIFast_IFast_ifastcbo_err_account_num_cannot_be_left_empty();
			break;
		case 1700058: /* ERR_ACCOUNT_NUM_NEEDED_FOR_CLOSE_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_account_num_needed_for_close_account();
			break;
		case 1700059: /* ERR_ACCOUNT_NUMBER_CANNOT_START_WITH_ZERO */
			conditionObj = new CIFast_IFast_ifastcbo_err_account_number_cannot_start_with_zero();
			break;
		case 1700060: /* ERR_ACCOUNT_NUMBER_EMPTY */
			conditionObj = new CIFast_IFast_ifastcbo_err_account_number_empty();
			break;
		case 1700061: /* ERR_ACCOUNT_NUMBER_EXISTS */
			conditionObj = new CIFast_IFast_ifastcbo_err_account_number_exists();
			break;
		case 1700062: /* ERR_ACCOUNT_NUMBER_NOT_ALL_DIGITS */
			conditionObj = new CIFast_IFast_ifastcbo_err_account_number_not_all_digits();
			break;
		case 1700063: /* ERR_ACCOUNT_OWNER_AGE_OVER_69 */
			conditionObj = new CIFast_IFast_ifastcbo_err_account_owner_age_over_69();
			break;
		case 1700064: /* ERR_ACCOUNT_OWNER_ENTITY_MUST_BE_SETUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_account_owner_entity_must_be_setup();
			break;
		case 1700065: /* ERR_ACCOUNT_REDEMPTION_FLAG_ENABLED */
			conditionObj = new CIFast_IFast_ifastcbo_err_account_redemption_flag_enabled();
			break;
		case 1700066: /* ERR_ACCOUNT_STOP_FLAG_ON */
			conditionObj = new CIFast_IFast_ifastcbo_err_account_stop_flag_on();
			break;
		case 1700067: /* ERR_ACCOUNT_TYPE_DONT_MATCH_FOR_IN_KIND_TRANS */
			conditionObj = new CIFast_IFast_ifastcbo_err_account_type_dont_match_for_in_kind_trans();
			break;
		case 1700068: /* ERR_ACCOUNT_TYPE_EMPTY */
			conditionObj = new CIFast_IFast_ifastcbo_err_account_type_empty();
			break;
		case 1700069: /* ERR_ACCOUNT_TYPE_MUST_SAME */
			conditionObj = new CIFast_IFast_ifastcbo_err_account_type_must_same();
			break;
		case 1700070: /* ERR_ACCOUNTABILITY_FOR_BACKDATE_TRADE */
			conditionObj = new CIFast_IFast_ifastcbo_err_accountability_for_backdate_trade();
			break;
		case 1700071: /* ERR_ACCOUNTABILITY_ONLY_FOR_BACKDATE_TRADE */
			conditionObj = new CIFast_IFast_ifastcbo_err_accountability_only_for_backdate_trade();
			break;
		case 1700072: /* ERR_ACCOUNTABLE_CODE_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_accountable_code_required();
			break;
		case 1700073: /* ERR_ACCOUNTHOLDER_DEATH_DATE_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_accountholder_death_date_required();
			break;
		case 1700074: /* ERR_ACCOUNTREVIEW_REVIEW_DATE_EARLIER */
			conditionObj = new CIFast_IFast_ifastcbo_err_accountreview_review_date_earlier();
			break;
		case 1700075: /* ERR_ACCOUNTREVIEW_SCHEDULED_DATE_EARLIER */
			conditionObj = new CIFast_IFast_ifastcbo_err_accountreview_scheduled_date_earlier();
			break;
		case 1700076: /* ERR_ACCOUNTS_HAVE_DIFFERENT_SIBLINGONLY_STATUS */
			conditionObj = new CIFast_IFast_ifastcbo_err_accounts_have_different_siblingonly_status();
			break;
		case 1700077: /* ERR_ACCRUALS_FUND_NOT_IN_HOLDINGS */
			conditionObj = new CIFast_IFast_ifastcbo_err_accruals_fund_not_in_holdings();
			break;
		case 1700078: /* ERR_ACCT_ALLOC_LIST_MANAGEMENT_FEE */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_alloc_list_management_fee();
			break;
		case 1700079: /* ERR_ACCT_ALLOC_ONE_ACCOUNT_ONLY */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_alloc_one_account_only();
			break;
		case 1700080: /* ERR_ACCT_ASSIGNED_COURT_ORDER */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_assigned_court_order();
			break;
		case 1700081: /* ERR_ACCT_BALANCE_TERM_AND_DEL */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_balance_term_and_del();
			break;
		case 1700082: /* ERR_ACCT_BALANCE_TERM_AND_DEL_MAINT */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_balance_term_and_del_maint();
			break;
		case 1700083: /* ERR_ACCT_BALANCE_ZERO */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_balance_zero();
			break;
		case 1700084: /* ERR_ACCT_CANNOT_BE_CLOSE */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_cannot_be_close();
			break;
		case 1700085: /* ERR_ACCT_CATEGORY_NOT_ALLOWED_FOR_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_category_not_allowed_for_account();
			break;
		case 1700086: /* ERR_ACCT_CATEGORY_NOT_CO_EXIST */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_category_not_co_exist();
			break;
		case 1700087: /* ERR_ACCT_CONT_NON_ACTIVE_STATUS_SELECTED */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_cont_non_active_status_selected();
			break;
		case 1700088: /* ERR_ACCT_CONT_SETTL_STATUS_CANNOT_BE_SELECTED */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_cont_settl_status_cannot_be_selected();
			break;
		case 1700089: /* ERR_ACCT_CONTROL_EXISTS */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_control_exists();
			break;
		case 1700090: /* ERR_ACCT_CONTROL_NOT_EXISTS */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_control_not_exists();
			break;
		case 1700091: /* ERR_ACCT_CONTROL_UNABLE_TO_MODIFY */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_control_unable_to_modify();
			break;
		case 1700092: /* ERR_ACCT_DESIGNATION_MUST_SAME_IN_KIND_TRANS */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_designation_must_same_in_kind_trans();
			break;
		case 1700093: /* ERR_ACCT_DOES_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_does_not_exist();
			break;
		case 1700094: /* ERR_ACCT_EFFECTIVE_DATE_VALIDATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_effective_date_validate();
			break;
		case 1700095: /* ERR_ACCT_FROM_TRANSFER_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_from_transfer_not_allowed();
			break;
		case 1700096: /* ERR_ACCT_FUND_CLASS_NOT_UNIQUE */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_fund_class_not_unique();
			break;
		case 1700097: /* ERR_ACCT_HAS_ALREADY_REBALANCE */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_has_already_rebalance();
			break;
		case 1700098: /* ERR_ACCT_HAS_STOPPED_PAC_OR_PURCH */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_has_stopped_pac_or_purch();
			break;
		case 1700099: /* ERR_ACCT_HAS_STOPPED_SWP_OR_REDEM */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_has_stopped_swp_or_redem();
			break;
		case 1700100: /* ERR_ACCT_INACTIVE */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_inactive();
			break;
		case 1700101: /* ERR_ACCT_INACTIVE_ON_TRADE_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_inactive_on_trade_date();
			break;
		case 1700102: /* ERR_ACCT_INELIGIBILE_PAY_OPTION_WAIVED */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_ineligibile_pay_option_waived();
			break;
		case 1700103: /* ERR_ACCT_INVALID_FOR_THIS_SHR */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_invalid_for_this_shr();
			break;
		case 1700104: /* ERR_ACCT_LOCKED_NO_REDEMPTION_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_locked_no_redemption_available();
			break;
		case 1700105: /* ERR_ACCT_MIN_ALLOWABLE_PURCHASE */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_min_allowable_purchase();
			break;
		case 1700106: /* ERR_ACCT_MIN_BALANCE */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_min_balance();
			break;
		case 1700107: /* ERR_ACCT_MIN_INIT_PURCHASE */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_min_init_purchase();
			break;
		case 1700108: /* ERR_ACCT_NBR_ALREADY_EXISTS */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_nbr_already_exists();
			break;
		case 1700109: /* ERR_ACCT_NO_HOLDINGS */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_no_holdings();
			break;
		case 1700110: /* ERR_ACCT_NO_HOLDINGS_FOR_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_no_holdings_for_fund();
			break;
		case 1700111: /* ERR_ACCT_NOT_DTA_ELIGIBLE */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_not_dta_eligible();
			break;
		case 1700112: /* ERR_ACCT_OWNER_DUPLICATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_owner_duplicate();
			break;
		case 1700113: /* ERR_ACCT_OWNER_MUST_SAME_IN_KIND_TRANS */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_owner_must_same_in_kind_trans();
			break;
		case 1700114: /* ERR_ACCT_OWNER_SEQ_ONE_NEEDED */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_owner_seq_one_needed();
			break;
		case 1700115: /* ERR_ACCT_PURCHASE_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_purchase_not_allowed();
			break;
		case 1700116: /* ERR_ACCT_REDEMPTION_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_redemption_not_allowed();
			break;
		case 1700117: /* ERR_ACCT_SPLIT_COMM_INVALID_DATE_RANGE */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_split_comm_invalid_date_range();
			break;
		case 1700118: /* ERR_ACCT_SPLIT_COMM_NO_ACTIVE_DATE_RANGE */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_split_comm_no_active_date_range();
			break;
		case 1700119: /* ERR_ACCT_STATUS_DEATH_OR_DEATH_TRANSFER */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_status_death_or_death_transfer();
			break;
		case 1700120: /* ERR_ACCT_TERMINATED */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_terminated();
			break;
		case 1700121: /* ERR_ACCT_TO_IS_INVALID */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_to_is_invalid();
			break;
		case 1700122: /* ERR_ACCT_TO_TRANSFER_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_to_transfer_not_allowed();
			break;
		case 1700123: /* ERR_ACCT_TRANSFER_IN_FLAG_ENABLE */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_transfer_in_flag_enable();
			break;
		case 1700124: /* ERR_ACCT_TYPE_MUST_SAME_IN_KIND_TRANS */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_type_must_same_in_kind_trans();
			break;
		case 1700125: /* ERR_ACCT_TYPE_NOT_VALID_FOR_TAX_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_type_not_valid_for_tax_type();
			break;
		case 1700126: /* ERR_ACCTGROUP_REQUIRED_ON_PORTFOLIO_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_acctgroup_required_on_portfolio_required();
			break;
		case 1700127: /* ERR_ACCTHOLDER_DOFB_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_acctholder_dofb_missing();
			break;
		case 1700128: /* ERR_ACCTHOLDER_DOFBIRTH_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_acctholder_dofbirth_missing();
			break;
		case 1700129: /* ERR_ACCTHOLDER_OVER_AGE_FOR_PROTECTED_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_acctholder_over_age_for_protected_fund();
			break;
		case 1700130: /* ERR_ACCTOUNTIBILITY_BACKDATEDREASON_ARE_REQUIRED_FOR_DILUTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_acctountibility_backdatedreason_are_required_for_dilution();
			break;
		case 1700131: /* ERR_ACCTOWNER_SIN_INVALID */
			conditionObj = new CIFast_IFast_ifastcbo_err_acctowner_sin_invalid();
			break;
		case 1700132: /* ERR_ACCTOWNER_SIN_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_acctowner_sin_missing();
			break;
		case 1700133: /* ERR_ACCTUSE_ALREADY_EXIST */
			conditionObj = new CIFast_IFast_ifastcbo_err_acctuse_already_exist();
			break;
		case 1700134: /* ERR_ACQ_FEE_OPTION_NOT_APPLICABLE_FOR_ADL_ENV */
			conditionObj = new CIFast_IFast_ifastcbo_err_acq_fee_option_not_applicable_for_adl_env();
			break;
		case 1700135: /* ERR_ACQ_FEE_OPTION_ONLY_APPLICABLE_FOR_3RD_PARTY_FUNDS */
			conditionObj = new CIFast_IFast_ifastcbo_err_acq_fee_option_only_applicable_for_3rd_party_funds();
			break;
		case 1700136: /* ERR_ACQ_FEES_MUST_BE_ZERO_FOR_AUTOMATIC_TRANSFER */
			conditionObj = new CIFast_IFast_ifastcbo_err_acq_fees_must_be_zero_for_automatic_transfer();
			break;
		case 1700137: /* ERR_ACTIVE_SWP_AMTTYPE_EXISTS */
			conditionObj = new CIFast_IFast_ifastcbo_err_active_swp_amttype_exists();
			break;
		case 1700138: /* ERR_ACTIVE_SWP_CONTTYPE_EXISTS */
			conditionObj = new CIFast_IFast_ifastcbo_err_active_swp_conttype_exists();
			break;
		case 1700139: /* ERR_ADD_ENTITY_DEATH_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_add_entity_death_date();
			break;
		case 1700140: /* ERR_ADD_LINKED_CONTRACT */
			conditionObj = new CIFast_IFast_ifastcbo_err_add_linked_contract();
			break;
		case 1700141: /* ERR_ADDING_TRANSFER_IS_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_adding_transfer_is_not_allowed();
			break;
		case 1700142: /* ERR_ADDRCODE_MUST_BE_SAME_FOR_SAME_DOCTYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_addrcode_must_be_same_for_same_doctype();
			break;
		case 1700143: /* ERR_ADDRESS_CODE_INVALID */
			conditionObj = new CIFast_IFast_ifastcbo_err_address_code_invalid();
			break;
		case 1700144: /* ERR_ADDRESS_CODE_NOT_EFFECTIVE */
			conditionObj = new CIFast_IFast_ifastcbo_err_address_code_not_effective();
			break;
		case 1700145: /* ERR_ADDRESS_CODE_NOT_SETUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_address_code_not_setup();
			break;
		case 1700146: /* ERR_ADDRESS_CODE_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_address_code_required();
			break;
		case 1700147: /* ERR_ADDRESS_CODE_USEDBY_MAILING */
			conditionObj = new CIFast_IFast_ifastcbo_err_address_code_usedby_mailing();
			break;
		case 1700148: /* ERR_ADDRESS_DOES_NOT_EXIST_FOR_THIS_INSTITUTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_address_does_not_exist_for_this_institution();
			break;
		case 1700149: /* ERR_ADDRESS_ID_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_address_id_not_found();
			break;
		case 1700150: /* ERR_ADDRESS_LINE_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_address_line_missing();
			break;
		case 1700151: /* ERR_ADDRESS_LINE45 */
			conditionObj = new CIFast_IFast_ifastcbo_err_address_line45();
			break;
		case 1700152: /* ERR_ADDRESS_NOT_VERIFY */
			conditionObj = new CIFast_IFast_ifastcbo_err_address_not_verify();
			break;
		case 1700153: /* ERR_ADDRESS_TWO_LINE */
			conditionObj = new CIFast_IFast_ifastcbo_err_address_two_line();
			break;
		case 1700154: /* ERR_ADJUSTMENT_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_adjustment_required();
			break;
		case 1700155: /* ERR_ADL_FEE_PERCENTAGE_FOR_DEFAULT_RECORD */
			conditionObj = new CIFast_IFast_ifastcbo_err_adl_fee_percentage_for_default_record();
			break;
		case 1700156: /* ERR_AGENT_INVALID_AS_OF_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_agent_invalid_as_of_date();
			break;
		case 1700157: /* ERR_AGENT_NOT_EFFECTIVE */
			conditionObj = new CIFast_IFast_ifastcbo_err_agent_not_effective();
			break;
		case 1700158: /* ERR_AGENT_NOT_ELIGIBLE_FOR_ACCT */
			conditionObj = new CIFast_IFast_ifastcbo_err_agent_not_eligible_for_acct();
			break;
		case 1700159: /* ERR_AGENT_NOT_FOUND_FOR_BROKER_BRANCH */
			conditionObj = new CIFast_IFast_ifastcbo_err_agent_not_found_for_broker_branch();
			break;
		case 1700160: /* ERR_AGENT_TPA_SAME */
			conditionObj = new CIFast_IFast_ifastcbo_err_agent_tpa_same();
			break;
		case 1700161: /* ERR_AGENTFORFIRM_INVALID */
			conditionObj = new CIFast_IFast_ifastcbo_err_agentforfirm_invalid();
			break;
		case 1700162: /* ERR_AGENTFORFIRM_NOT_RELATED_TO_CLEARINGFIRM */
			conditionObj = new CIFast_IFast_ifastcbo_err_agentforfirm_not_related_to_clearingfirm();
			break;
		case 1700163: /* ERR_AGGREGATED_ORDER_TRADE_DATE_INVALID */
			conditionObj = new CIFast_IFast_ifastcbo_err_aggregated_order_trade_date_invalid();
			break;
		case 1700164: /* ERR_AIP_ENTITY_NOT_CANADIEN */
			conditionObj = new CIFast_IFast_ifastcbo_err_aip_entity_not_canadien();
			break;
		case 1700165: /* ERR_AIP_TO_NONRESIDENT_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_aip_to_nonresident_not_allowed();
			break;
		case 1700166: /* ERR_AIP_WITHDRAWAL_EXISTS_TX_TO_ANOTHER_RESP_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_aip_withdrawal_exists_tx_to_another_resp_not_allowed();
			break;
		case 1700167: /* ERR_ALLOC_AMT_EXCEEDS_TRADE_AMT */
			conditionObj = new CIFast_IFast_ifastcbo_err_alloc_amt_exceeds_trade_amt();
			break;
		case 1700168: /* ERR_ALLOC_FOR_ACCT_TYPE06 */
			conditionObj = new CIFast_IFast_ifastcbo_err_alloc_for_acct_type06();
			break;
		case 1700169: /* ERR_ALLOC_FOR_INACTIVE_ACCT */
			conditionObj = new CIFast_IFast_ifastcbo_err_alloc_for_inactive_acct();
			break;
		case 1700170: /* ERR_ALLOC_TYPE_IS_BLANK */
			conditionObj = new CIFast_IFast_ifastcbo_err_alloc_type_is_blank();
			break;
		case 1700171: /* ERR_ALLOCAMOUNT_GREATER_THAN_TOTAL */
			conditionObj = new CIFast_IFast_ifastcbo_err_allocamount_greater_than_total();
			break;
		case 1700172: /* ERR_ALLOCAMOUNT_LESS_THAN_TOTAL */
			conditionObj = new CIFast_IFast_ifastcbo_err_allocamount_less_than_total();
			break;
		case 1700173: /* ERR_ALLOCATION_MUST_BE_ENTERED */
			conditionObj = new CIFast_IFast_ifastcbo_err_allocation_must_be_entered();
			break;
		case 1700174: /* ERR_ALLOCATION_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_allocation_not_allowed();
			break;
		case 1700175: /* ERR_ALLOCATION_TOTAL_INCORRECT */
			conditionObj = new CIFast_IFast_ifastcbo_err_allocation_total_incorrect();
			break;
		case 1700176: /* ERR_ALTACCT_REQUIRED_FOR_PUEV_INVESTRO */
			conditionObj = new CIFast_IFast_ifastcbo_err_altacct_required_for_puev_investro();
			break;
		case 1700177: /* ERR_AMENDMENT_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_amendment_required();
			break;
		case 1700178: /* ERR_AMOUNT_DOES_NOT_MATCH */
			conditionObj = new CIFast_IFast_ifastcbo_err_amount_does_not_match();
			break;
		case 1700179: /* ERR_AMOUNT_EXCEED_MAX_LIMIT */
			conditionObj = new CIFast_IFast_ifastcbo_err_amount_exceed_max_limit();
			break;
		case 1700180: /* ERR_AMOUNT_EXCEEDS_PRINCIPAL */
			conditionObj = new CIFast_IFast_ifastcbo_err_amount_exceeds_principal();
			break;
		case 1700181: /* ERR_AMOUNT_GREAT_THAN_MAX */
			conditionObj = new CIFast_IFast_ifastcbo_err_amount_great_than_max();
			break;
		case 1700182: /* ERR_AMOUNT_GREATER_THAN_HOLDING */
			conditionObj = new CIFast_IFast_ifastcbo_err_amount_greater_than_holding();
			break;
		case 1700183: /* ERR_AMOUNT_IS_LESS_THEN_MINIMUM_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_amount_is_less_then_minimum_required();
			break;
		case 1700184: /* ERR_AMOUNT_IS_OVER_THRESHOLD */
			conditionObj = new CIFast_IFast_ifastcbo_err_amount_is_over_threshold();
			break;
		case 1700185: /* ERR_AMOUNT_MISMATCH */
			conditionObj = new CIFast_IFast_ifastcbo_err_amount_mismatch();
			break;
		case 1700186: /* ERR_AMOUNT_MUST_BE_0_FOR_ALL_FUND_TRANSFER */
			conditionObj = new CIFast_IFast_ifastcbo_err_amount_must_be_0_for_all_fund_transfer();
			break;
		case 1700187: /* ERR_AMOUNT_MUST_BE_GREATER_THAN_ZERO */
			conditionObj = new CIFast_IFast_ifastcbo_err_amount_must_be_greater_than_zero();
			break;
		case 1700188: /* ERR_AMOUNT_MUST_BE_ZERO_FOR_FULL_RED */
			conditionObj = new CIFast_IFast_ifastcbo_err_amount_must_be_zero_for_full_red();
			break;
		case 1700189: /* ERR_AMOUNT_MUST_BE_ZERO_IF_ESCROW_REASON_CODE_IS_BANKRUPTCY */
			conditionObj = new CIFast_IFast_ifastcbo_err_amount_must_be_zero_if_escrow_reason_code_is_bankruptcy();
			break;
		case 1700190: /* ERR_AMOUNT_MUST_BE_ZERO_WHEN_CLOSING_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_amount_must_be_zero_when_closing_account();
			break;
		case 1700191: /* ERR_AMOUNT_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_amount_not_allowed();
			break;
		case 1700192: /* ERR_AMOUNT_TYPE_INVALID_FOR_3_RD_PARTY_FUNDS_VIA_NETWORK */
			conditionObj = new CIFast_IFast_ifastcbo_err_amount_type_invalid_for_3_rd_party_funds_via_network();
			break;
		case 1700193: /* ERR_AMOUNT_TYPE_INVALID_FOR_3_RD_PARTY_FUNDS_WITH_FUNDBROKER */
			conditionObj = new CIFast_IFast_ifastcbo_err_amount_type_invalid_for_3_rd_party_funds_with_fundbroker();
			break;
		case 1700194: /* ERR_AMOUNT_TYPE_INVALID_FOR_DEPOT_FUNDS */
			conditionObj = new CIFast_IFast_ifastcbo_err_amount_type_invalid_for_depot_funds();
			break;
		case 1700195: /* ERR_AMOUNT_TYPE_INVALID_FOR_SPECIAL_FUNDS */
			conditionObj = new CIFast_IFast_ifastcbo_err_amount_type_invalid_for_special_funds();
			break;
		case 1700196: /* ERR_AMOUNT_TYPE_IS_MANDATORY */
			conditionObj = new CIFast_IFast_ifastcbo_err_amount_type_is_mandatory();
			break;
		case 1700197: /* ERR_AMOUNT_TYPE_NOT_VALID_FOR_REDCODE */
			conditionObj = new CIFast_IFast_ifastcbo_err_amount_type_not_valid_for_redcode();
			break;
		case 1700198: /* ERR_AMS_ACCOUNT_DESIGNATION */
			conditionObj = new CIFast_IFast_ifastcbo_err_ams_account_designation();
			break;
		case 1700199: /* ERR_AMS_ACCOUNT_HOLD_GIC */
			conditionObj = new CIFast_IFast_ifastcbo_err_ams_account_hold_gic();
			break;
		case 1700200: /* ERR_AMS_ACCOUNT_RESIDENT_PROVINCE */
			conditionObj = new CIFast_IFast_ifastcbo_err_ams_account_resident_province();
			break;
		case 1700201: /* ERR_AMS_ACCOUNT_TAX_JURISDICTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_ams_account_tax_jurisdiction();
			break;
		case 1700202: /* ERR_AMS_ACCOUNT_TAX_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_ams_account_tax_type();
			break;
		case 1700203: /* ERR_AMS_ACCOUNT_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_ams_account_type();
			break;
		case 1700204: /* ERR_AMS_CANNOT_SETUP_FOR_ACCOUNT_HOLDING_MULTICURRENCY_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_ams_cannot_setup_for_account_holding_multicurrency_fund();
			break;
		case 1700205: /* ERR_AMS_CODE_FOR_BROKER_IS_BAD */
			conditionObj = new CIFast_IFast_ifastcbo_err_ams_code_for_broker_is_bad();
			break;
		case 1700206: /* ERR_AMS_CODE_FOR_BROKER_IS_FUTURE_DATED */
			conditionObj = new CIFast_IFast_ifastcbo_err_ams_code_for_broker_is_future_dated();
			break;
		case 1700207: /* ERR_AMS_CODE_IN_USE */
			conditionObj = new CIFast_IFast_ifastcbo_err_ams_code_in_use();
			break;
		case 1700208: /* ERR_AMS_CODE_NOT_AVAILABLE_FOR_BROKER */
			conditionObj = new CIFast_IFast_ifastcbo_err_ams_code_not_available_for_broker();
			break;
		case 1700209: /* ERR_AMS_CODE_RESTRICTED */
			conditionObj = new CIFast_IFast_ifastcbo_err_ams_code_restricted();
			break;
		case 1700210: /* ERR_AMS_CODE_RESTRICTED_FOR_BROKER */
			conditionObj = new CIFast_IFast_ifastcbo_err_ams_code_restricted_for_broker();
			break;
		case 1700211: /* ERR_AMS_CODE_SET_UP */
			conditionObj = new CIFast_IFast_ifastcbo_err_ams_code_set_up();
			break;
		case 1700212: /* ERR_AMS_CODE_SET_UP_0001 */
			conditionObj = new CIFast_IFast_ifastcbo_err_ams_code_set_up_0001();
			break;
		case 1700213: /* ERR_AMS_ESCROW_FOR_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_ams_escrow_for_account();
			break;
		case 1700214: /* ERR_AMS_FUND_CLASS_INVALID */
			conditionObj = new CIFast_IFast_ifastcbo_err_ams_fund_class_invalid();
			break;
		case 1700215: /* ERR_AMS_FUND_CLASS_NOT_VALID_FOR_FOF */
			conditionObj = new CIFast_IFast_ifastcbo_err_ams_fund_class_not_valid_for_fof();
			break;
		case 1700216: /* ERR_AMS_GLOBAL_ROUNDING_FUND_CLASS_NOT_IN_AMS_MIX */
			conditionObj = new CIFast_IFast_ifastcbo_err_ams_global_rounding_fund_class_not_in_ams_mix();
			break;
		case 1700217: /* ERR_AMS_GRAND_FATHER_DATED */
			conditionObj = new CIFast_IFast_ifastcbo_err_ams_grand_father_dated();
			break;
		case 1700218: /* ERR_AMS_MKT_REBALANCING_LIMITATION_RULE_NOT_MET */
			conditionObj = new CIFast_IFast_ifastcbo_err_ams_mkt_rebalancing_limitation_rule_not_met();
			break;
		case 1700219: /* ERR_AMS_REP_PROPOSED_DATE_MUST_BE_FUTURE_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_ams_rep_proposed_date_must_be_future_date();
			break;
		case 1700220: /* ERR_AMS_SETUP_FOR_PAC */
			conditionObj = new CIFast_IFast_ifastcbo_err_ams_setup_for_pac();
			break;
		case 1700221: /* ERR_AMS_SETUP_FOR_SWP */
			conditionObj = new CIFast_IFast_ifastcbo_err_ams_setup_for_swp();
			break;
		case 1700222: /* ERR_AMS_SETUP_NOT_ALLOWED_FOR_INSTITUTIONAL */
			conditionObj = new CIFast_IFast_ifastcbo_err_ams_setup_not_allowed_for_institutional();
			break;
		case 1700223: /* ERR_AMS_SETUP_NOT_ALLOWED_FOR_INSTITUTIONAL_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_ams_setup_not_allowed_for_institutional_account();
			break;
		case 1700224: /* ERR_AMS_SETUP_NOT_ALLOWED_IF_STOP_PURCH_REDEM */
			conditionObj = new CIFast_IFast_ifastcbo_err_ams_setup_not_allowed_if_stop_purch_redem();
			break;
		case 1700225: /* ERR_AMS_TYPE_INVALID */
			conditionObj = new CIFast_IFast_ifastcbo_err_ams_type_invalid();
			break;
		case 1700226: /* ERR_AMT_CAPPED_FUND_INCREASE */
			conditionObj = new CIFast_IFast_ifastcbo_err_amt_capped_fund_increase();
			break;
		case 1700227: /* ERR_AMT_MUST_BE_ZERO_ESCROW_REASON_LOAN */
			conditionObj = new CIFast_IFast_ifastcbo_err_amt_must_be_zero_escrow_reason_loan();
			break;
		case 1700228: /* ERR_AMT_PROTECT_FUND_INCREASE */
			conditionObj = new CIFast_IFast_ifastcbo_err_amt_protect_fund_increase();
			break;
		case 1700229: /* ERR_AMT_TYPE_CANNOT_SETTLE_CUR */
			conditionObj = new CIFast_IFast_ifastcbo_err_amt_type_cannot_settle_cur();
			break;
		case 1700230: /* ERR_AMT_TYPE_MUST_BE_AMOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_amt_type_must_be_amount();
			break;
		case 1700231: /* ERR_AMT_TYPE_MUST_BE_UNIT */
			conditionObj = new CIFast_IFast_ifastcbo_err_amt_type_must_be_unit();
			break;
		case 1700232: /* ERR_AMT_TYPE_NOTAPPLICABLE */
			conditionObj = new CIFast_IFast_ifastcbo_err_amt_type_notapplicable();
			break;
		case 1700233: /* ERR_AMTTYPE_APPL_TO_BEL_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_amttype_appl_to_bel_fund();
			break;
		case 1700234: /* ERR_ANNITANT_BIRTHDAY_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_annitant_birthday_not_found();
			break;
		case 1700235: /* ERR_ANNUAL_CONTRIB_LIMITS_NOT_SETUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_annual_contrib_limits_not_setup();
			break;
		case 1700236: /* ERR_ANNUITANT_ENTITY_IS_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_annuitant_entity_is_not_allowed();
			break;
		case 1700237: /* ERR_ANNUITANT_ENTITY_SHOULD_BE_SETUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_annuitant_entity_should_be_setup();
			break;
		case 1700238: /* ERR_ANNUITANT_INFORMATION_IS_NOT_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastcbo_err_annuitant_information_is_not_available();
			break;
		case 1700239: /* ERR_ANNUITANT_INVALID_FOR_ACCT_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_annuitant_invalid_for_acct_type();
			break;
		case 1700240: /* ERR_ANNUITANT_OLDER_THAN_69 */
			conditionObj = new CIFast_IFast_ifastcbo_err_annuitant_older_than_69();
			break;
		case 1700241: /* ERR_ANNUITANT_SIN_NOT_THE_SAME */
			conditionObj = new CIFast_IFast_ifastcbo_err_annuitant_sin_not_the_same();
			break;
		case 1700242: /* ERR_ANTI_DILUTION_LEVY_DEFAULT_RATE_DOES_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastcbo_err_anti_dilution_levy_default_rate_does_not_exist();
			break;
		case 1700243: /* ERR_AS_PENSION_ACCT */
			conditionObj = new CIFast_IFast_ifastcbo_err_as_pension_acct();
			break;
		case 1700244: /* ERR_AS_PENSION_ELIGIBLE */
			conditionObj = new CIFast_IFast_ifastcbo_err_as_pension_eligible();
			break;
		case 1700245: /* ERR_ASSIGNMENT_REDEEM_NOT_ALLOW */
			conditionObj = new CIFast_IFast_ifastcbo_err_assignment_redeem_not_allow();
			break;
		case 1700246: /* ERR_ASSIGNMENT_TRANSFER_NOT_ALLOW */
			conditionObj = new CIFast_IFast_ifastcbo_err_assignment_transfer_not_allow();
			break;
		case 1700247: /* ERR_ASSIGNNED_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_assignned_account();
			break;
		case 1700248: /* ERR_ASSISTED_CONTRIBUTION_AMOUNT_MORE_THAN_AVAILABLE_ASSISTED_AMOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_assisted_contribution_amount_more_than_available_assisted_amount();
			break;
		case 1700249: /* ERR_ASSISTED_CONTRIBUTION_AMOUNT_MORE_THAN_UNASSISTED_AMOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_assisted_contribution_amount_more_than_unassisted_amount();
			break;
		case 1700250: /* ERR_ASSOCIATED_ENTITY_NOT_PROVIDED */
			conditionObj = new CIFast_IFast_ifastcbo_err_associated_entity_not_provided();
			break;
		case 1700251: /* ERR_AT_ACCOUNT_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastcbo_err_at_account_not_exist();
			break;
		case 1700252: /* ERR_AT_AMOUNT_TRANSFER */
			conditionObj = new CIFast_IFast_ifastcbo_err_at_amount_transfer();
			break;
		case 1700253: /* ERR_AT_AMOUNT_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_at_amount_type();
			break;
		case 1700254: /* ERR_AT_COST_ALLOCATION_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_at_cost_allocation_not_allowed();
			break;
		case 1700255: /* ERR_AT_DEEMED_FULL */
			conditionObj = new CIFast_IFast_ifastcbo_err_at_deemed_full();
			break;
		case 1700256: /* ERR_AT_FOR_ESCROW_ACCT */
			conditionObj = new CIFast_IFast_ifastcbo_err_at_for_escrow_acct();
			break;
		case 1700257: /* ERR_AT_FROM_FUND_CLASS_TO_FUND_CLASS */
			conditionObj = new CIFast_IFast_ifastcbo_err_at_from_fund_class_to_fund_class();
			break;
		case 1700258: /* ERR_AT_FUNDCLASS_TRANSFER_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_at_fundclass_transfer_not_allowed();
			break;
		case 1700259: /* ERR_AT_FUNDTO_CLASSTO_ACOUNTTO_SAME_AS_FROM */
			conditionObj = new CIFast_IFast_ifastcbo_err_at_fundto_classto_acountto_same_as_from();
			break;
		case 1700260: /* ERR_AT_HAS_STOPPED_TRANSFER_IN */
			conditionObj = new CIFast_IFast_ifastcbo_err_at_has_stopped_transfer_in();
			break;
		case 1700261: /* ERR_AT_HAS_STOPPED_TRANSFER_OR_EXCH */
			conditionObj = new CIFast_IFast_ifastcbo_err_at_has_stopped_transfer_or_exch();
			break;
		case 1700262: /* ERR_AT_INVALID_ACCT_TAXTYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_at_invalid_acct_taxtype();
			break;
		case 1700263: /* ERR_AT_INVALID_ZERO_AMOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_at_invalid_zero_amount();
			break;
		case 1700264: /* ERR_AT_LEAST_ONE_DTABANKING_MUST_BE_SETUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_at_least_one_dtabanking_must_be_setup();
			break;
		case 1700265: /* ERR_AT_LEAST_ONE_MONTH_MUST_ACTIVE */
			conditionObj = new CIFast_IFast_ifastcbo_err_at_least_one_month_must_active();
			break;
		case 1700266: /* ERR_AT_LEAST_ONE_OBJECT_MUST_SETUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_at_least_one_object_must_setup();
			break;
		case 1700267: /* ERR_AT_LEAST_ONE_RECORD_FOR_SCALE */
			conditionObj = new CIFast_IFast_ifastcbo_err_at_least_one_record_for_scale();
			break;
		case 1700268: /* ERR_AV_UNIT_RATE_DOES_NOT_EXIST_FOR_FUND_ON_DEFF */
			conditionObj = new CIFast_IFast_ifastcbo_err_av_unit_rate_does_not_exist_for_fund_on_deff();
			break;
		case 1700269: /* ERR_AVAILABLE_PERCENT_FOR_PRIMARY_BENEF */
			conditionObj = new CIFast_IFast_ifastcbo_err_available_percent_for_primary_benef();
			break;
		case 1700270: /* ERR_BACK_DATE_TRADE_NOT_ALLOWED_BEFORE_LE */
			conditionObj = new CIFast_IFast_ifastcbo_err_back_date_trade_not_allowed_before_le();
			break;
		case 1700271: /* ERR_BACK_DATE_TRADE_NOT_ALLOWED_BEFORE_LWA */
			conditionObj = new CIFast_IFast_ifastcbo_err_back_date_trade_not_allowed_before_lwa();
			break;
		case 1700272: /* ERR_BACKDATE_TRADE_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_backdate_trade_not_allowed();
			break;
		case 1700273: /* ERR_BACKDATED_ENTITY_TAX_JURISDICTION_NOT_ALLOWED_FOR_RESP */
			conditionObj = new CIFast_IFast_ifastcbo_err_backdated_entity_tax_jurisdiction_not_allowed_for_resp();
			break;
		case 1700274: /* ERR_BACKDATED_NOT_ALLOWED_FOR_SEARCH_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_backdated_not_allowed_for_search_type();
			break;
		case 1700275: /* ERR_BACKDATEDREASON_FOR_BACKDATE_TRADE */
			conditionObj = new CIFast_IFast_ifastcbo_err_backdatedreason_for_backdate_trade();
			break;
		case 1700276: /* ERR_BALANCE_LESS_THEN_ENTERED_TRANS_AMOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_balance_less_then_entered_trans_amount();
			break;
		case 1700277: /* ERR_BALANCE_LESS_THEN_TRANS_AMOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_balance_less_then_trans_amount();
			break;
		case 1700278: /* ERR_BANK_ACCOUNT_SHOULD_MATCH_SYSTEMATIC_CURRECNCY */
			conditionObj = new CIFast_IFast_ifastcbo_err_bank_account_should_match_systematic_currecncy();
			break;
		case 1700279: /* ERR_BANK_ACCT_NUM_CANNOT_BE_BLANK */
			conditionObj = new CIFast_IFast_ifastcbo_err_bank_acct_num_cannot_be_blank();
			break;
		case 1700280: /* ERR_BANK_COUNTRY_CODE_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_bank_country_code_required();
			break;
		case 1700281: /* ERR_BANK_IN_USE */
			conditionObj = new CIFast_IFast_ifastcbo_err_bank_in_use();
			break;
		case 1700282: /* ERR_BANK_INSTRUCTIONS_NOT_EFFECTIVE */
			conditionObj = new CIFast_IFast_ifastcbo_err_bank_instructions_not_effective();
			break;
		case 1700283: /* ERR_BANK_INSTRUCTIONS_OVERLAP */
			conditionObj = new CIFast_IFast_ifastcbo_err_bank_instructions_overlap();
			break;
		case 1700284: /* ERR_BANK_INSTRUCTIONS_STOPPED */
			conditionObj = new CIFast_IFast_ifastcbo_err_bank_instructions_stopped();
			break;
		case 1700285: /* ERR_BANK_IS_USED */
			conditionObj = new CIFast_IFast_ifastcbo_err_bank_is_used();
			break;
		case 1700286: /* ERR_BANKACCTNUM_TOO_BIG */
			conditionObj = new CIFast_IFast_ifastcbo_err_bankacctnum_too_big();
			break;
		case 1700287: /* ERR_BANKINFO_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_bankinfo_required();
			break;
		case 1700288: /* ERR_BANKING_IDYPE_MANDATORY_FOR_PAC */
			conditionObj = new CIFast_IFast_ifastcbo_err_banking_idype_mandatory_for_pac();
			break;
		case 1700289: /* ERR_BATCH_BELONGS_TO_OTHERUSER */
			conditionObj = new CIFast_IFast_ifastcbo_err_batch_belongs_to_otheruser();
			break;
		case 1700290: /* ERR_BATCH_IS_CLOSED */
			conditionObj = new CIFast_IFast_ifastcbo_err_batch_is_closed();
			break;
		case 1700291: /* ERR_BENE_OVER_AGE_OF_15 */
			conditionObj = new CIFast_IFast_ifastcbo_err_bene_over_age_of_15();
			break;
		case 1700292: /* ERR_BENEF_ADDRESS_IS_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_benef_address_is_missing();
			break;
		case 1700293: /* ERR_BENEF_CURR_TAXYEAR_MANDATORY */
			conditionObj = new CIFast_IFast_ifastcbo_err_benef_curr_taxyear_mandatory();
			break;
		case 1700294: /* ERR_BENEF_NOT_ELIGIBLE_FOR_CLB */
			conditionObj = new CIFast_IFast_ifastcbo_err_benef_not_eligible_for_clb();
			break;
		case 1700295: /* ERR_BENEF_PERCENT_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_benef_percent_required();
			break;
		case 1700296: /* ERR_BENEF_SELECTED_DATE_BIRTH_NOT_ELIG_FOR_CLB */
			conditionObj = new CIFast_IFast_ifastcbo_err_benef_selected_date_birth_not_elig_for_clb();
			break;
		case 1700297: /* ERR_BENEF_WRONG_RELATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_benef_wrong_relate();
			break;
		case 1700298: /* ERR_BENEFICAL_OWNER_NAME_FOR_PROTECTED_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_benefical_owner_name_for_protected_fund();
			break;
		case 1700299: /* ERR_BENEFICIARY_ADDRESS_CODE_DOES_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastcbo_err_beneficiary_address_code_does_not_exist();
			break;
		case 1700300: /* ERR_BENEFICIARY_IS_NOT_LINKED_TO_PCG */
			conditionObj = new CIFast_IFast_ifastcbo_err_beneficiary_is_not_linked_to_pcg();
			break;
		case 1700301: /* ERR_BENEFICIARY_IS_OVER_18 */
			conditionObj = new CIFast_IFast_ifastcbo_err_beneficiary_is_over_18();
			break;
		case 1700302: /* ERR_BENEFICIARY_NOT_EFFECTIVE */
			conditionObj = new CIFast_IFast_ifastcbo_err_beneficiary_not_effective();
			break;
		case 1700303: /* ERR_BENEFICIARY_NOT_ELIGIBLE_FOR_QESI_INCREASE_NOT_SIBLINGONLY */
			conditionObj = new CIFast_IFast_ifastcbo_err_beneficiary_not_eligible_for_qesi_increase_not_siblingonly();
			break;
		case 1700304: /* ERR_BENEFICIARY_NOT_QUEBEC_RESIDENT */
			conditionObj = new CIFast_IFast_ifastcbo_err_beneficiary_not_quebec_resident();
			break;
		case 1700305: /* ERR_BENEFICIARY_NOT_SASKATCHEWAN_RESIDENT */
			conditionObj = new CIFast_IFast_ifastcbo_err_beneficiary_not_saskatchewan_resident();
			break;
		case 1700306: /* ERR_BEWAREOF_PENDINGTRADE */
			conditionObj = new CIFast_IFast_ifastcbo_err_bewareof_pendingtrade();
			break;
		case 1700307: /* ERR_BIRTHNAME_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_birthname_required();
			break;
		case 1700308: /* ERR_BLANK_CLASS */
			conditionObj = new CIFast_IFast_ifastcbo_err_blank_class();
			break;
		case 1700309: /* ERR_BLANK_CNTRY_OF_ISSUE */
			conditionObj = new CIFast_IFast_ifastcbo_err_blank_cntry_of_issue();
			break;
		case 1700310: /* ERR_BLANK_FREQENCY */
			conditionObj = new CIFast_IFast_ifastcbo_err_blank_freqency();
			break;
		case 1700311: /* ERR_BLANK_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_blank_fund();
			break;
		case 1700312: /* ERR_BLANK_FUNDCODE_FOR_INDICATIE_ALLOCATION */
			conditionObj = new CIFast_IFast_ifastcbo_err_blank_fundcode_for_indicatie_allocation();
			break;
		case 1700313: /* ERR_BLANK_REG_STANDARD */
			conditionObj = new CIFast_IFast_ifastcbo_err_blank_reg_standard();
			break;
		case 1700314: /* ERR_BRANCH_CODE_CAN_NOT_LONGER_THAN_6 */
			conditionObj = new CIFast_IFast_ifastcbo_err_branch_code_can_not_longer_than_6();
			break;
		case 1700315: /* ERR_BRANCH_CODE_HAS_TO_BE_5 */
			conditionObj = new CIFast_IFast_ifastcbo_err_branch_code_has_to_be_5();
			break;
		case 1700316: /* ERR_BRANCH_EMPTY */
			conditionObj = new CIFast_IFast_ifastcbo_err_branch_empty();
			break;
		case 1700317: /* ERR_BRANCH_FROM_TRANSFER_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_branch_from_transfer_not_allowed();
			break;
		case 1700318: /* ERR_BRANCH_INVALID_AS_OF_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_branch_invalid_as_of_date();
			break;
		case 1700319: /* ERR_BRANCH_MIN_ALLOWABLE_PURCHASE */
			conditionObj = new CIFast_IFast_ifastcbo_err_branch_min_allowable_purchase();
			break;
		case 1700320: /* ERR_BRANCH_MIN_BALANCE */
			conditionObj = new CIFast_IFast_ifastcbo_err_branch_min_balance();
			break;
		case 1700321: /* ERR_BRANCH_MIN_INIT_PURCHASE */
			conditionObj = new CIFast_IFast_ifastcbo_err_branch_min_init_purchase();
			break;
		case 1700322: /* ERR_BRANCH_NOT_EFFECTIVE */
			conditionObj = new CIFast_IFast_ifastcbo_err_branch_not_effective();
			break;
		case 1700323: /* ERR_BRANCH_PURCHASE_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_branch_purchase_not_allowed();
			break;
		case 1700324: /* ERR_BRANCH_REDEMPTION_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_branch_redemption_not_allowed();
			break;
		case 1700325: /* ERR_BRANCH_TO_TRANSFER_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_branch_to_transfer_not_allowed();
			break;
		case 1700326: /* ERR_BROKER_BLANK_SETTLEMENT_AMOUINT */
			conditionObj = new CIFast_IFast_ifastcbo_err_broker_blank_settlement_amouint();
			break;
		case 1700327: /* ERR_BROKER_BRANCH_CFG */
			conditionObj = new CIFast_IFast_ifastcbo_err_broker_branch_cfg();
			break;
		case 1700328: /* ERR_BROKER_CODE_CAN_NOT_LONGER_THAN_6 */
			conditionObj = new CIFast_IFast_ifastcbo_err_broker_code_can_not_longer_than_6();
			break;
		case 1700329: /* ERR_BROKER_CODE_HAS_TO_BE_5 */
			conditionObj = new CIFast_IFast_ifastcbo_err_broker_code_has_to_be_5();
			break;
		case 1700330: /* ERR_BROKER_DIFFERENT_THAN_ACCOUNT_BROKER */
			conditionObj = new CIFast_IFast_ifastcbo_err_broker_different_than_account_broker();
			break;
		case 1700331: /* ERR_BROKER_EMPTY */
			conditionObj = new CIFast_IFast_ifastcbo_err_broker_empty();
			break;
		case 1700332: /* ERR_BROKER_FROM_TRANSFER_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_broker_from_transfer_not_allowed();
			break;
		case 1700333: /* ERR_BROKER_INTERMEDIARY_ADDRESS_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_broker_intermediary_address_not_found();
			break;
		case 1700334: /* ERR_BROKER_INVALID_AS_OF_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_broker_invalid_as_of_date();
			break;
		case 1700335: /* ERR_BROKER_MIN_ALLOWABLE_PURCHASE */
			conditionObj = new CIFast_IFast_ifastcbo_err_broker_min_allowable_purchase();
			break;
		case 1700336: /* ERR_BROKER_MIN_BALANCE */
			conditionObj = new CIFast_IFast_ifastcbo_err_broker_min_balance();
			break;
		case 1700337: /* ERR_BROKER_MIN_INIT_PURCHASE */
			conditionObj = new CIFast_IFast_ifastcbo_err_broker_min_init_purchase();
			break;
		case 1700338: /* ERR_BROKER_NOT_EFFECTIVE */
			conditionObj = new CIFast_IFast_ifastcbo_err_broker_not_effective();
			break;
		case 1700339: /* ERR_BROKER_NOT_ELIGIBLE_FOR_ACCT */
			conditionObj = new CIFast_IFast_ifastcbo_err_broker_not_eligible_for_acct();
			break;
		case 1700340: /* ERR_BROKER_OR_SLSREP_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_broker_or_slsrep_not_found();
			break;
		case 1700341: /* ERR_BROKER_PAYMENT_FOR_SETUP_NOT_IN_PAIR */
			conditionObj = new CIFast_IFast_ifastcbo_err_broker_payment_for_setup_not_in_pair();
			break;
		case 1700342: /* ERR_BROKER_PAYMENT_INSTRUCTIONS_FOR_DISTRIBUTION_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_broker_payment_instructions_for_distribution_missing();
			break;
		case 1700343: /* ERR_BROKER_PAYMENT_INSTRUCTIONS_FOR_REDEMPTION_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_broker_payment_instructions_for_redemption_missing();
			break;
		case 1700344: /* ERR_BROKER_PURCHASE_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_broker_purchase_not_allowed();
			break;
		case 1700345: /* ERR_BROKER_REDEMPTION_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_broker_redemption_not_allowed();
			break;
		case 1700346: /* ERR_BROKER_STTL_AMOUNT_CANNOT_BE_ZERO */
			conditionObj = new CIFast_IFast_ifastcbo_err_broker_sttl_amount_cannot_be_zero();
			break;
		case 1700347: /* ERR_BROKER_TO_TRANSFER_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_broker_to_transfer_not_allowed();
			break;
		case 1700348: /* ERR_BUSINESS_DATE_ONLY */
			conditionObj = new CIFast_IFast_ifastcbo_err_business_date_only();
			break;
		case 1700349: /* ERR_CAN_TRANSFER_ONLY_TO_RRIF */
			conditionObj = new CIFast_IFast_ifastcbo_err_can_transfer_only_to_rrif();
			break;
		case 1700350: /* ERR_CAN_TRANSFER_ONLY_TO_RRSP_RRIF */
			conditionObj = new CIFast_IFast_ifastcbo_err_can_transfer_only_to_rrsp_rrif();
			break;
		case 1700351: /* ERR_CANADIAN_RESIDENT_WITHDRAW */
			conditionObj = new CIFast_IFast_ifastcbo_err_canadian_resident_withdraw();
			break;
		case 1700352: /* ERR_CANCEL_BATCH_MUST_BE_PREFIXED_SP_DC */
			conditionObj = new CIFast_IFast_ifastcbo_err_cancel_batch_must_be_prefixed_sp_dc();
			break;
		case 1700353: /* ERR_CANNOT_ADD_CANADIAN_JURIDICTION_TO_NR301 */
			conditionObj = new CIFast_IFast_ifastcbo_err_cannot_add_canadian_juridiction_to_nr301();
			break;
		case 1700354: /* ERR_CANNOT_ADD_NEW_ACCESS_ID */
			conditionObj = new CIFast_IFast_ifastcbo_err_cannot_add_new_access_id();
			break;
		case 1700355: /* ERR_CANNOT_ADD_NEW_CIF */
			conditionObj = new CIFast_IFast_ifastcbo_err_cannot_add_new_cif();
			break;
		case 1700356: /* ERR_CANNOT_CHANGE_CURRENT_YEAR */
			conditionObj = new CIFast_IFast_ifastcbo_err_cannot_change_current_year();
			break;
		case 1700357: /* ERR_CANNOT_CHANGE_TAX_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_cannot_change_tax_type();
			break;
		case 1700358: /* ERR_CANNOT_CHANGE_TAXTYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_cannot_change_taxtype();
			break;
		case 1700359: /* ERR_CANNOT_DELETE_FIXED_RECORD */
			conditionObj = new CIFast_IFast_ifastcbo_err_cannot_delete_fixed_record();
			break;
		case 1700360: /* ERR_CANNOT_EXCLUDE_ALL */
			conditionObj = new CIFast_IFast_ifastcbo_err_cannot_exclude_all();
			break;
		case 1700361: /* ERR_CANNOT_INCLUDE_PENDING_TRADES_FOR_ONLINE_REBALALANCING */
			conditionObj = new CIFast_IFast_ifastcbo_err_cannot_include_pending_trades_for_online_rebalalancing();
			break;
		case 1700362: /* ERR_CANNOT_MODIFY_ACCT_FEATURE */
			conditionObj = new CIFast_IFast_ifastcbo_err_cannot_modify_acct_feature();
			break;
		case 1700363: /* ERR_CANNOT_MODIFY_MARGIN */
			conditionObj = new CIFast_IFast_ifastcbo_err_cannot_modify_margin();
			break;
		case 1700364: /* ERR_CANNOT_RESTART_CAPPED_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_cannot_restart_capped_fund();
			break;
		case 1700365: /* ERR_CANNOT_SWITCH_FROM_RESTRICTED_TO_NON_RESTRICTED */
			conditionObj = new CIFast_IFast_ifastcbo_err_cannot_switch_from_restricted_to_non_restricted();
			break;
		case 1700366: /* ERR_CANNOT_SWITCH_TAXTYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_cannot_switch_taxtype();
			break;
		case 1700367: /* ERR_CANSIM_NOT_EXISTS */
			conditionObj = new CIFast_IFast_ifastcbo_err_cansim_not_exists();
			break;
		case 1700368: /* ERR_CAPPEDFUND_STATUSE */
			conditionObj = new CIFast_IFast_ifastcbo_err_cappedfund_statuse();
			break;
		case 1700369: /* ERR_CAPPEDFUND_STATUSW */
			conditionObj = new CIFast_IFast_ifastcbo_err_cappedfund_statusw();
			break;
		case 1700370: /* ERR_CASH_DISTRIB_NOT_ALLOWED_FOR_FROM_FUND_CLASS */
			conditionObj = new CIFast_IFast_ifastcbo_err_cash_distrib_not_allowed_for_from_fund_class();
			break;
		case 1700371: /* ERR_CASH_FUND_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_cash_fund_not_allowed();
			break;
		case 1700372: /* ERR_CASH_INSTR_NOT_ALLOWED_FOR_REG_ACC */
			conditionObj = new CIFast_IFast_ifastcbo_err_cash_instr_not_allowed_for_reg_acc();
			break;
		case 1700373: /* ERR_CASH_NONREG_TAXTYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_cash_nonreg_taxtype();
			break;
		case 1700374: /* ERR_CASH_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_cash_not_allowed();
			break;
		case 1700375: /* ERR_CASH_TRADE_NOT_ALLOWED_FOR_TAX_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_cash_trade_not_allowed_for_tax_type();
			break;
		case 1700376: /* ERR_CBO_HOLDING_ENTITY_CODE_ALREADY_EXISTS */
			conditionObj = new CIFast_IFast_ifastcbo_err_cbo_holding_entity_code_already_exists();
			break;
		case 1700377: /* ERR_CBO_WARNING_NOT_DEFINED */
			conditionObj = new CIFast_IFast_ifastcbo_err_cbo_warning_not_defined();
			break;
		case 1700378: /* ERR_CERT_NOT_FOR_FUND_CLASS */
			conditionObj = new CIFast_IFast_ifastcbo_err_cert_not_for_fund_class();
			break;
		case 1700379: /* ERR_CESG_AMOUNT_BE_RETURNED_BECAUSE_REDEMPTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_cesg_amount_be_returned_because_redemption();
			break;
		case 1700380: /* ERR_CESG_AMOUNT_MANDATORY */
			conditionObj = new CIFast_IFast_ifastcbo_err_cesg_amount_mandatory();
			break;
		case 1700381: /* ERR_CESG_LIMIT_EXCEEDED */
			conditionObj = new CIFast_IFast_ifastcbo_err_cesg_limit_exceeded();
			break;
		case 1700382: /* ERR_CHANGE_ALL_MARKET_MAILING */
			conditionObj = new CIFast_IFast_ifastcbo_err_change_all_market_mailing();
			break;
		case 1700383: /* ERR_CHANGE_REPS_IS_NOT_APPLICABLE */
			conditionObj = new CIFast_IFast_ifastcbo_err_change_reps_is_not_applicable();
			break;
		case 1700384: /* ERR_CHANGE_STATUS_TO_DEATH */
			conditionObj = new CIFast_IFast_ifastcbo_err_change_status_to_death();
			break;
		case 1700385: /* ERR_CHARGE_SHORT_TERM_TRANSFER_FEE_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_charge_short_term_transfer_fee_not_allowed();
			break;
		case 1700386: /* ERR_CLASS_CODE_MUST_BE_BLANK */
			conditionObj = new CIFast_IFast_ifastcbo_err_class_code_must_be_blank();
			break;
		case 1700387: /* ERR_CLB_AMOUNT_CANNOT_BE_TRANSFERED */
			conditionObj = new CIFast_IFast_ifastcbo_err_clb_amount_cannot_be_transfered();
			break;
		case 1700388: /* ERR_CLEARING_ID_MUST_BELONG_TO_CLEARING_ENTITY */
			conditionObj = new CIFast_IFast_ifastcbo_err_clearing_id_must_belong_to_clearing_entity();
			break;
		case 1700389: /* ERR_CLEARING_METHOD_NOT_ALLOWED_FOR_NON_CLEARING_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_clearing_method_not_allowed_for_non_clearing_account();
			break;
		case 1700390: /* ERR_CLEARING_METHOD_NOT_ALLOWED_FOR_NON_FUNDSETTLE_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_clearing_method_not_allowed_for_non_fundsettle_account();
			break;
		case 1700391: /* ERR_CLEARING_METHOD_NOT_ALLOWED_FOR_NON_VESTIMA_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_clearing_method_not_allowed_for_non_vestima_account();
			break;
		case 1700392: /* ERR_CLEARING_METHOD_NOT_ALLOWED_FOR_TRANSACTION_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_clearing_method_not_allowed_for_transaction_type();
			break;
		case 1700393: /* ERR_CLEARING_METHOD_REALIGNMENT_APPLICABLE_TO_FROM_AND_TO_CLEARING_ACCOUNTS */
			conditionObj = new CIFast_IFast_ifastcbo_err_clearing_method_realignment_applicable_to_from_and_to_clearing_accounts();
			break;
		case 1700394: /* ERR_CLEARING_PLATFORM_ID_TYPE_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_clearing_platform_id_type_required();
			break;
		case 1700395: /* ERR_CLEARING_PLATFORM_ID_VALUE_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_clearing_platform_id_value_required();
			break;
		case 1700396: /* ERR_CLEARING_PLATFORM_MUST_BE_CORPORATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_clearing_platform_must_be_corporate();
			break;
		case 1700397: /* ERR_CLEARINGFIRM_ALREADY_EQUAL_TO_BROKER */
			conditionObj = new CIFast_IFast_ifastcbo_err_clearingfirm_already_equal_to_broker();
			break;
		case 1700398: /* ERR_CLEARINGFIRM_IS_MANDATORY */
			conditionObj = new CIFast_IFast_ifastcbo_err_clearingfirm_is_mandatory();
			break;
		case 1700399: /* ERR_CLIENT_AGE_BEYOND_ALLOW */
			conditionObj = new CIFast_IFast_ifastcbo_err_client_age_beyond_allow();
			break;
		case 1700400: /* ERR_CLIENT_AGE_LESS_THAN_MINWITHAGE1 */
			conditionObj = new CIFast_IFast_ifastcbo_err_client_age_less_than_minwithage1();
			break;
		case 1700401: /* ERR_CLIENT_AGE_LESS_THAN_MINWITHAGE2 */
			conditionObj = new CIFast_IFast_ifastcbo_err_client_age_less_than_minwithage2();
			break;
		case 1700402: /* ERR_CLIENT_NON_REG_MARGIN_ACCT */
			conditionObj = new CIFast_IFast_ifastcbo_err_client_non_reg_margin_acct();
			break;
		case 1700403: /* ERR_CLIENT_RRSP_RRIF_LOAN_ACCT */
			conditionObj = new CIFast_IFast_ifastcbo_err_client_rrsp_rrif_loan_acct();
			break;
		case 1700404: /* ERR_CLIENTS_AGE_BEYOND */
			conditionObj = new CIFast_IFast_ifastcbo_err_clients_age_beyond();
			break;
		case 1700405: /* ERR_CLNT_MTH_STMT_FOR_ACCOUNT_BELONG_NISTMT */
			conditionObj = new CIFast_IFast_ifastcbo_err_clnt_mth_stmt_for_account_belong_nistmt();
			break;
		case 1700406: /* ERR_CLNT_MTH_STMT_FOR_CLIENT_HELD_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_clnt_mth_stmt_for_client_held_account();
			break;
		case 1700407: /* ERR_CLNT_MTH_STMT_NOT_FOR_SEG_ENV */
			conditionObj = new CIFast_IFast_ifastcbo_err_clnt_mth_stmt_not_for_seg_env();
			break;
		case 1700408: /* ERR_CLOSE_ACCT_MUST_BE_FULL_RED */
			conditionObj = new CIFast_IFast_ifastcbo_err_close_acct_must_be_full_red();
			break;
		case 1700409: /* ERR_CLOSED_COUNTRY_RESIDENT_FOR_MONEY_IN */
			conditionObj = new CIFast_IFast_ifastcbo_err_closed_country_resident_for_money_in();
			break;
		case 1700410: /* ERR_CLOSING_VALUE_ZERO */
			conditionObj = new CIFast_IFast_ifastcbo_err_closing_value_zero();
			break;
		case 1700411: /* ERR_CMD_AFTER_LCMD */
			conditionObj = new CIFast_IFast_ifastcbo_err_cmd_after_lcmd();
			break;
		case 1700412: /* ERR_CMD_LATER_THAN_LEGAL_MATURITY_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_cmd_later_than_legal_maturity_date();
			break;
		case 1700413: /* ERR_CNTRY_OF_ISSUE_IS_BLANK */
			conditionObj = new CIFast_IFast_ifastcbo_err_cntry_of_issue_is_blank();
			break;
		case 1700414: /* ERR_COMM_GROUP_CODE_OVERLAPED */
			conditionObj = new CIFast_IFast_ifastcbo_err_comm_group_code_overlaped();
			break;
		case 1700415: /* ERR_COMM_RATE_GREATER_THEN_100 */
			conditionObj = new CIFast_IFast_ifastcbo_err_comm_rate_greater_then_100();
			break;
		case 1700416: /* ERR_COMM_RATE_LESS_THEN_ZERO */
			conditionObj = new CIFast_IFast_ifastcbo_err_comm_rate_less_then_zero();
			break;
		case 1700417: /* ERR_COMMGROUP_FUND_CLASS_CAN_NOT_COEXIST */
			conditionObj = new CIFast_IFast_ifastcbo_err_commgroup_fund_class_can_not_coexist();
			break;
		case 1700418: /* ERR_COMMISSION_IS_NOT_NEGOTIABLE */
			conditionObj = new CIFast_IFast_ifastcbo_err_commission_is_not_negotiable();
			break;
		case 1700419: /* ERR_COMMISSION_REBATE_NOT_ALLOWED_FOR_THIS_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_commission_rebate_not_allowed_for_this_fund();
			break;
		case 1700420: /* ERR_COMMITMENT_PRODUCT_NOT_ACTIVE */
			conditionObj = new CIFast_IFast_ifastcbo_err_commitment_product_not_active();
			break;
		case 1700421: /* ERR_COMPENSATION_AGENT_MUST_BE_CHANGED */
			conditionObj = new CIFast_IFast_ifastcbo_err_compensation_agent_must_be_changed();
			break;
		case 1700422: /* ERR_CONDITION_RATE_NOT_SETUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_condition_rate_not_setup();
			break;
		case 1700423: /* ERR_CONFIRM_TYPE_ONLY_VALID_FOR_SWIFT */
			conditionObj = new CIFast_IFast_ifastcbo_err_confirm_type_only_valid_for_swift();
			break;
		case 1700424: /* ERR_CONFLICTING_RECORD_ALREADY_EXISTS */
			conditionObj = new CIFast_IFast_ifastcbo_err_conflicting_record_already_exists();
			break;
		case 1700425: /* ERR_CONSOL_NOT_VALID */
			conditionObj = new CIFast_IFast_ifastcbo_err_consol_not_valid();
			break;
		case 1700426: /* ERR_CONSOL_NOT_VALID_FOR_DISTRIBUTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_consol_not_valid_for_distribution();
			break;
		case 1700427: /* ERR_CONTACT_PERSON_LASTNAME_CANNOT_BE_BLANK */
			conditionObj = new CIFast_IFast_ifastcbo_err_contact_person_lastname_cannot_be_blank();
			break;
		case 1700428: /* ERR_CONTR_MAT_DATE_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_contr_mat_date_missing();
			break;
		case 1700429: /* ERR_CONTR_MATURITY_RED_100_PERCENT */
			conditionObj = new CIFast_IFast_ifastcbo_err_contr_maturity_red_100_percent();
			break;
		case 1700430: /* ERR_CONTRACT_ACCT_STATUS_INACTIVE */
			conditionObj = new CIFast_IFast_ifastcbo_err_contract_acct_status_inactive();
			break;
		case 1700431: /* ERR_CONTRACT_EFF_DATE_AFTER_ISSUE_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_contract_eff_date_after_issue_date();
			break;
		case 1700432: /* ERR_CONTRACT_MUST_BE_CREATED */
			conditionObj = new CIFast_IFast_ifastcbo_err_contract_must_be_created();
			break;
		case 1700433: /* ERR_CONTRACT_NOT_EFFECTIVE */
			conditionObj = new CIFast_IFast_ifastcbo_err_contract_not_effective();
			break;
		case 1700434: /* ERR_CONTRACT_STATUS */
			conditionObj = new CIFast_IFast_ifastcbo_err_contract_status();
			break;
		case 1700435: /* ERR_CONTRACT_TYPE_AND_VERSION_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_contract_type_and_version_required();
			break;
		case 1700436: /* ERR_CONTRACT_TYPE_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_contract_type_not_found();
			break;
		case 1700437: /* ERR_CONTRIBUTION_NOT_ALLOWED_FOR_NON_RESIDENT */
			conditionObj = new CIFast_IFast_ifastcbo_err_contribution_not_allowed_for_non_resident();
			break;
		case 1700438: /* ERR_CONTROLX_RECORD_NOT_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastcbo_err_controlx_record_not_available();
			break;
		case 1700440: /* ERR_CORR_BANK_FIELDS_SHOUD_BE_ENTERED */
			conditionObj = new CIFast_IFast_ifastcbo_err_corr_bank_fields_shoud_be_entered();
			break;
		case 1700441: /* ERR_CORR_BANK_SHOULD_BE_EMPTY */
			conditionObj = new CIFast_IFast_ifastcbo_err_corr_bank_should_be_empty();
			break;
		case 1700442: /* ERR_COUNTRY_IS_BLANK */
			conditionObj = new CIFast_IFast_ifastcbo_err_country_is_blank();
			break;
		case 1700443: /* ERR_COUNTRY_OF_ISSUE_IS_REQUIRED_FOR_BUSINESS_NUMBER_AND_TRUST_NUMBER */
			conditionObj = new CIFast_IFast_ifastcbo_err_country_of_issue_is_required_for_business_number_and_trust_number();
			break;
		case 1700444: /* ERR_COURSE_LEN_BETWEEN_1_AND_52_WEEKS */
			conditionObj = new CIFast_IFast_ifastcbo_err_course_len_between_1_and_52_weeks();
			break;
		case 1700445: /* ERR_COURSE_START_DATE_MANDATORY */
			conditionObj = new CIFast_IFast_ifastcbo_err_course_start_date_mandatory();
			break;
		case 1700446: /* ERR_CRITERIA_ALL_SELECTED */
			conditionObj = new CIFast_IFast_ifastcbo_err_criteria_all_selected();
			break;
		case 1700447: /* ERR_CRITERIA_EXCEED_LIMIT */
			conditionObj = new CIFast_IFast_ifastcbo_err_criteria_exceed_limit();
			break;
		case 1700448: /* ERR_CRITERIA_LIMIT_EXCEEDED */
			conditionObj = new CIFast_IFast_ifastcbo_err_criteria_limit_exceeded();
			break;
		case 1700449: /* ERR_CURRENCY_DOES_NOT_MATCH */
			conditionObj = new CIFast_IFast_ifastcbo_err_currency_does_not_match();
			break;
		case 1700450: /* ERR_CURRENCY_MISMATCH */
			conditionObj = new CIFast_IFast_ifastcbo_err_currency_mismatch();
			break;
		case 1700451: /* ERR_CURRENCY_NOT_FOR_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_currency_not_for_fund();
			break;
		case 1700452: /* ERR_CURRENCY_SHOULD_BE_SAME */
			conditionObj = new CIFast_IFast_ifastcbo_err_currency_should_be_same();
			break;
		case 1700453: /* ERR_CURRENT_DATE_SUBSCRIBED_UNITS_INCLUDED */
			conditionObj = new CIFast_IFast_ifastcbo_err_current_date_subscribed_units_included();
			break;
		case 1700454: /* ERR_CURRENT_FUND_BALANCES */
			conditionObj = new CIFast_IFast_ifastcbo_err_current_fund_balances();
			break;
		case 1700455: /* ERR_CUSTODY_TRADING_CANNOT_COEXIST */
			conditionObj = new CIFast_IFast_ifastcbo_err_custody_trading_cannot_coexist();
			break;
		case 1700456: /* ERR_CUT_OFF_TIME_DUPLICATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_cut_off_time_duplicate();
			break;
		case 1700457: /* ERR_CYCLE_CALCULATED_DATE_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_cycle_calculated_date_not_allowed();
			break;
		case 1700458: /* ERR_DATE_CANNOT_BE_EARLIER_THAN_ACCOUNT_EFFECTIVE */
			conditionObj = new CIFast_IFast_ifastcbo_err_date_cannot_be_earlier_than_account_effective();
			break;
		case 1700459: /* ERR_DATE_CANNOT_BE_FUTURE */
			conditionObj = new CIFast_IFast_ifastcbo_err_date_cannot_be_future();
			break;
		case 1700460: /* ERR_DATE_CANNOT_EARLIER_THAN_CURRENT_BUSINESS_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_date_cannot_earlier_than_current_business_date();
			break;
		case 1700461: /* ERR_DATE_CANNOT_GREATER_THAN_LAST_REB_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_date_cannot_greater_than_last_reb_date();
			break;
		case 1700462: /* ERR_DATE_EARLIER_THAN_CURRENT_BUS_DAY */
			conditionObj = new CIFast_IFast_ifastcbo_err_date_earlier_than_current_bus_day();
			break;
		case 1700463: /* ERR_DATE_FUNCTIONS */
			conditionObj = new CIFast_IFast_ifastcbo_err_date_functions();
			break;
		case 1700464: /* ERR_DATE_MUST_BE_BUSINESS_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_date_must_be_business_date();
			break;
		case 1700465: /* ERR_DATE_MUST_BE_EQUAL_OR_EARLIER_THAN_2ND_DIPLOMA_COMM_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_date_must_be_equal_or_earlier_than_2nd_diploma_comm_date();
			break;
		case 1700466: /* ERR_DATE_MUST_BE_EQUAL_OR_GREATER_THAN_CURR_DATE_PLUS_3_BUSS_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_date_must_be_equal_or_greater_than_curr_date_plus_3_buss_date();
			break;
		case 1700467: /* ERR_DATE_NOT_LAST_BUSINESS_DAY_OF_WEEK */
			conditionObj = new CIFast_IFast_ifastcbo_err_date_not_last_business_day_of_week();
			break;
		case 1700468: /* ERR_DATE_NUST_BEFORE_CURRBUSDATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_date_nust_before_currbusdate();
			break;
		case 1700469: /* ERR_DATE_OF_BIRTH_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_date_of_birth_required();
			break;
		case 1700470: /* ERR_DATE_OF_REGISTRATION */
			conditionObj = new CIFast_IFast_ifastcbo_err_date_of_registration();
			break;
		case 1700471: /* ERR_DATE_RANGE_OVERLAP */
			conditionObj = new CIFast_IFast_ifastcbo_err_date_range_overlap();
			break;
		case 1700472: /* ERR_DAYOFWEEK_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_dayofweek_required();
			break;
		case 1700473: /* ERR_DAYS_BASIS_EMPTY */
			conditionObj = new CIFast_IFast_ifastcbo_err_days_basis_empty();
			break;
		case 1700474: /* ERR_DAYS_OF_MONTH_INVALID */
			conditionObj = new CIFast_IFast_ifastcbo_err_days_of_month_invalid();
			break;
		case 1700475: /* ERR_DEALER_INFO_MISSING_FOR_BROKER */
			conditionObj = new CIFast_IFast_ifastcbo_err_dealer_info_missing_for_broker();
			break;
		case 1700476: /* ERR_DEALER_NOT_ELIGIBLE_FOR_FUND_CLASS */
			conditionObj = new CIFast_IFast_ifastcbo_err_dealer_not_eligible_for_fund_class();
			break;
		case 1700477: /* ERR_DEATH_CLAIM_REDEMPTION_CODE */
			conditionObj = new CIFast_IFast_ifastcbo_err_death_claim_redemption_code();
			break;
		case 1700478: /* ERR_DEATH_DATE_EXIST_FOR_ACCTHOLDER */
			conditionObj = new CIFast_IFast_ifastcbo_err_death_date_exist_for_acctholder();
			break;
		case 1700479: /* ERR_DEATH_NOTIF_BEFORE_DEATH_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_death_notif_before_death_date();
			break;
		case 1700480: /* ERR_DEATH_NOTIF_NO_DEATH_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_death_notif_no_death_date();
			break;
		case 1700481: /* ERR_DEATH_SETTLEMENT_STAMPED */
			conditionObj = new CIFast_IFast_ifastcbo_err_death_settlement_stamped();
			break;
		case 1700482: /* ERR_DEATHCLAIM_DOC_BLANK */
			conditionObj = new CIFast_IFast_ifastcbo_err_deathclaim_doc_blank();
			break;
		case 1700483: /* ERR_DEFAULT_FUND_BRKR_REQUIRED_FOR_TRADE */
			conditionObj = new CIFast_IFast_ifastcbo_err_default_fund_brkr_required_for_trade();
			break;
		case 1700484: /* ERR_DEFF_CANNOT_LESS_THAN_INIT_DEFF */
			conditionObj = new CIFast_IFast_ifastcbo_err_deff_cannot_less_than_init_deff();
			break;
		case 1700485: /* ERR_DEFF_STOP_DATE_RANGE_EXISTS */
			conditionObj = new CIFast_IFast_ifastcbo_err_deff_stop_date_range_exists();
			break;
		case 1700486: /* ERR_DEFF_UNTIL_CANNOT_BE_LESS_THAN_TODAY */
			conditionObj = new CIFast_IFast_ifastcbo_err_deff_until_cannot_be_less_than_today();
			break;
		case 1700487: /* ERR_DEL_HIST_TXFR_BENEF_RECORD */
			conditionObj = new CIFast_IFast_ifastcbo_err_del_hist_txfr_benef_record();
			break;
		case 1700488: /* ERR_DELETE_ENTITY */
			conditionObj = new CIFast_IFast_ifastcbo_err_delete_entity();
			break;
		case 1700489: /* ERR_DELETE_FEE_PARAMETER */
			conditionObj = new CIFast_IFast_ifastcbo_err_delete_fee_parameter();
			break;
		case 1700490: /* ERR_DELETE_FUNDSPONSOR_FEE_MODEL */
			conditionObj = new CIFast_IFast_ifastcbo_err_delete_fundsponsor_fee_model();
			break;
		case 1700491: /* ERR_DELETE_PRIVATE_ACCOUNT_CATEGORY */
			conditionObj = new CIFast_IFast_ifastcbo_err_delete_private_account_category();
			break;
		case 1700492: /* ERR_DELETE_RESP_ENTITY */
			conditionObj = new CIFast_IFast_ifastcbo_err_delete_resp_entity();
			break;
		case 1700493: /* ERR_DELETE_SCALE_FEE */
			conditionObj = new CIFast_IFast_ifastcbo_err_delete_scale_fee();
			break;
		case 1700494: /* ERR_DELINK_PCG_WITH_RESP_BENEF_HAS_GRANT */
			conditionObj = new CIFast_IFast_ifastcbo_err_delink_pcg_with_resp_benef_has_grant();
			break;
		case 1700495: /* ERR_DENOMINATOR_IS_ZERO */
			conditionObj = new CIFast_IFast_ifastcbo_err_denominator_is_zero();
			break;
		case 1700496: /* ERR_DEPOSIT_CODE_IS_APPLICABLE_FOR_SIBLING_ONLY_ACCOUNTS */
			conditionObj = new CIFast_IFast_ifastcbo_err_deposit_code_is_applicable_for_sibling_only_accounts();
			break;
		case 1700497: /* ERR_DEPOSIT_DATE_AFFECT_MIN_MAX_AMT */
			conditionObj = new CIFast_IFast_ifastcbo_err_deposit_date_affect_min_max_amt();
			break;
		case 1700498: /* ERR_DEPOSIT_ID_CLOSED */
			conditionObj = new CIFast_IFast_ifastcbo_err_deposit_id_closed();
			break;
		case 1700499: /* ERR_DEPOSIT_ID_INVALID */
			conditionObj = new CIFast_IFast_ifastcbo_err_deposit_id_invalid();
			break;
		case 1700500: /* ERR_DEPOSIT_TYPE_07_MUST_BEUSED_RIF */
			conditionObj = new CIFast_IFast_ifastcbo_err_deposit_type_07_must_beused_rif();
			break;
		case 1700501: /* ERR_DEPOSIT_TYPE_23_NOT_SUPPORT */
			conditionObj = new CIFast_IFast_ifastcbo_err_deposit_type_23_not_support();
			break;
		case 1700502: /* ERR_DEPOSIT_TYPE_24_NOT_SUPPORTED */
			conditionObj = new CIFast_IFast_ifastcbo_err_deposit_type_24_not_supported();
			break;
		case 1700503: /* ERR_DEPOSIT_TYPE_40_CANNOT_BE_PLACED */
			conditionObj = new CIFast_IFast_ifastcbo_err_deposit_type_40_cannot_be_placed();
			break;
		case 1700504: /* ERR_DEPOSIT_TYPE_INVALID_FOR_TAXTYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_deposit_type_invalid_for_taxtype();
			break;
		case 1700505: /* ERR_DEPOSIT_TYPE_MUST_BE_06_OR_07 */
			conditionObj = new CIFast_IFast_ifastcbo_err_deposit_type_must_be_06_or_07();
			break;
		case 1700506: /* ERR_DEPOSIT_TYPE_NOT_ALLOWED_FOR_REDCODE */
			conditionObj = new CIFast_IFast_ifastcbo_err_deposit_type_not_allowed_for_redcode();
			break;
		case 1700507: /* ERR_DEPOSITS_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_deposits_not_allowed();
			break;
		case 1700508: /* ERR_DEPTYPE_REDCODE_CAN_NOT_BE_USED_WITH_CURR_YEAR */
			conditionObj = new CIFast_IFast_ifastcbo_err_deptype_redcode_can_not_be_used_with_curr_year();
			break;
		case 1700509: /* ERR_DEPTYPE_REDCODE_CAN_ONLY_BE_USED_FOR_RESP_TO_RESP_TX */
			conditionObj = new CIFast_IFast_ifastcbo_err_deptype_redcode_can_only_be_used_for_resp_to_resp_tx();
			break;
		case 1700510: /* ERR_DEPTYPE_REDCODE_NOT_ALLOWED_IN_RESP_TO_RESP_TRANSFER */
			conditionObj = new CIFast_IFast_ifastcbo_err_deptype_redcode_not_allowed_in_resp_to_resp_transfer();
			break;
		case 1700511: /* ERR_DEPTYPE_REDCODE_NOT_ALLOWED_IN_TRANSFER */
			conditionObj = new CIFast_IFast_ifastcbo_err_deptype_redcode_not_allowed_in_transfer();
			break;
		case 1700512: /* ERR_DEPTYPE_REDCODE_NOT_ALLOWED_NON_QESI_ENV */
			conditionObj = new CIFast_IFast_ifastcbo_err_deptype_redcode_not_allowed_non_qesi_env();
			break;
		case 1700513: /* ERR_DESIGNATION_INSTITUTION_HAS_NOT_BEEN_SETUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_designation_institution_has_not_been_setup();
			break;
		case 1700514: /* ERR_DIFFERENT_ACCOUNTABLE_THAN_CANCELLATION_NOT_THROUGH_FUNDSERV */
			conditionObj = new CIFast_IFast_ifastcbo_err_different_accountable_than_cancellation_not_through_fundserv();
			break;
		case 1700515: /* ERR_DIFFERENT_REG_AGENT */
			conditionObj = new CIFast_IFast_ifastcbo_err_different_reg_agent();
			break;
		case 1700516: /* ERR_DIFFERENT_SIBLINGONLY_STATUS */
			conditionObj = new CIFast_IFast_ifastcbo_err_different_siblingonly_status();
			break;
		case 1700517: /* ERR_DIFFERNT_SETTLESOURCE_THAN_CANCELLATION */
			conditionObj = new CIFast_IFast_ifastcbo_err_differnt_settlesource_than_cancellation();
			break;
		case 1700518: /* ERR_DILUTION_ALLOC_AT_LEAST_ONE_RECORD_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_dilution_alloc_at_least_one_record_required();
			break;
		case 1700519: /* ERR_DILUTION_ALLOC_ONLY_ONE_SPLIT_FACTOR_MANDATORY */
			conditionObj = new CIFast_IFast_ifastcbo_err_dilution_alloc_only_one_split_factor_mandatory();
			break;
		case 1700520: /* ERR_DILUTION_ALLOC_PERCENTAGE_MUST_BE_ZERO */
			conditionObj = new CIFast_IFast_ifastcbo_err_dilution_alloc_percentage_must_be_zero();
			break;
		case 1700521: /* ERR_DILUTION_ALLOC_PERCENTAGE_SPLIT_METHOD */
			conditionObj = new CIFast_IFast_ifastcbo_err_dilution_alloc_percentage_split_method();
			break;
		case 1700522: /* ERR_DILUTION_ALLOC_RESP_DATE_MUST_BE_BETWEEN_TRADE_AND_SETTLEMENT_DATES */
			conditionObj = new CIFast_IFast_ifastcbo_err_dilution_alloc_resp_date_must_be_between_trade_and_settlement_dates();
			break;
		case 1700523: /* ERR_DILUTION_ALLOC_RESP_DATE_SPLIT_METHOD */
			conditionObj = new CIFast_IFast_ifastcbo_err_dilution_alloc_resp_date_split_method();
			break;
		case 1700524: /* ERR_DILUTION_ALLOC_SAME_RESP_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_dilution_alloc_same_resp_date();
			break;
		case 1700525: /* ERR_DILUTION_ALLOC_SPLIT_FACTOR_MANDATORY */
			conditionObj = new CIFast_IFast_ifastcbo_err_dilution_alloc_split_factor_mandatory();
			break;
		case 1700526: /* ERR_DIRCT_DEPT_PAYTYPE_FOR_CLNT_NON_REGIS_ONLY */
			conditionObj = new CIFast_IFast_ifastcbo_err_dirct_dept_paytype_for_clnt_non_regis_only();
			break;
		case 1700527: /* ERR_DIRCT_DEPT_PAYTYPE_FOR_DIRCT_DEPT_BANK_ONLY */
			conditionObj = new CIFast_IFast_ifastcbo_err_dirct_dept_paytype_for_dirct_dept_bank_only();
			break;
		case 1700528: /* ERR_DIRECT_DEPOSIT_BANK_INVESTOR_AUTHORIZE_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_direct_deposit_bank_investor_authorize_missing();
			break;
		case 1700529: /* ERR_DIRECT_DEPOSIT_BNK_INFO_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_direct_deposit_bnk_info_missing();
			break;
		case 1700530: /* ERR_DIRECT_DEPST_BANK_FOR_CAN_BANK_ONLY */
			conditionObj = new CIFast_IFast_ifastcbo_err_direct_depst_bank_for_can_bank_only();
			break;
		case 1700531: /* ERR_DIRECT_DEPST_BANK_FOR_CAN_CUR_BANK_ACCT_ONLY */
			conditionObj = new CIFast_IFast_ifastcbo_err_direct_depst_bank_for_can_cur_bank_acct_only();
			break;
		case 1700532: /* ERR_DIRECT_DEPST_BANK_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_direct_depst_bank_required();
			break;
		case 1700533: /* ERR_DIRECT_DEPST_FOR_CAN_CUR_ONLY */
			conditionObj = new CIFast_IFast_ifastcbo_err_direct_depst_for_can_cur_only();
			break;
		case 1700534: /* ERR_DIRECT_DEPST_SHRHLDR_ONLY */
			conditionObj = new CIFast_IFast_ifastcbo_err_direct_depst_shrhldr_only();
			break;
		case 1700535: /* ERR_DIRECT_DPST_BANK_BEFORE_ACCT_EFFDATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_direct_dpst_bank_before_acct_effdate();
			break;
		case 1700536: /* ERR_DISPOSITION_NOT_UPDATABLE_FOR_ACCT_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_disposition_not_updatable_for_acct_type();
			break;
		case 1700537: /* ERR_DISTRIB_MIX_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_distrib_mix_not_allowed();
			break;
		case 1700538: /* ERR_DIV_TYPE_IS_NOT_AVAIL_FOR_FUNDCLASS */
			conditionObj = new CIFast_IFast_ifastcbo_err_div_type_is_not_avail_for_fundclass();
			break;
		case 1700539: /* ERR_DM_EVENT_HAS_OCCURED */
			conditionObj = new CIFast_IFast_ifastcbo_err_dm_event_has_occured();
			break;
		case 1700540: /* ERR_DMD_LATER_THAN_LEGAL_MATURITY_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_dmd_later_than_legal_maturity_date();
			break;
		case 1700541: /* ERR_DOB_RESP_BENEF_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_dob_resp_benef_required();
			break;
		case 1700542: /* ERR_DOC_STATUS_BLANK */
			conditionObj = new CIFast_IFast_ifastcbo_err_doc_status_blank();
			break;
		case 1700543: /* ERR_DOCUMENT_DATE_RECEIVED_MANDATORY */
			conditionObj = new CIFast_IFast_ifastcbo_err_document_date_received_mandatory();
			break;
		case 1700544: /* ERR_DOCUMENT_OVERLAPPED */
			conditionObj = new CIFast_IFast_ifastcbo_err_document_overlapped();
			break;
		case 1700545: /* ERR_DOD_ENTITY_TYPE_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_dod_entity_type_missing();
			break;
		case 1700546: /* ERR_DOMESTIC_FUND_ONLY */
			conditionObj = new CIFast_IFast_ifastcbo_err_domestic_fund_only();
			break;
		case 1700547: /* ERR_DTA_NOT_ALLOWED_FOR_THIS_DEPOSITTYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_dta_not_allowed_for_this_deposittype();
			break;
		case 1700548: /* ERR_DTA_NOT_ALLOWED_FOR_THIS_REDCODE */
			conditionObj = new CIFast_IFast_ifastcbo_err_dta_not_allowed_for_this_redcode();
			break;
		case 1700549: /* ERR_DUP_RESET_INSTR */
			conditionObj = new CIFast_IFast_ifastcbo_err_dup_reset_instr();
			break;
		case 1700550: /* ERR_DUPLICATE_ADDRESS_CODE */
			conditionObj = new CIFast_IFast_ifastcbo_err_duplicate_address_code();
			break;
		case 1700551: /* ERR_DUPLICATE_AMSCODE */
			conditionObj = new CIFast_IFast_ifastcbo_err_duplicate_amscode();
			break;
		case 1700552: /* ERR_DUPLICATE_BICCODE */
			conditionObj = new CIFast_IFast_ifastcbo_err_duplicate_biccode();
			break;
		case 1700553: /* ERR_DUPLICATE_CLEARING_PLATFORM_ID_FOR_ENTITY */
			conditionObj = new CIFast_IFast_ifastcbo_err_duplicate_clearing_platform_id_for_entity();
			break;
		case 1700554: /* ERR_DUPLICATE_CRITERIA_VALUE */
			conditionObj = new CIFast_IFast_ifastcbo_err_duplicate_criteria_value();
			break;
		case 1700555: /* ERR_DUPLICATE_EFT_PURCHASE_CURRENCY */
			conditionObj = new CIFast_IFast_ifastcbo_err_duplicate_eft_purchase_currency();
			break;
		case 1700556: /* ERR_DUPLICATE_EFT_REDEMPTION_CURRENCY */
			conditionObj = new CIFast_IFast_ifastcbo_err_duplicate_eft_redemption_currency();
			break;
		case 1700557: /* ERR_DUPLICATE_FUND_CLASS */
			conditionObj = new CIFast_IFast_ifastcbo_err_duplicate_fund_class();
			break;
		case 1700558: /* ERR_DUPLICATE_HURDLE_ENTRY */
			conditionObj = new CIFast_IFast_ifastcbo_err_duplicate_hurdle_entry();
			break;
		case 1700559: /* ERR_DUPLICATE_LOAN_NUM */
			conditionObj = new CIFast_IFast_ifastcbo_err_duplicate_loan_num();
			break;
		case 1700560: /* ERR_DUPLICATE_LOAN_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_duplicate_loan_type();
			break;
		case 1700561: /* ERR_DUPLICATE_MKT_INDEX_CODE */
			conditionObj = new CIFast_IFast_ifastcbo_err_duplicate_mkt_index_code();
			break;
		case 1700562: /* ERR_DUPLICATE_MKT_INDEX_ENTRY */
			conditionObj = new CIFast_IFast_ifastcbo_err_duplicate_mkt_index_entry();
			break;
		case 1700563: /* ERR_DUPLICATE_NEQ */
			conditionObj = new CIFast_IFast_ifastcbo_err_duplicate_neq();
			break;
		case 1700564: /* ERR_DUPLICATE_PARENT_FUND_CLASS_WITH_ANOTHER_ACTIVE_AMS_MODEL */
			conditionObj = new CIFast_IFast_ifastcbo_err_duplicate_parent_fund_class_with_another_active_ams_model();
			break;
		case 1700565: /* ERR_DUPLICATE_RECORD */
			conditionObj = new CIFast_IFast_ifastcbo_err_duplicate_record();
			break;
		case 1700566: /* ERR_DUPLICATE_RECORD_SETTLEMENT_INSTR */
			conditionObj = new CIFast_IFast_ifastcbo_err_duplicate_record_settlement_instr();
			break;
		case 1700567: /* ERR_DUPLICATE_SAVING_PLAN */
			conditionObj = new CIFast_IFast_ifastcbo_err_duplicate_saving_plan();
			break;
		case 1700568: /* ERR_DUPLICATE_SETTLE_LOCATION */
			conditionObj = new CIFast_IFast_ifastcbo_err_duplicate_settle_location();
			break;
		case 1700569: /* ERR_DUPLICATE_SIN */
			conditionObj = new CIFast_IFast_ifastcbo_err_duplicate_sin();
			break;
		case 1700570: /* ERR_DUPLICATE_SIN_DIFFERENT_ENTITY */
			conditionObj = new CIFast_IFast_ifastcbo_err_duplicate_sin_different_entity();
			break;
		case 1700571: /* ERR_DUPLICATE_SYSTEMATIC */
			conditionObj = new CIFast_IFast_ifastcbo_err_duplicate_systematic();
			break;
		case 1700572: /* ERR_DUPLICATE_TRADE */
			conditionObj = new CIFast_IFast_ifastcbo_err_duplicate_trade();
			break;
		case 1700573: /* ERR_DUPLICATE_TYPE_FOR_FAMILY_CODE */
			conditionObj = new CIFast_IFast_ifastcbo_err_duplicate_type_for_family_code();
			break;
		case 1700574: /* ERR_Duplicate_WhereUse */
			conditionObj = new CIFast_IFast_ifastcbo_err_duplicate_whereuse();
			break;
		case 1700575: /* ERR_DUPLICATED_ENTITY_MAIL */
			conditionObj = new CIFast_IFast_ifastcbo_err_duplicated_entity_mail();
			break;
		case 1700576: /* ERR_E_ENTITY_AGE_OVER_69 */
			conditionObj = new CIFast_IFast_ifastcbo_err_e_entity_age_over_69();
			break;
		case 1700577: /* ERR_E_ID_VALUE_IS_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_e_id_value_is_missing();
			break;
		case 1700578: /* ERR_E_INVALID_ID_VALUE */
			conditionObj = new CIFast_IFast_ifastcbo_err_e_invalid_id_value();
			break;
		case 1700579: /* ERR_E_INVALID_SIN */
			conditionObj = new CIFast_IFast_ifastcbo_err_e_invalid_sin();
			break;
		case 1700580: /* ERR_E_SIN_IS_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_e_sin_is_missing();
			break;
		case 1700581: /* ERR_EAP_AMOUNT_EXCEEDS_MARKET_VALUE */
			conditionObj = new CIFast_IFast_ifastcbo_err_eap_amount_exceeds_market_value();
			break;
		case 1700582: /* ERR_EAP_REDEMPT_EXCEEDED_EARNING */
			conditionObj = new CIFast_IFast_ifastcbo_err_eap_redempt_exceeded_earning();
			break;
		case 1700583: /* ERR_EARLY_DEATH_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_early_death_date();
			break;
		case 1700584: /* ERR_EARLY_ENDDATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_early_enddate();
			break;
		case 1700585: /* ERR_EARLY_TERMINATION */
			conditionObj = new CIFast_IFast_ifastcbo_err_early_termination();
			break;
		case 1700586: /* ERR_EDUCATION_INST_POST_CODE_AND_COUNTRY_NAME_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_education_inst_post_code_and_country_name_required();
			break;
		case 1700587: /* ERR_EF */
			conditionObj = new CIFast_IFast_ifastcbo_err_ef();
			break;
		case 1700588: /* ERR_EFF_DATE_LATE_THAN_STOP_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_eff_date_late_than_stop_date();
			break;
		case 1700589: /* ERR_EFF_STOP_DATE_RANGE_OVERLAP */
			conditionObj = new CIFast_IFast_ifastcbo_err_eff_stop_date_range_overlap();
			break;
		case 1700590: /* ERR_EFFDATE_AFTER_STOP_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_effdate_after_stop_date();
			break;
		case 1700591: /* ERR_EFFECTIVE_DATE_BACKWARD */
			conditionObj = new CIFast_IFast_ifastcbo_err_effective_date_backward();
			break;
		case 1700592: /* ERR_EFFECTIVE_DATE_BEFORE_CURBUSDATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_effective_date_before_curbusdate();
			break;
		case 1700593: /* ERR_EFFECTIVE_DATE_CONTRACT_EARLIER_THAN_EFFECTIVE_DATE_MFACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_effective_date_contract_earlier_than_effective_date_mfaccount();
			break;
		case 1700594: /* ERR_EFFECTIVE_DATE_FORWARD */
			conditionObj = new CIFast_IFast_ifastcbo_err_effective_date_forward();
			break;
		case 1700595: /* ERR_EFFECTIVE_DATE_LATE_THAN_STOP_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_effective_date_late_than_stop_date();
			break;
		case 1700596: /* ERR_EFFECTIVE_DATE_MUST_BE_ENTERED */
			conditionObj = new CIFast_IFast_ifastcbo_err_effective_date_must_be_entered();
			break;
		case 1700597: /* ERR_EFFECTIVE_DATE_MUST_LATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_effective_date_must_late();
			break;
		case 1700598: /* ERR_EFFECTIVEDATE_MUST_BE_EARLIER_STOPDATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_effectivedate_must_be_earlier_stopdate();
			break;
		case 1700599: /* ERR_EFT_FULL_REDEMPTION_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_eft_full_redemption_not_allowed();
			break;
		case 1700600: /* ERR_EFT_IN_UNITS_NOT_FOR_PURCHASE */
			conditionObj = new CIFast_IFast_ifastcbo_err_eft_in_units_not_for_purchase();
			break;
		case 1700601: /* ERR_EFT_TO_CHQ_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_eft_to_chq_not_allowed();
			break;
		case 1700602: /* ERR_EITHER_CUSTODY_TRADING_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_either_custody_trading_required();
			break;
		case 1700603: /* ERR_ELECTION_LWA_AGE_RATE_ALLOWED_ONLY_LWA_RATES_ARE_THE_SAME */
			conditionObj = new CIFast_IFast_ifastcbo_err_election_lwa_age_rate_allowed_only_lwa_rates_are_the_same();
			break;
		case 1700604: /* ERR_EMAIL_ALREADY_EXIST */
			conditionObj = new CIFast_IFast_ifastcbo_err_email_already_exist();
			break;
		case 1700605: /* ERR_EMPLOYEE_AGENT_BONUS_PURCHASE_ONLY_APPLICABLE_FOR_EMPLOY_AGENT */
			conditionObj = new CIFast_IFast_ifastcbo_err_employee_agent_bonus_purchase_only_applicable_for_employ_agent();
			break;
		case 1700606: /* ERR_EMPLOYEE_AGENT_BONUS_PURCHASE_ONLY_APPLICABLE_FOR_SEG_FUNDS */
			conditionObj = new CIFast_IFast_ifastcbo_err_employee_agent_bonus_purchase_only_applicable_for_seg_funds();
			break;
		case 1700607: /* ERR_EMPLOYEE_AGENT_NOT_ALLOW_FOR_BALANCE_ACCT */
			conditionObj = new CIFast_IFast_ifastcbo_err_employee_agent_not_allow_for_balance_acct();
			break;
		case 1700608: /* ERR_EMPLOYEE_AGENT_ONLY_APPICABLE_FOR_CLIENT_ACCT */
			conditionObj = new CIFast_IFast_ifastcbo_err_employee_agent_only_appicable_for_client_acct();
			break;
		case 1700609: /* ERR_EMPLOYEE_LOCKED_IN_AT_GROUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_employee_locked_in_at_group();
			break;
		case 1700610: /* ERR_EMPLOYER_EMPLOYEE_LOCKED_IN_AT_GROUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_employer_employee_locked_in_at_group();
			break;
		case 1700611: /* ERR_EMPLOYER_ENTITY_MUST_BE_SETUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_employer_entity_must_be_setup();
			break;
		case 1700612: /* ERR_EMPLOYER_LOCKED_IN_AT_GROUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_employer_locked_in_at_group();
			break;
		case 1700613: /* ERR_EMPTY_CLIENT_ID */
			conditionObj = new CIFast_IFast_ifastcbo_err_empty_client_id();
			break;
		case 1700614: /* ERR_EMPTY_FUNDCLASS */
			conditionObj = new CIFast_IFast_ifastcbo_err_empty_fundclass();
			break;
		case 1700615: /* ERR_END_DATE_EARLIER_THAN_ALL_FUND_DIV_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_end_date_earlier_than_all_fund_div_date();
			break;
		case 1700616: /* ERR_END_DATE_LESS_THAN_STOP_DATE_OF_PACSWP */
			conditionObj = new CIFast_IFast_ifastcbo_err_end_date_less_than_stop_date_of_pacswp();
			break;
		case 1700617: /* ERR_ENDDATE_MATURITY_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_enddate_maturity_date();
			break;
		case 1700618: /* ERR_ENITITY_NOT_ALLOWED_FOR_NON_RESP */
			conditionObj = new CIFast_IFast_ifastcbo_err_enitity_not_allowed_for_non_resp();
			break;
		case 1700619: /* ERR_ENITITY_NOT_ALLOWED_FOR_RESP_SIBLING_NOT_YES */
			conditionObj = new CIFast_IFast_ifastcbo_err_enitity_not_allowed_for_resp_sibling_not_yes();
			break;
		case 1700620: /* ERR_ENTER_TO_ACCT_ALL_FUND_TRANS */
			conditionObj = new CIFast_IFast_ifastcbo_err_enter_to_acct_all_fund_trans();
			break;
		case 1700621: /* ERR_ENTERED_ID_NOT_UNIQUE */
			conditionObj = new CIFast_IFast_ifastcbo_err_entered_id_not_unique();
			break;
		case 1700622: /* ERR_ENTIRE_ACCT_ASSIGNED */
			conditionObj = new CIFast_IFast_ifastcbo_err_entire_acct_assigned();
			break;
		case 1700623: /* ERR_ENTITY_ADDRESS_CODE_CANNOT_BE_BLANK */
			conditionObj = new CIFast_IFast_ifastcbo_err_entity_address_code_cannot_be_blank();
			break;
		case 1700624: /* ERR_ENTITY_ADDRESS_ID_INVALID */
			conditionObj = new CIFast_IFast_ifastcbo_err_entity_address_id_invalid();
			break;
		case 1700625: /* ERR_ENTITY_ADDRESS_IS_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_entity_address_is_missing();
			break;
		case 1700626: /* ERR_ENTITY_BEING_LINKED_TO_OTHER_RESP_BENEF */
			conditionObj = new CIFast_IFast_ifastcbo_err_entity_being_linked_to_other_resp_benef();
			break;
		case 1700627: /* ERR_ENTITY_CANNOT_BE_USED_WITH_REDEMPTION_CODE */
			conditionObj = new CIFast_IFast_ifastcbo_err_entity_cannot_be_used_with_redemption_code();
			break;
		case 1700628: /* ERR_ENTITY_CATEGORY_IS_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_entity_category_is_required();
			break;
		case 1700629: /* ERR_ENTITY_DONT_MATCH_FOR_IN_KIND_TRANS */
			conditionObj = new CIFast_IFast_ifastcbo_err_entity_dont_match_for_in_kind_trans();
			break;
		case 1700630: /* ERR_ENTITY_LASTNAME_CANNOT_BE_BLANK */
			conditionObj = new CIFast_IFast_ifastcbo_err_entity_lastname_cannot_be_blank();
			break;
		case 1700631: /* ERR_ENTITY_MAY_USED_BY_OTHER_PLACES */
			conditionObj = new CIFast_IFast_ifastcbo_err_entity_may_used_by_other_places();
			break;
		case 1700632: /* ERR_ENTITY_NATIONALITY_BLANK */
			conditionObj = new CIFast_IFast_ifastcbo_err_entity_nationality_blank();
			break;
		case 1700633: /* ERR_ENTITY_TYPE_ASSIGNEE_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_entity_type_assignee_not_allowed();
			break;
		case 1700634: /* ERR_ENTITY_TYPE_EMPTY */
			conditionObj = new CIFast_IFast_ifastcbo_err_entity_type_empty();
			break;
		case 1700635: /* ERR_ENTITY_TYPE_ESCROW_NOT_PERMIT */
			conditionObj = new CIFast_IFast_ifastcbo_err_entity_type_escrow_not_permit();
			break;
		case 1700636: /* ERR_ENTRY_BOTH_FIELDS */
			conditionObj = new CIFast_IFast_ifastcbo_err_entry_both_fields();
			break;
		case 1700637: /* ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE */
			conditionObj = new CIFast_IFast_ifastcbo_err_entry_empty_or_contains_only_space();
			break;
		case 1700638: /* ERR_ERISA_PROHIBITED_FUND_CANNOT_BE_TRADED_IN_ERISA_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_erisa_prohibited_fund_cannot_be_traded_in_erisa_account();
			break;
		case 1700639: /* ERR_ESCROW_ACCT_ASSIGNMENT */
			conditionObj = new CIFast_IFast_ifastcbo_err_escrow_acct_assignment();
			break;
		case 1700640: /* ERR_ESCROW_AMOUNT_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_escrow_amount_type();
			break;
		case 1700641: /* ERR_ESCROW_EFECTIVE_DATE_LESS_THAN_CURRENT_BUSSINES_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_escrow_efective_date_less_than_current_bussines_date();
			break;
		case 1700642: /* ERR_ESCROW_ENTITY_SETUP_FOR_NON_ESCROW */
			conditionObj = new CIFast_IFast_ifastcbo_err_escrow_entity_setup_for_non_escrow();
			break;
		case 1700643: /* ERR_ESCROW_FUND_CLASS_BLANK */
			conditionObj = new CIFast_IFast_ifastcbo_err_escrow_fund_class_blank();
			break;
		case 1700644: /* ERR_ESCROW_LOCKED_ALL_UNITS */
			conditionObj = new CIFast_IFast_ifastcbo_err_escrow_locked_all_units();
			break;
		case 1700645: /* ERR_ESCROW_LOCKED_PARTIAL_UNITS */
			conditionObj = new CIFast_IFast_ifastcbo_err_escrow_locked_partial_units();
			break;
		case 1700646: /* ERR_ESCROW_REP_SHOULD_BE_DELETED */
			conditionObj = new CIFast_IFast_ifastcbo_err_escrow_rep_should_be_deleted();
			break;
		case 1700647: /* ERR_ESCROW_REPREZENTATIVE_ENTITY_MUST_BE_SETUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_escrow_reprezentative_entity_must_be_setup();
			break;
		case 1700648: /* ERR_ESCROWFUND_CLASS */
			conditionObj = new CIFast_IFast_ifastcbo_err_escrowfund_class();
			break;
		case 1700649: /* ERR_ESCROWFUND_ENTITY_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_escrowfund_entity_type();
			break;
		case 1700650: /* ERR_ESOP_INTERRUPT_DATE_BLANK */
			conditionObj = new CIFast_IFast_ifastcbo_err_esop_interrupt_date_blank();
			break;
		case 1700651: /* ERR_ESOP_INTERRUPT_DATE_INVALID */
			conditionObj = new CIFast_IFast_ifastcbo_err_esop_interrupt_date_invalid();
			break;
		case 1700652: /* ERR_ESTATE_ALLOCATION_REQUIRED_FOR_DEATH_REDEMPTIONS */
			conditionObj = new CIFast_IFast_ifastcbo_err_estate_allocation_required_for_death_redemptions();
			break;
		case 1700653: /* ERR_EVENT_RECIEPT_DATE_AND_TIME_EMPTY */
			conditionObj = new CIFast_IFast_ifastcbo_err_event_reciept_date_and_time_empty();
			break;
		case 1700654: /* ERR_EX_AMT_MORE_THAN_HOLDING */
			conditionObj = new CIFast_IFast_ifastcbo_err_ex_amt_more_than_holding();
			break;
		case 1700655: /* ERR_EXACTLY_TWO_RIFF_DAYS_OF_MONTH_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_exactly_two_riff_days_of_month_required();
			break;
		case 1700656: /* ERR_EXCH_IN_FEE_OVER_MAXIMUM */
			conditionObj = new CIFast_IFast_ifastcbo_err_exch_in_fee_over_maximum();
			break;
		case 1700657: /* ERR_EXCH_IN_FEE_UNDER_MINIMUM */
			conditionObj = new CIFast_IFast_ifastcbo_err_exch_in_fee_under_minimum();
			break;
		case 1700658: /* ERR_EXCH_RATE_MUST_BE_NUMERIC */
			conditionObj = new CIFast_IFast_ifastcbo_err_exch_rate_must_be_numeric();
			break;
		case 1700659: /* ERR_EXCHANGE_DIFFERENT_AS_FUND_ACCT */
			conditionObj = new CIFast_IFast_ifastcbo_err_exchange_different_as_fund_acct();
			break;
		case 1700660: /* ERR_EXCHANGE_DIFFERENT_AS_NON_AS_FUND_ACCT */
			conditionObj = new CIFast_IFast_ifastcbo_err_exchange_different_as_non_as_fund_acct();
			break;
		case 1700661: /* ERR_EXCHANGE_OUT_FEE_OVER_MAXIMUM */
			conditionObj = new CIFast_IFast_ifastcbo_err_exchange_out_fee_over_maximum();
			break;
		case 1700662: /* ERR_EXCHANGE_OUT_FEE_UNDER_MINIMUM */
			conditionObj = new CIFast_IFast_ifastcbo_err_exchange_out_fee_under_minimum();
			break;
		case 1700663: /* ERR_EXCLUDE_IS_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_exclude_is_not_allowed();
			break;
		case 1700664: /* ERR_EXEMPT_HOLDING_EXCESS */
			conditionObj = new CIFast_IFast_ifastcbo_err_exempt_holding_excess();
			break;
		case 1700665: /* ERR_EXEMPT_SCOPE_NOT_VALID_FOR_TAX_JURISDICTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_exempt_scope_not_valid_for_tax_jurisdiction();
			break;
		case 1700666: /* ERR_EXEMPT_TYPE_NOT_VALID_FOR_ACCOUNT_TYPE_AND_DESIGNATION */
			conditionObj = new CIFast_IFast_ifastcbo_err_exempt_type_not_valid_for_account_type_and_designation();
			break;
		case 1700667: /* ERR_EXEMPT_TYPE_NOT_VALID_FOR_TAX_JURISDICTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_exempt_type_not_valid_for_tax_jurisdiction();
			break;
		case 1700668: /* ERR_EXPIRY_DATE_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_expiry_date_required();
			break;
		case 1700669: /* ERR_FEDERAL_JURISDICTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_federal_jurisdiction();
			break;
		case 1700670: /* ERR_FEDERAL_NOT_VALID_TAX */
			conditionObj = new CIFast_IFast_ifastcbo_err_federal_not_valid_tax();
			break;
		case 1700671: /* ERR_FEDERAL_QUALIFIED_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_federal_qualified_not_allowed();
			break;
		case 1700672: /* ERR_FEE_CANNOT_BE_OVERRIDDEN */
			conditionObj = new CIFast_IFast_ifastcbo_err_fee_cannot_be_overridden();
			break;
		case 1700673: /* ERR_FEE_CODE_COEXIST_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_fee_code_coexist_not_allowed();
			break;
		case 1700674: /* ERR_FEE_CODE_NOT_DEFINED_UNABLE_STORE_DEDUCTION_FEE */
			conditionObj = new CIFast_IFast_ifastcbo_err_fee_code_not_defined_unable_store_deduction_fee();
			break;
		case 1700675: /* ERR_FEE_CODE_OVERLAPED */
			conditionObj = new CIFast_IFast_ifastcbo_err_fee_code_overlaped();
			break;
		case 1700676: /* ERR_FEE_DIFFER_FROM_DEFAULT */
			conditionObj = new CIFast_IFast_ifastcbo_err_fee_differ_from_default();
			break;
		case 1700677: /* ERR_FEE_LESS_OR_EQUAL_100 */
			conditionObj = new CIFast_IFast_ifastcbo_err_fee_less_or_equal_100();
			break;
		case 1700678: /* ERR_FEE_LESS_THAN_MIN_RESP_GRANT */
			conditionObj = new CIFast_IFast_ifastcbo_err_fee_less_than_min_resp_grant();
			break;
		case 1700679: /* ERR_FEE_MODEL_ALREADY_IN_USE */
			conditionObj = new CIFast_IFast_ifastcbo_err_fee_model_already_in_use();
			break;
		case 1700680: /* ERR_FEE_MODEL_CODE_IN_USE */
			conditionObj = new CIFast_IFast_ifastcbo_err_fee_model_code_in_use();
			break;
		case 1700681: /* ERR_FEE_MODEL_CODE_MUST_BELONG_TO_A_VALID_COMM_GROUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_fee_model_code_must_belong_to_a_valid_comm_group();
			break;
		case 1700682: /* ERR_FEE_MODEL_CODE_MUST_BELONG_TO_A_VALID_COMM_GROUP_OR_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_fee_model_code_must_belong_to_a_valid_comm_group_or_fund();
			break;
		case 1700683: /* ERR_FEE_MODEL_DEFF_NOT_APPLIC_TO_ACCT_ASSOC */
			conditionObj = new CIFast_IFast_ifastcbo_err_fee_model_deff_not_applic_to_acct_assoc();
			break;
		case 1700684: /* ERR_FEE_MODEL_FUNDSPONSOR_ALREADY_IN_SYSTEM */
			conditionObj = new CIFast_IFast_ifastcbo_err_fee_model_fundsponsor_already_in_system();
			break;
		case 1700685: /* ERR_FEE_MODEL_STOP_DATE_NOT_APPLIC_TO_ACCT_ASSOC */
			conditionObj = new CIFast_IFast_ifastcbo_err_fee_model_stop_date_not_applic_to_acct_assoc();
			break;
		case 1700686: /* ERR_FEE_MORE_THAN_MAX */
			conditionObj = new CIFast_IFast_ifastcbo_err_fee_more_than_max();
			break;
		case 1700687: /* ERR_FEE_MORE_THAN_MAX_RESP_GRANT */
			conditionObj = new CIFast_IFast_ifastcbo_err_fee_more_than_max_resp_grant();
			break;
		case 1700688: /* ERR_FEE_MORE_THAN_MIN */
			conditionObj = new CIFast_IFast_ifastcbo_err_fee_more_than_min();
			break;
		case 1700689: /* ERR_FEE_MUST_BE_NUMERIC */
			conditionObj = new CIFast_IFast_ifastcbo_err_fee_must_be_numeric();
			break;
		case 1700690: /* ERR_FEE_MUST_BE_ZERO_OR_GREATER */
			conditionObj = new CIFast_IFast_ifastcbo_err_fee_must_be_zero_or_greater();
			break;
		case 1700691: /* ERR_FEE_MUST_LESS_OR_EQUAL_THAN_MAXIMUM_FEE */
			conditionObj = new CIFast_IFast_ifastcbo_err_fee_must_less_or_equal_than_maximum_fee();
			break;
		case 1700692: /* ERR_FEE_OPTION_DOSE_NOT_APPLY */
			conditionObj = new CIFast_IFast_ifastcbo_err_fee_option_dose_not_apply();
			break;
		case 1700693: /* ERR_FEE_PARAMETER_NOT_SETUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_fee_parameter_not_setup();
			break;
		case 1700694: /* ERR_FEE_PERCENT_INVALID */
			conditionObj = new CIFast_IFast_ifastcbo_err_fee_percent_invalid();
			break;
		case 1700695: /* ERR_FEE_RATE_ABOVE_100_PERCENT */
			conditionObj = new CIFast_IFast_ifastcbo_err_fee_rate_above_100_percent();
			break;
		case 1700696: /* ERR_FEE_RATE_ABOVE_MAX */
			conditionObj = new CIFast_IFast_ifastcbo_err_fee_rate_above_max();
			break;
		case 1700697: /* ERR_FEE_RATE_UNDER_0_PERCENT */
			conditionObj = new CIFast_IFast_ifastcbo_err_fee_rate_under_0_percent();
			break;
		case 1700698: /* ERR_FEE_RATE_UNDER_MINIMUM */
			conditionObj = new CIFast_IFast_ifastcbo_err_fee_rate_under_minimum();
			break;
		case 1700699: /* ERR_FEE_SET_UP_IS_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_fee_set_up_is_not_allowed();
			break;
		case 1700700: /* ERR_FEE_TYPE_FLAT_FOR_BEARER_CERTIFICATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_fee_type_flat_for_bearer_certificate();
			break;
		case 1700701: /* ERR_FEE_TYPE_SCALE_NOT_SUPPORTED */
			conditionObj = new CIFast_IFast_ifastcbo_err_fee_type_scale_not_supported();
			break;
		case 1700702: /* ERR_FEE_TYPE_SCALE_ONLY */
			conditionObj = new CIFast_IFast_ifastcbo_err_fee_type_scale_only();
			break;
		case 1700703: /* ERR_FEE_TYPE_TIER_NOT_SUPPORTED */
			conditionObj = new CIFast_IFast_ifastcbo_err_fee_type_tier_not_supported();
			break;
		case 1700704: /* ERR_FEECODE_CANNOT_COEXIT */
			conditionObj = new CIFast_IFast_ifastcbo_err_feecode_cannot_coexit();
			break;
		case 1700705: /* ERR_FEECODE_NOT_APPLY_TO_MODELOPTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_feecode_not_apply_to_modeloption();
			break;
		case 1700706: /* ERR_FEEMODEL_CODE_NOT_ACTIVE */
			conditionObj = new CIFast_IFast_ifastcbo_err_feemodel_code_not_active();
			break;
		case 1700707: /* ERR_FEEMODEL_CODE_NOT_SETUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_feemodel_code_not_setup();
			break;
		case 1700708: /* ERR_FEETYPE_NOT_SUPPORTED */
			conditionObj = new CIFast_IFast_ifastcbo_err_feetype_not_supported();
			break;
		case 1700709: /* ERR_FIELD_INACTIVE_AS_OF_TRADE_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_field_inactive_as_of_trade_date();
			break;
		case 1700710: /* ERR_FIELD_INVALID_F4_FOR_SEARCH */
			conditionObj = new CIFast_IFast_ifastcbo_err_field_invalid_f4_for_search();
			break;
		case 1700711: /* ERR_FIELD_INVALID_F4_FOR_SELECTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_field_invalid_f4_for_selection();
			break;
		case 1700712: /* ERR_FIELD_IS_BLANK */
			conditionObj = new CIFast_IFast_ifastcbo_err_field_is_blank();
			break;
		case 1700713: /* ERR_FIELD_MANDATORY_F4_FOR_SEARCH */
			conditionObj = new CIFast_IFast_ifastcbo_err_field_mandatory_f4_for_search();
			break;
		case 1700714: /* ERR_FIELD_MANDATORY_F4_FOR_SELECTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_field_mandatory_f4_for_selection();
			break;
		case 1700715: /* ERR_FIELD_REQUIRED_PLS_ENTER */
			conditionObj = new CIFast_IFast_ifastcbo_err_field_required_pls_enter();
			break;
		case 1700716: /* ERR_FIELD_REQUIRED_PLS_SELECT */
			conditionObj = new CIFast_IFast_ifastcbo_err_field_required_pls_select();
			break;
		case 1700717: /* ERR_FIELD_VAL_CANNOT_BE_ZERO */
			conditionObj = new CIFast_IFast_ifastcbo_err_field_val_cannot_be_zero();
			break;
		case 1700718: /* ERR_FIELD_VAL_REQUIRED_PLS_ENTER */
			conditionObj = new CIFast_IFast_ifastcbo_err_field_val_required_pls_enter();
			break;
		case 1700719: /* ERR_FIELD_VAL_REQUIRED_PLS_SELECT */
			conditionObj = new CIFast_IFast_ifastcbo_err_field_val_required_pls_select();
			break;
		case 1700720: /* ERR_FIELDS_MUST_BE_UNIQUE */
			conditionObj = new CIFast_IFast_ifastcbo_err_fields_must_be_unique();
			break;
		case 1700721: /* ERR_FIRST_DTA_TRADE_MUST_BE_PURCHASE */
			conditionObj = new CIFast_IFast_ifastcbo_err_first_dta_trade_must_be_purchase();
			break;
		case 1700722: /* ERR_FIRST_TRADE_MUST_BE_TRANSFER */
			conditionObj = new CIFast_IFast_ifastcbo_err_first_trade_must_be_transfer();
			break;
		case 1700723: /* ERR_FLAT_PERCENT_MUST_BE_YES */
			conditionObj = new CIFast_IFast_ifastcbo_err_flat_percent_must_be_yes();
			break;
		case 1700724: /* ERR_FLATPECENT_MUST_BE_FLAT */
			conditionObj = new CIFast_IFast_ifastcbo_err_flatpecent_must_be_flat();
			break;
		case 1700725: /* ERR_FLATPERCENT_MUST_BE_YES */
			conditionObj = new CIFast_IFast_ifastcbo_err_flatpercent_must_be_yes();
			break;
		case 1700726: /* ERR_FOREIGN_CAP_GAIN_ALLOC_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_foreign_cap_gain_alloc_not_allowed();
			break;
		case 1700727: /* ERR_FOREIGN_FUND_CLASS_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_foreign_fund_class_required();
			break;
		case 1700728: /* ERR_FR_TO_CLEARING_METHOD_NOT_SAME_AND_NOT_RLG */
			conditionObj = new CIFast_IFast_ifastcbo_err_fr_to_clearing_method_not_same_and_not_rlg();
			break;
		case 1700729: /* ERR_FRACTIONAL_VALUES_NOT_ALLOWED_IN_CURRENCY */
			conditionObj = new CIFast_IFast_ifastcbo_err_fractional_values_not_allowed_in_currency();
			break;
		case 1700730: /* ERR_FREQ_DIFF_FROM_DEF */
			conditionObj = new CIFast_IFast_ifastcbo_err_freq_diff_from_def();
			break;
		case 1700731: /* ERR_FROM_AFC_MATCH_TO_AFC */
			conditionObj = new CIFast_IFast_ifastcbo_err_from_afc_match_to_afc();
			break;
		case 1700732: /* ERR_FROM_BENEF_IS_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_from_benef_is_missing();
			break;
		case 1700733: /* ERR_FROM_CLEARING_METHOD_REALIGNMENT_ONLY_FOR_SAME_FROM_TO_CLASS */
			conditionObj = new CIFast_IFast_ifastcbo_err_from_clearing_method_realignment_only_for_same_from_to_class();
			break;
		case 1700734: /* ERR_FROM_CLEARING_METHOD_REALIGNMENT_ONLY_FOR_SAME_FROM_TO_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_from_clearing_method_realignment_only_for_same_from_to_fund();
			break;
		case 1700735: /* ERR_FROM_DATE_FUTURE_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_from_date_future_date();
			break;
		case 1700736: /* ERR_FROM_DELIVERY_TO_MUST_BE_SUPPLIED_FOR_CLEARING_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_from_delivery_to_must_be_supplied_for_clearing_account();
			break;
		case 1700737: /* ERR_FROM_TO_CLASSES_NOT_BELONG_TO_SAME_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_from_to_classes_not_belong_to_same_fund();
			break;
		case 1700738: /* ERR_FROM_TO_CURRENCIES_DO_NOT_MATCH */
			conditionObj = new CIFast_IFast_ifastcbo_err_from_to_currencies_do_not_match();
			break;
		case 1700739: /* ERR_FROMDATE_BEFORE_ACCT_EFFECTIVE_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_fromdate_before_acct_effective_date();
			break;
		case 1700740: /* ERR_FROMDATE_BEFORE_ACCT_INCEPTION_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_fromdate_before_acct_inception_date();
			break;
		case 1700741: /* ERR_FROMFUND_TOFUND_MUST_BE_BLANK_FOR_ALLFUND_TRANSFER */
			conditionObj = new CIFast_IFast_ifastcbo_err_fromfund_tofund_must_be_blank_for_allfund_transfer();
			break;
		case 1700742: /* ERR_FULL_EXCHANGE_INDICATED */
			conditionObj = new CIFast_IFast_ifastcbo_err_full_exchange_indicated();
			break;
		case 1700743: /* ERR_FULL_PARTIAL_EXEMPTION_SCOPE_EXIST_ACCT_FUND_CLASS */
			conditionObj = new CIFast_IFast_ifastcbo_err_full_partial_exemption_scope_exist_acct_fund_class();
			break;
		case 1700744: /* ERR_FULL_REDEMPTION_INDICATED */
			conditionObj = new CIFast_IFast_ifastcbo_err_full_redemption_indicated();
			break;
		case 1700745: /* ERR_FULL_REDEMPTION_NOT_ALLOW */
			conditionObj = new CIFast_IFast_ifastcbo_err_full_redemption_not_allow();
			break;
		case 1700746: /* ERR_FULL_REDEMPTION_PERCENTAGE_MUST_BE_ZERO_FOR_EACH_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_full_redemption_percentage_must_be_zero_for_each_fund();
			break;
		case 1700747: /* ERR_FULL_ROLLOVER_EXCHANGE_FOR_OMNIBUS_ACCT */
			conditionObj = new CIFast_IFast_ifastcbo_err_full_rollover_exchange_for_omnibus_acct();
			break;
		case 1700748: /* ERR_FULL_TRANSFER_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_full_transfer_not_allowed();
			break;
		case 1700749: /* ERR_FULL_WITHDRAW_FOR_OMNIBUS_ACCT */
			conditionObj = new CIFast_IFast_ifastcbo_err_full_withdraw_for_omnibus_acct();
			break;
		case 1700750: /* ERR_FULL_WITHDRAWALS_NOT_ALLOWED_FOR_OMNIBUS_ACCOUNTS */
			conditionObj = new CIFast_IFast_ifastcbo_err_full_withdrawals_not_allowed_for_omnibus_accounts();
			break;
		case 1700751: /* ERR_FUND_ACCOUNTANT_ENTITY_REQUIRE_FUND_ACCOUNTANT_ID */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_accountant_entity_require_fund_accountant_id();
			break;
		case 1700752: /* ERR_FUND_ALLOC_LIST_MANAGEMENT_FEE */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_alloc_list_management_fee();
			break;
		case 1700753: /* ERR_FUND_ALLOC_ONE_FUND_ONLY */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_alloc_one_fund_only();
			break;
		case 1700754: /* ERR_FUND_ALLOC_SET_UP */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_alloc_set_up();
			break;
		case 1700755: /* ERR_FUND_BROKER_CODE_IS_EMPTY */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_broker_code_is_empty();
			break;
		case 1700756: /* ERR_FUND_BROKER_CODE_NOT_EXISTING */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_broker_code_not_existing();
			break;
		case 1700757: /* ERR_FUND_BROKER_INVESTRO_CAPABLE_WHILE_FUND_IS_NOT */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_broker_investro_capable_while_fund_is_not();
			break;
		case 1700758: /* ERR_FUND_BROKER_IS_NOT_EFFECTIVE */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_broker_is_not_effective();
			break;
		case 1700759: /* ERR_FUND_BROKER_NOT_ELIGIBLE_TO_TRADE_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_broker_not_eligible_to_trade_fund();
			break;
		case 1700760: /* ERR_FUND_BROKER_SETTLEMENT_INSTR_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_broker_settlement_instr_missing();
			break;
		case 1700761: /* ERR_FUND_CAN_NOT_BE_BLANK */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_can_not_be_blank();
			break;
		case 1700762: /* ERR_FUND_CANNOT_BE_BLANK_FOR_BEARER_CERTIFICATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_cannot_be_blank_for_bearer_certificate();
			break;
		case 1700763: /* ERR_FUND_CANNOTBE_DIF */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_cannotbe_dif();
			break;
		case 1700764: /* ERR_FUND_CAPPED_AT_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_capped_at_account();
			break;
		case 1700765: /* ERR_FUND_CAPPED_AT_FND_CLS */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_capped_at_fnd_cls();
			break;
		case 1700766: /* ERR_FUND_CLASS_AMOUNT_TRADE_STOP_FLAG_ON */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_class_amount_trade_stop_flag_on();
			break;
		case 1700767: /* ERR_FUND_CLASS_CANNOT_PARENT */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_class_cannot_parent();
			break;
		case 1700768: /* ERR_FUND_CLASS_DOES_NOT_MATCH */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_class_does_not_match();
			break;
		case 1700769: /* ERR_FUND_CLASS_EXCHANGEIN_STOP_FLAG_ON */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_class_exchangein_stop_flag_on();
			break;
		case 1700770: /* ERR_FUND_CLASS_EXCHANGEOUT_STOP_FLAG_ON */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_class_exchangeout_stop_flag_on();
			break;
		case 1700771: /* ERR_FUND_CLASS_FOR_MANAGEMENT_FEE */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_class_for_management_fee();
			break;
		case 1700772: /* ERR_FUND_CLASS_FOR_MANAGEMENT_FEE_REBATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_class_for_management_fee_rebate();
			break;
		case 1700773: /* ERR_FUND_CLASS_MUST_BE_AMS_PARENT_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_class_must_be_ams_parent_fund();
			break;
		case 1700774: /* ERR_FUND_CLASS_MUST_BE_CHILD */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_class_must_be_child();
			break;
		case 1700775: /* ERR_FUND_CLASS_MUST_BE_IN_GROUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_class_must_be_in_group();
			break;
		case 1700776: /* ERR_FUND_CLASS_MUST_BE_PARENT */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_class_must_be_parent();
			break;
		case 1700777: /* ERR_FUND_CLASS_MUST_BE_PARENT_CHILD */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_class_must_be_parent_child();
			break;
		case 1700778: /* ERR_FUND_CLASS_MUST_BE_SPECIFIED */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_class_must_be_specified();
			break;
		case 1700779: /* ERR_FUND_CLASS_MUST_BLANK_FOR_BANKRUPTCY */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_class_must_blank_for_bankruptcy();
			break;
		case 1700780: /* ERR_FUND_CLASS_MUST_BOTH_BE_BLANK */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_class_must_both_be_blank();
			break;
		case 1700781: /* ERR_FUND_CLASS_NOT_ALLOWED_TO_EXCHANGE */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_class_not_allowed_to_exchange();
			break;
		case 1700782: /* ERR_FUND_CLASS_NOT_ALLOWED_UNDER_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_class_not_allowed_under_account();
			break;
		case 1700783: /* ERR_FUND_CLASS_NOT_APPLICABLE */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_class_not_applicable();
			break;
		case 1700784: /* ERR_FUND_CLASS_NOT_AVAILABLE_FOR_BROKER */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_class_not_available_for_broker();
			break;
		case 1700785: /* ERR_FUND_CLASS_NOT_AVAILABLE_FOR_SALESREP */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_class_not_available_for_salesrep();
			break;
		case 1700786: /* ERR_FUND_CLASS_NOT_AVAILABLE_TO_CURRENT_ACCT_PORTFOLIO */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_class_not_available_to_current_acct_portfolio();
			break;
		case 1700787: /* ERR_FUND_CLASS_NOT_AVAILABLE_TO_GROUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_class_not_available_to_group();
			break;
		case 1700788: /* ERR_FUND_CLASS_NOT_EFFECTIVE */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_class_not_effective();
			break;
		case 1700789: /* ERR_FUND_CLASS_NOT_IN_PORTFOLIO */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_class_not_in_portfolio();
			break;
		case 1700790: /* ERR_FUND_CLASS_NOT_PROTECTED */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_class_not_protected();
			break;
		case 1700791: /* ERR_FUND_CLASS_NOT_SUPPORTED_FOR_DISTRIB_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_class_not_supported_for_distrib_type();
			break;
		case 1700792: /* ERR_FUND_CLASS_PAC_STOP_FLAG_ON */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_class_pac_stop_flag_on();
			break;
		case 1700793: /* ERR_FUND_CLASS_PURCHASE_STOP_FLAG_ON */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_class_purchase_stop_flag_on();
			break;
		case 1700794: /* ERR_FUND_CLASS_REDEMPTION_STOP_FLAG_ON */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_class_redemption_stop_flag_on();
			break;
		case 1700795: /* ERR_FUND_CLASS_STOP_FLAG_ON */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_class_stop_flag_on();
			break;
		case 1700796: /* ERR_FUND_CLASS_SWP_STOP_FLAG_ON */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_class_swp_stop_flag_on();
			break;
		case 1700797: /* ERR_FUND_CLASS_SYSGENTRFIN_STOP_FLAG_ON */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_class_sysgentrfin_stop_flag_on();
			break;
		case 1700798: /* ERR_FUND_CLASS_SYSGENTRFOUT_STOP_FLAG_ON */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_class_sysgentrfout_stop_flag_on();
			break;
		case 1700799: /* ERR_FUND_CLASS_TRANSFERIN_STOP_FLAG_ON */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_class_transferin_stop_flag_on();
			break;
		case 1700800: /* ERR_FUND_CLASS_TRANSFEROUT_STOP_FLAG_ON */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_class_transferout_stop_flag_on();
			break;
		case 1700801: /* ERR_FUND_CLASS_XFER_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_class_xfer_not_allowed();
			break;
		case 1700802: /* ERR_FUND_CODE_MUST_BE_IN_GROUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_code_must_be_in_group();
			break;
		case 1700803: /* ERR_FUND_CODES_MUST_BE_BLANK_FOR_REDEMPTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_codes_must_be_blank_for_redemption();
			break;
		case 1700804: /* ERR_FUND_COMMGROUP_MUST_BE_ENTERED */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_commgroup_must_be_entered();
			break;
		case 1700805: /* ERR_FUND_CURRENCIES_NOT_MATCHING */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_currencies_not_matching();
			break;
		case 1700806: /* ERR_FUND_CURRENCY_DIFFERENT */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_currency_different();
			break;
		case 1700807: /* ERR_FUND_CUSTODIAN_ENTITY_REQUIRE_FUND_CUSTODIAN_ID */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_custodian_entity_require_fund_custodian_id();
			break;
		case 1700808: /* ERR_FUND_FEE_DETAIL_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_fee_detail_not_exist();
			break;
		case 1700809: /* ERR_FUND_FEE_DOES_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_fee_does_not_exist();
			break;
		case 1700810: /* ERR_FUND_FOREIGN_CURRENCY */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_foreign_currency();
			break;
		case 1700811: /* ERR_FUND_GROUP_NOT_EXIST_FOR_MANAGEMENT_FEE */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_group_not_exist_for_management_fee();
			break;
		case 1700812: /* ERR_FUND_HAS_CERTIFICATE_UNITS */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_has_certificate_units();
			break;
		case 1700813: /* ERR_FUND_INVALID_FOR_REGISTER_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_invalid_for_register_account();
			break;
		case 1700814: /* ERR_FUND_INVESTRO_CAPABLE_WHILE_FUND_BROKER_IS_NOT */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_investro_capable_while_fund_broker_is_not();
			break;
		case 1700815: /* ERR_FUND_IS_NOT_ACCRUAL_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_is_not_accrual_type();
			break;
		case 1700816: /* ERR_FUND_LOAD_GRP_NOT_SAME_UNDER_AMS_ALLOC_SETUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_load_grp_not_same_under_ams_alloc_setup();
			break;
		case 1700817: /* ERR_FUND_MUST_BE_DIFF */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_must_be_diff();
			break;
		case 1700818: /* ERR_FUND_MUST_BE_GIA */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_must_be_gia();
			break;
		case 1700819: /* ERR_FUND_NOT_EFFECTIVE */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_not_effective();
			break;
		case 1700820: /* ERR_FUND_NOT_ELIGABLE_FOR_ROLLOVEREX */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_not_eligable_for_rolloverex();
			break;
		case 1700821: /* ERR_FUND_NOT_ELIGIBLE_FCTRFR */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_not_eligible_fctrfr();
			break;
		case 1700822: /* ERR_FUND_NOT_ELIGIBLE_FOR_MGMT_FEE */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_not_eligible_for_mgmt_fee();
			break;
		case 1700823: /* ERR_FUND_NOT_LSIF */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_not_lsif();
			break;
		case 1700824: /* ERR_FUND_NOT_MARGIN_ELIGIBLE */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_not_margin_eligible();
			break;
		case 1700825: /* ERR_FUND_NOT_PUEV_CAPABLE */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_not_puev_capable();
			break;
		case 1700826: /* ERR_FUND_NOT_RRIF_ELIGIBLE */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_not_rrif_eligible();
			break;
		case 1700827: /* ERR_FUND_NOT_RRSP_ELIGIBLE */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_not_rrsp_eligible();
			break;
		case 1700828: /* ERR_FUND_NOT_WITHIN_REINVEST_PURCHASE_SCHEDULE */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_not_within_reinvest_purchase_schedule();
			break;
		case 1700829: /* ERR_FUND_OR_ALLOCATION_MUST_ENTER */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_or_allocation_must_enter();
			break;
		case 1700830: /* ERR_FUND_STOP_TRANSFER */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_stop_transfer();
			break;
		case 1700831: /* ERR_FUND_SYSGENTRFIN_STOP_FLAG_ON */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_sysgentrfin_stop_flag_on();
			break;
		case 1700832: /* ERR_FUND_UNIT_PRICE_NOT_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_unit_price_not_available();
			break;
		case 1700833: /* ERR_FUNDCLASS_SETTLE_CURRENCY_DIFFERENT */
			conditionObj = new CIFast_IFast_ifastcbo_err_fundclass_settle_currency_different();
			break;
		case 1700834: /* ERR_FUNDCODE_SETTLE_CURRENCY */
			conditionObj = new CIFast_IFast_ifastcbo_err_fundcode_settle_currency();
			break;
		case 1700835: /* ERR_FUNDS_IN_ALLOC_NOT_EXCHANGABLE */
			conditionObj = new CIFast_IFast_ifastcbo_err_funds_in_alloc_not_exchangable();
			break;
		case 1700836: /* ERR_FUNDTO_CLASSTO_ACCOUNTTO */
			conditionObj = new CIFast_IFast_ifastcbo_err_fundto_classto_accountto();
			break;
		case 1700837: /* ERR_FUNDTO_CLASSTO_DIFFERENT */
			conditionObj = new CIFast_IFast_ifastcbo_err_fundto_classto_different();
			break;
		case 1700838: /* ERR_FUNDTO_GIC_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_fundto_gic_not_allowed();
			break;
		case 1700839: /* ERR_FUTURE_BIRTHDATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_future_birthdate();
			break;
		case 1700840: /* ERR_FUTURE_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_future_date();
			break;
		case 1700841: /* ERR_FUTURE_DATE_NOT_ALLOWED_FOR_RT511CUTOFF_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_future_date_not_allowed_for_rt511cutoff_date();
			break;
		case 1700842: /* ERR_FUTURE_DATED_STOPDATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_future_dated_stopdate();
			break;
		case 1700843: /* ERR_FUTURE_DATED_TRADE */
			conditionObj = new CIFast_IFast_ifastcbo_err_future_dated_trade();
			break;
		case 1700844: /* ERR_FUTURE_DEAL_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_future_deal_date();
			break;
		case 1700845: /* ERR_FUTURE_DEATH_NOTIFY */
			conditionObj = new CIFast_IFast_ifastcbo_err_future_death_notify();
			break;
		case 1700846: /* ERR_FUTURE_DEATHDATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_future_deathdate();
			break;
		case 1700847: /* ERR_FX_RATE_IS_EMPTY */
			conditionObj = new CIFast_IFast_ifastcbo_err_fx_rate_is_empty();
			break;
		case 1700848: /* ERR_GENDER_CANNOT_BE_BLANK_FOR_NMCR_SINGLE_LIFE_CONTRACT */
			conditionObj = new CIFast_IFast_ifastcbo_err_gender_cannot_be_blank_for_nmcr_single_life_contract();
			break;
		case 1700849: /* ERR_GENDER_CHANGE_NOT_ALLOWED_FOR_ELECTED_SINGLE_LIFE_NMCR_CONTRACT */
			conditionObj = new CIFast_IFast_ifastcbo_err_gender_change_not_allowed_for_elected_single_life_nmcr_contract();
			break;
		case 1700850: /* ERR_GENDER_REQUIRED_FOR_ENTITY_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_gender_required_for_entity_type();
			break;
		case 1700851: /* ERR_GI_FUND_IS_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_gi_fund_is_not_allowed();
			break;
		case 1700852: /* ERR_GI_NET_REDEMPTION_CAN_USE_ONLY_ONE_INVESTMENT */
			conditionObj = new CIFast_IFast_ifastcbo_err_gi_net_redemption_can_use_only_one_investment();
			break;
		case 1700853: /* ERR_GI_SELECTED_AMOUNT_NOT_TRADE_AMOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_gi_selected_amount_not_trade_amount();
			break;
		case 1700854: /* ERR_GI_SELECTED_TOTAL_NOT_100 */
			conditionObj = new CIFast_IFast_ifastcbo_err_gi_selected_total_not_100();
			break;
		case 1700855: /* ERR_GIC_FUND_NOT_ALLOWED_IN_AMS */
			conditionObj = new CIFast_IFast_ifastcbo_err_gic_fund_not_allowed_in_ams();
			break;
		case 1700856: /* ERR_GIC_PURCHASE_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_gic_purchase_not_allowed();
			break;
		case 1700857: /* ERR_GMWB_PAYOPTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_gmwb_payoption();
			break;
		case 1700858: /* ERR_GRAND_FATHER_DATE_BACKWARD */
			conditionObj = new CIFast_IFast_ifastcbo_err_grand_father_date_backward();
			break;
		case 1700859: /* ERR_GRAND_FATHER_DATE_CANNOT_EARLIER_THAN_EFFECTIVE_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_grand_father_date_cannot_earlier_than_effective_date();
			break;
		case 1700860: /* ERR_GRANT_AMOUNT_NOT_APPLICABLE */
			conditionObj = new CIFast_IFast_ifastcbo_err_grant_amount_not_applicable();
			break;
		case 1700861: /* ERR_GRANT_ASSOC_WITH_TRADE */
			conditionObj = new CIFast_IFast_ifastcbo_err_grant_assoc_with_trade();
			break;
		case 1700862: /* ERR_GROSS_FULL_REDEMPTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_gross_full_redemption();
			break;
		case 1700863: /* ERR_GROSS_REDEMPTION_MINIMUM_APPLIES */
			conditionObj = new CIFast_IFast_ifastcbo_err_gross_redemption_minimum_applies();
			break;
		case 1700864: /* ERR_GROUP_CODE_LEVEL */
			conditionObj = new CIFast_IFast_ifastcbo_err_group_code_level();
			break;
		case 1700865: /* ERR_GROUP_NUMBER_IS_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_group_number_is_required();
			break;
		case 1700866: /* ERR_GROUP_STOP_FLAG_ON */
			conditionObj = new CIFast_IFast_ifastcbo_err_group_stop_flag_on();
			break;
		case 1700867: /* ERR_GUAGUARD_NOT_SAME_BETWEEN_TO_TI */
			conditionObj = new CIFast_IFast_ifastcbo_err_guaguard_not_same_between_to_ti();
			break;
		case 1700868: /* ERR_GUAR_TRANS_EVENTS_EXIST */
			conditionObj = new CIFast_IFast_ifastcbo_err_guar_trans_events_exist();
			break;
		case 1700869: /* ERR_GUARANTEE_ADJUSTMENT_EXISTS_AFTER_TRADE_DATE_INA */
			conditionObj = new CIFast_IFast_ifastcbo_err_guarantee_adjustment_exists_after_trade_date_ina();
			break;
		case 1700870: /* ERR_GUARANTEE_FEE_TRADE_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_guarantee_fee_trade_not_allowed();
			break;
		case 1700871: /* ERR_GUARANTEE_OVERRIDE_FLAG_IS_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_guarantee_override_flag_is_required();
			break;
		case 1700872: /* ERR_HAS_NO_INQ_PERMISSION_FOR_SETTLEMENT */
			conditionObj = new CIFast_IFast_ifastcbo_err_has_no_inq_permission_for_settlement();
			break;
		case 1700873: /* ERR_HOLDING_COMP_CODE_IS_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_holding_comp_code_is_required();
			break;
		case 1700874: /* ERR_HURDLE_BETWEEN_TWO_REOCRDS */
			conditionObj = new CIFast_IFast_ifastcbo_err_hurdle_between_two_reocrds();
			break;
		case 1700875: /* ERR_HURDLE_CALCULATED */
			conditionObj = new CIFast_IFast_ifastcbo_err_hurdle_calculated();
			break;
		case 1700876: /* ERR_HURDLE_RATE_ZERO */
			conditionObj = new CIFast_IFast_ifastcbo_err_hurdle_rate_zero();
			break;
		case 1700877: /* ERR_ID_INFO_IS_MANDATORY_FOR_ROUTINGTYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_id_info_is_mandatory_for_routingtype();
			break;
		case 1700878: /* ERR_ID_TYPE_DUPLICATED_RECORD */
			conditionObj = new CIFast_IFast_ifastcbo_err_id_type_duplicated_record();
			break;
		case 1700879: /* ERR_ID_TYPE_IS_NOT_APPLICABLE_FOR_ENTITY_CATEGORY */
			conditionObj = new CIFast_IFast_ifastcbo_err_id_type_is_not_applicable_for_entity_category();
			break;
		case 1700880: /* ERR_ID_TYPE_IS_REQUIRED_FOR_ENTITY_CATEGORY */
			conditionObj = new CIFast_IFast_ifastcbo_err_id_type_is_required_for_entity_category();
			break;
		case 1700881: /* ERR_ID_TYPE_NOT_APPLICABLE_FOR_ACCOUNT_PROPRIETORY */
			conditionObj = new CIFast_IFast_ifastcbo_err_id_type_not_applicable_for_account_proprietory();
			break;
		case 1700882: /* ERR_ID_TYPE_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_id_type_required();
			break;
		case 1700883: /* ERR_ID_TYPE_REQUIRED_FOR_FUNDBROKER */
			conditionObj = new CIFast_IFast_ifastcbo_err_id_type_required_for_fundbroker();
			break;
		case 1700884: /* ERR_IDENTICAL_ACCT_DEFAULT_ALLOCS */
			conditionObj = new CIFast_IFast_ifastcbo_err_identical_acct_default_allocs();
			break;
		case 1700885: /* ERR_IDENTICAL_FUND_ALLOCS */
			conditionObj = new CIFast_IFast_ifastcbo_err_identical_fund_allocs();
			break;
		case 1700886: /* ERR_IDENTICAL_SHR_DEFAULT_ALLOCS */
			conditionObj = new CIFast_IFast_ifastcbo_err_identical_shr_default_allocs();
			break;
		case 1700887: /* ERR_IDENTICAL_SPLIT_COM */
			conditionObj = new CIFast_IFast_ifastcbo_err_identical_split_com();
			break;
		case 1700888: /* ERR_IDTYPE_FOR_COUNTRY_EXISTED */
			conditionObj = new CIFast_IFast_ifastcbo_err_idtype_for_country_existed();
			break;
		case 1700889: /* ERR_IDTYPE_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_idtype_missing();
			break;
		case 1700890: /* ERR_ILLEGAL_REDEMPTION_CODE_FOR_ACCT_TAX_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_illegal_redemption_code_for_acct_tax_type();
			break;
		case 1700891: /* ERR_INACTIVE_SALES_REP */
			conditionObj = new CIFast_IFast_ifastcbo_err_inactive_sales_rep();
			break;
		case 1700892: /* ERR_INCOMPLETE_FROM_FUND_INFORMATION */
			conditionObj = new CIFast_IFast_ifastcbo_err_incomplete_from_fund_information();
			break;
		case 1700893: /* ERR_INCOMPLETE_TO_INFORMATION */
			conditionObj = new CIFast_IFast_ifastcbo_err_incomplete_to_information();
			break;
		case 1700894: /* ERR_INCORRECT_PRECISION */
			conditionObj = new CIFast_IFast_ifastcbo_err_incorrect_precision();
			break;
		case 1700895: /* ERR_INCREMENTED_AMT_IS_RDR_ADVICED */
			conditionObj = new CIFast_IFast_ifastcbo_err_incremented_amt_is_rdr_adviced();
			break;
		case 1700896: /* ERR_INDEX_DATE_LATER_THAN_END_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_index_date_later_than_end_date();
			break;
		case 1700897: /* ERR_INDEX_DATE_RANGE_OVERLAP */
			conditionObj = new CIFast_IFast_ifastcbo_err_index_date_range_overlap();
			break;
		case 1700898: /* ERR_INDEX_FRQ_BEYOND_END_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_index_frq_beyond_end_date();
			break;
		case 1700899: /* ERR_INDEX_FRQ_LESS_THAN_PAC_SWP_FRQ */
			conditionObj = new CIFast_IFast_ifastcbo_err_index_frq_less_than_pac_swp_frq();
			break;
		case 1700900: /* ERR_INDEXING_EXISTS */
			conditionObj = new CIFast_IFast_ifastcbo_err_indexing_exists();
			break;
		case 1700901: /* ERR_INIT_CONTRIB_MUST_GREATER_THAN_FEE */
			conditionObj = new CIFast_IFast_ifastcbo_err_init_contrib_must_greater_than_fee();
			break;
		case 1700902: /* ERR_INIT_CONTRIB_MUST_GREATER_THAN_FEE_12 */
			conditionObj = new CIFast_IFast_ifastcbo_err_init_contrib_must_greater_than_fee_12();
			break;
		case 1700903: /* ERR_INPUT_FUND_DOMESTIC */
			conditionObj = new CIFast_IFast_ifastcbo_err_input_fund_domestic();
			break;
		case 1700904: /* ERR_INPUTDATATYPE_EMPTY */
			conditionObj = new CIFast_IFast_ifastcbo_err_inputdatatype_empty();
			break;
		case 1700905: /* ERR_INPUTED_VALUES_IS_NOT_NSCC_COMPLIANT */
			conditionObj = new CIFast_IFast_ifastcbo_err_inputed_values_is_not_nscc_compliant();
			break;
		case 1700906: /* ERR_INSTCODE_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastcbo_err_instcode_not_exist();
			break;
		case 1700907: /* ERR_INSTCODE_NUMERIC */
			conditionObj = new CIFast_IFast_ifastcbo_err_instcode_numeric();
			break;
		case 1700908: /* ERR_INSTCODE_TOO_BIG */
			conditionObj = new CIFast_IFast_ifastcbo_err_instcode_too_big();
			break;
		case 1700909: /* ERR_INSTCODE_TRANSITNO_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastcbo_err_instcode_transitno_not_exist();
			break;
		case 1700910: /* ERR_INSTR_CANNOT_COEXIST */
			conditionObj = new CIFast_IFast_ifastcbo_err_instr_cannot_coexist();
			break;
		case 1700911: /* ERR_INSTR_DETAILS_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_instr_details_missing();
			break;
		case 1700912: /* ERR_INSUFFICENT_UNITS_FOR_UC_TRANSFER_TRADES */
			conditionObj = new CIFast_IFast_ifastcbo_err_insufficent_units_for_uc_transfer_trades();
			break;
		case 1700913: /* ERR_INSUFFICIENT_BALANCE_FOR_NEG_MONEY_MKT */
			conditionObj = new CIFast_IFast_ifastcbo_err_insufficient_balance_for_neg_money_mkt();
			break;
		case 1700914: /* ERR_INSUFFICIENT_QESI_GRANTS */
			conditionObj = new CIFast_IFast_ifastcbo_err_insufficient_qesi_grants();
			break;
		case 1700915: /* ERR_INTERMEDIARY_ACCOUNT_NUMBER_IS_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_intermediary_account_number_is_required();
			break;
		case 1700916: /* ERR_INTERMEDIARY_CODE_IS_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_intermediary_code_is_required();
			break;
		case 1700917: /* ERR_INVALID_ACCOUNT_NUMBER */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_account_number();
			break;
		case 1700918: /* ERR_INVALID_AGE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_age();
			break;
		case 1700919: /* ERR_INVALID_AMOUNT_CODE_FOR_LLP_REPAYMENT */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_amount_code_for_llp_repayment();
			break;
		case 1700920: /* ERR_INVALID_AMOUNT_TYPE_FOR_PAC */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_amount_type_for_pac();
			break;
		case 1700921: /* ERR_INVALID_AMOUNT_TYPE_FOR_SWP */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_amount_type_for_swp();
			break;
		case 1700922: /* ERR_INVALID_AMS_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_ams_account();
			break;
		case 1700923: /* ERR_INVALID_AMS_CODE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_ams_code();
			break;
		case 1700924: /* ERR_INVALID_AMSCODE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_amscode();
			break;
		case 1700925: /* ERR_INVALID_AMSCODE_REBALANCING_ASSET_MIX */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_amscode_rebalancing_asset_mix();
			break;
		case 1700926: /* ERR_INVALID_AMSCODE_TARGET_ASSET_MIX */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_amscode_target_asset_mix();
			break;
		case 1700927: /* ERR_INVALID_AMT_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_amt_type();
			break;
		case 1700928: /* ERR_INVALID_AMTCODE_FOR_INVESTMENT_ALLOCATION */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_amtcode_for_investment_allocation();
			break;
		case 1700929: /* ERR_INVALID_AMTTYPE_FOR_BEL_REDEMPTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_amttype_for_bel_redemption();
			break;
		case 1700930: /* ERR_INVALID_AMTTYPE_FOR_FULL_TRANSFER */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_amttype_for_full_transfer();
			break;
		case 1700931: /* ERR_INVALID_AMTTYPE_FOR_FUND_CLASS */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_amttype_for_fund_class();
			break;
		case 1700932: /* ERR_INVALID_AMTTYPE_FOR_INVESTMENT_ALLOCATION */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_amttype_for_investment_allocation();
			break;
		case 1700933: /* ERR_INVALID_AMTTYPE_FOR_LSIF_REDEMPTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_amttype_for_lsif_redemption();
			break;
		case 1700934: /* ERR_INVALID_AMTTYPE_FOR_PURCHASE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_amttype_for_purchase();
			break;
		case 1700935: /* ERR_INVALID_AMTTYPE_FOR_REDEMPTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_amttype_for_redemption();
			break;
		case 1700936: /* ERR_INVALID_AMTTYPE_FOR_REDEMPTION_CODE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_amttype_for_redemption_code();
			break;
		case 1700937: /* ERR_INVALID_AMTTYPE_FOR_TRADETYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_amttype_for_tradetype();
			break;
		case 1700938: /* ERR_INVALID_AUTH_VALUE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_auth_value();
			break;
		case 1700939: /* ERR_INVALID_BROKER_FOR_MONEY_MARKET_WIRE_ORDERS */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_broker_for_money_market_wire_orders();
			break;
		case 1700940: /* ERR_INVALID_BUSINESSNO */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_businessno();
			break;
		case 1700941: /* ERR_INVALID_CASH_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_cash_date();
			break;
		case 1700942: /* ERR_INVALID_CESG_REPAYMENT_REASON_CODE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_cesg_repayment_reason_code();
			break;
		case 1700943: /* ERR_INVALID_CHAR */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_char();
			break;
		case 1700944: /* ERR_INVALID_CLEARING_METHOD_FOR_REALIGNMNT_TR */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_clearing_method_for_realignmnt_tr();
			break;
		case 1700945: /* ERR_INVALID_CLOSE_FUND_REDEMPTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_close_fund_redemption();
			break;
		case 1700946: /* ERR_INVALID_CODE_FOR_TRANSFER */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_code_for_transfer();
			break;
		case 1700947: /* ERR_INVALID_COMBINATION_ACCT_TYPE_ENTITY_CATEGORY */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_combination_acct_type_entity_category();
			break;
		case 1700948: /* ERR_INVALID_CONFIRM_TYPE_FOR_NETWORKID */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_confirm_type_for_networkid();
			break;
		case 1700949: /* ERR_INVALID_CONSOL_VALUE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_consol_value();
			break;
		case 1700950: /* ERR_INVALID_CONTRACT_TERM */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_contract_term();
			break;
		case 1700951: /* ERR_INVALID_CURRENCYOPTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_currencyoption();
			break;
		case 1700952: /* ERR_INVALID_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_date();
			break;
		case 1700953: /* ERR_INVALID_DEALER_FOR_ORDER_SETTLEMENT_BY_INTERMEDIARY */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_dealer_for_order_settlement_by_intermediary();
			break;
		case 1700954: /* ERR_INVALID_DSC_OVERRIDE_PERCENTAGE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_dsc_override_percentage();
			break;
		case 1700955: /* ERR_INVALID_EARLY_END_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_early_end_date();
			break;
		case 1700956: /* ERR_INVALID_EFFECTIVE_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_effective_date();
			break;
		case 1700957: /* ERR_INVALID_EMAIL */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_email();
			break;
		case 1700958: /* ERR_INVALID_END_BIRTH_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_end_birth_date();
			break;
		case 1700959: /* ERR_INVALID_END_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_end_date();
			break;
		case 1700960: /* ERR_INVALID_END_START_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_end_start_date();
			break;
		case 1700961: /* ERR_INVALID_FEE_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_fee_type();
			break;
		case 1700962: /* ERR_INVALID_FEE_VALUE_RESP_GRANT */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_fee_value_resp_grant();
			break;
		case 1700963: /* ERR_INVALID_FIRE_FIGHTER_LOGON */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_fire_fighter_logon();
			break;
		case 1700964: /* ERR_INVALID_FOR_FOREIGN_CONTENT_TRANSFER */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_for_foreign_content_transfer();
			break;
		case 1700965: /* ERR_INVALID_FS_RELATIONSHIP */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_fs_relationship();
			break;
		case 1700966: /* ERR_INVALID_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_fund();
			break;
		case 1700967: /* ERR_INVALID_FUND_BROKER */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_fund_broker();
			break;
		case 1700968: /* ERR_INVALID_FUND_CLASS_CODES */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_fund_class_codes();
			break;
		case 1700969: /* ERR_INVALID_FUND_CODE_FOR_ACCT_CATEGORY_FUND_ON_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_fund_code_for_acct_category_fund_on_fund();
			break;
		case 1700970: /* ERR_INVALID_FUND_FUND_BROKER_COMBINATION */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_fund_fund_broker_combination();
			break;
		case 1700971: /* ERR_INVALID_FUND_ISIN */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_fund_isin();
			break;
		case 1700972: /* ERR_INVALID_FUND_NUMBER */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_fund_number();
			break;
		case 1700973: /* ERR_INVALID_FUND_WKN */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_fund_wkn();
			break;
		case 1700974: /* ERR_INVALID_FUNDBROKER_OFFSETTIME */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_fundbroker_offsettime();
			break;
		case 1700975: /* ERR_INVALID_GIIN_FORMAT */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_giin_format();
			break;
		case 1700976: /* ERR_INVALID_GRANT_REPAYMENT_REASON_REDCODE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_grant_repayment_reason_redcode();
			break;
		case 1700977: /* ERR_INVALID_GUARD_OPTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_guard_option();
			break;
		case 1700978: /* ERR_INVALID_HKID */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_hkid();
			break;
		case 1700979: /* ERR_INVALID_HOLDING_COMP_CODE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_holding_comp_code();
			break;
		case 1700980: /* ERR_INVALID_INCEPTION_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_inception_date();
			break;
		case 1700981: /* ERR_INVALID_INSTITUTE_CODE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_institute_code();
			break;
		case 1700982: /* ERR_INVALID_INTEREST_ON_CLOSE_FUND_REDEMPTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_interest_on_close_fund_redemption();
			break;
		case 1700983: /* ERR_INVALID_INTERESTINST_DATA */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_interestinst_data();
			break;
		case 1700984: /* ERR_INVALID_INTERMEDIARY_FOR_MONEY_MARKET_WIRE_ORDERS */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_intermediary_for_money_market_wire_orders();
			break;
		case 1700985: /* ERR_INVALID_INTERMEDIARY_FOR_WIRE_ORDERS */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_intermediary_for_wire_orders();
			break;
		case 1700986: /* ERR_INVALID_INVESTMENT_NUMBER */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_investment_number();
			break;
		case 1700987: /* ERR_INVALID_INVESTMENT_STATUS */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_investment_status();
			break;
		case 1700988: /* ERR_INVALID_ISIN_NUMBER */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_isin_number();
			break;
		case 1700989: /* ERR_INVALID_MATURITY_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_maturity_type();
			break;
		case 1700990: /* ERR_INVALID_MF_PAYMENT */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_mf_payment();
			break;
		case 1700991: /* ERR_INVALID_NEGATIVE_AMOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_negative_amount();
			break;
		case 1700992: /* ERR_INVALID_NET */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_net();
			break;
		case 1700993: /* ERR_INVALID_NRIC */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_nric();
			break;
		case 1700994: /* ERR_INVALID_ORDERSRC_FOR_ACCT_DESIGNATION */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_ordersrc_for_acct_designation();
			break;
		case 1700995: /* ERR_INVALID_PAY_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_pay_type();
			break;
		case 1700996: /* ERR_INVALID_PAY_TYPE_FOR_TRADETYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_pay_type_for_tradetype();
			break;
		case 1700997: /* ERR_INVALID_PAYMANT_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_paymant_type();
			break;
		case 1700998: /* ERR_INVALID_PAYMENTYPE_FOR_CURRENCY */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_paymentype_for_currency();
			break;
		case 1700999: /* ERR_INVALID_PCG_FOR_RESP_ACCOUNTHOLDER */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_pcg_for_resp_accountholder();
			break;
		case 1701000: /* ERR_INVALID_PENSION */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_pension();
			break;
		case 1701001: /* ERR_INVALID_PERCENT */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_percent();
			break;
		case 1701002: /* ERR_INVALID_POSTAL_CODE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_postal_code();
			break;
		case 1701003: /* ERR_INVALID_POSTAL_CODE_PROVINCE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_postal_code_province();
			break;
		case 1701004: /* ERR_INVALID_PRICE_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_price_type();
			break;
		case 1701005: /* ERR_INVALID_RANGE_FOR_VALUE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_range_for_value();
			break;
		case 1701006: /* ERR_INVALID_RED_CODE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_red_code();
			break;
		case 1701007: /* ERR_INVALID_RESP_CONTRACTIDS */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_resp_contractids();
			break;
		case 1701008: /* ERR_INVALID_RESP_PLAN */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_resp_plan();
			break;
		case 1701009: /* ERR_INVALID_ROLLOVER_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_rollover_type();
			break;
		case 1701010: /* ERR_INVALID_RXTRANSTYPE_TAXTYPE_COMBINATION */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_rxtranstype_taxtype_combination();
			break;
		case 1701011: /* ERR_INVALID_SETTLE_CURRENCY */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_settle_currency();
			break;
		case 1701012: /* ERR_INVALID_SETTLEINDATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_settleindate();
			break;
		case 1701013: /* ERR_INVALID_SETTLEMENT_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_settlement_date();
			break;
		case 1701014: /* ERR_INVALID_SETTLEMENT_INSTR_CODE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_settlement_instr_code();
			break;
		case 1701015: /* ERR_INVALID_SETTLEMENT_TYPE_FOR_DEALER_OR_INTERMEDIARY */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_settlement_type_for_dealer_or_intermediary();
			break;
		case 1701016: /* ERR_INVALID_SHAREHOLDER_NUM */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_shareholder_num();
			break;
		case 1701017: /* ERR_INVALID_STATUS */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_status();
			break;
		case 1701018: /* ERR_INVALID_STATUS_FOR_ACCESS_ID */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_status_for_access_id();
			break;
		case 1701019: /* ERR_INVALID_TAX_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_tax_type();
			break;
		case 1701020: /* ERR_INVALID_TAX_TYPE_FOR_RESP */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_tax_type_for_resp();
			break;
		case 1701021: /* ERR_INVALID_TAX_TYPE4_REGAGENT */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_tax_type4_regagent();
			break;
		case 1701022: /* ERR_INVALID_TAXTYPE_FOR_PAC_ALLOC */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_taxtype_for_pac_alloc();
			break;
		case 1701023: /* ERR_INVALID_TAXYEAR_FOR_DEPTYPE_REDCODE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_taxyear_for_deptype_redcode();
			break;
		case 1701024: /* ERR_INVALID_TERMINATION_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_termination_date();
			break;
		case 1701025: /* ERR_INVALID_TIME_FORMAT */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_time_format();
			break;
		case 1701026: /* ERR_INVALID_TIS_COST_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_tis_cost_type();
			break;
		case 1701027: /* ERR_INVALID_TRADE_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_trade_date();
			break;
		case 1701028: /* ERR_INVALID_VALUE_FOR_DESGN_INST */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_value_for_desgn_inst();
			break;
		case 1701029: /* ERR_INVALID_VALUE_FOR_PARENT_LEGAL_GUARDIAN */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_value_for_parent_legal_guardian();
			break;
		case 1701030: /* ERR_INVALID_WKN_NUMBER */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_wkn_number();
			break;
		case 1701031: /* ERR_INVALID_YEAR_RESP_OC_WITHDRAWAL */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_year_resp_oc_withdrawal();
			break;
		case 1701032: /* ERR_INVESTOR_AUTHORIZATION_BEFORE_ACCT_EFFDATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_investor_authorization_before_acct_effdate();
			break;
		case 1701033: /* ERR_INVESTOR_AUTHORIZATION_INFO_FOR_CLNT_NON_REGIS_ONLY */
			conditionObj = new CIFast_IFast_ifastcbo_err_investor_authorization_info_for_clnt_non_regis_only();
			break;
		case 1701034: /* ERR_INVESTOR_AUTHORIZATION_INFO_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_investor_authorization_info_missing();
			break;
		case 1701035: /* ERR_IRREVOCABLE_NOT_UPDATABLE_FOR_ACCT_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_irrevocable_not_updatable_for_acct_type();
			break;
		case 1701036: /* ERR_ITF_ENTITY_SETUP_FOR_NON_ITF */
			conditionObj = new CIFast_IFast_ifastcbo_err_itf_entity_setup_for_non_itf();
			break;
		case 1701037: /* ERR_ITF_ENTITY_SHOULD_BE_SETUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_itf_entity_should_be_setup();
			break;
		case 1701038: /* ERR_JOINT_TYPE_NOT_UPDATABLE_FOR_ACCT_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_joint_type_not_updatable_for_acct_type();
			break;
		case 1701039: /* ERR_JUMBO_PRICE_NOT_APPLICABLE */
			conditionObj = new CIFast_IFast_ifastcbo_err_jumbo_price_not_applicable();
			break;
		case 1701040: /* ERR_JURISDICTION_EFFECT_DATE_EARLIER_THAN_SHAREHOLDER */
			conditionObj = new CIFast_IFast_ifastcbo_err_jurisdiction_effect_date_earlier_than_shareholder();
			break;
		case 1701041: /* ERR_JURISDICTION_NOT_SAME_AS_SHRHLDR_JURISDICTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_jurisdiction_not_same_as_shrhldr_jurisdiction();
			break;
		case 1701042: /* ERR_KIID_ATTESTATION */
			conditionObj = new CIFast_IFast_ifastcbo_err_kiid_attestation();
			break;
		case 1701043: /* ERR_LANGUAGE_MUST_BE_ENTERED */
			conditionObj = new CIFast_IFast_ifastcbo_err_language_must_be_entered();
			break;
		case 1701044: /* ERR_LAST_NAME_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_last_name_required();
			break;
		case 1701045: /* ERR_LAST_QUARTER_AS_PENSION */
			conditionObj = new CIFast_IFast_ifastcbo_err_last_quarter_as_pension();
			break;
		case 1701046: /* ERR_LATER_ENDDATE_MATURITY_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_later_enddate_maturity_date();
			break;
		case 1701047: /* ERR_LATER_MONTHEND_MATURITY_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_later_monthend_maturity_date();
			break;
		case 1701048: /* ERR_LATER_QUARTEREND_MATURITY_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_later_quarterend_maturity_date();
			break;
		case 1701049: /* ERR_LB_UP_OVERLAPED */
			conditionObj = new CIFast_IFast_ifastcbo_err_lb_up_overlaped();
			break;
		case 1701050: /* ERR_LB_UP_OVERLAPED_THRSHLD */
			conditionObj = new CIFast_IFast_ifastcbo_err_lb_up_overlaped_thrshld();
			break;
		case 1701051: /* ERR_LEGAL_MATURITY_DATE_EARLY_THAN_TODAY */
			conditionObj = new CIFast_IFast_ifastcbo_err_legal_maturity_date_early_than_today();
			break;
		case 1701052: /* ERR_LESS_THAN_XII_MONTH */
			conditionObj = new CIFast_IFast_ifastcbo_err_less_than_xii_month();
			break;
		case 1701053: /* ERR_LETTER_REQUIRED_EMPTY */
			conditionObj = new CIFast_IFast_ifastcbo_err_letter_required_empty();
			break;
		case 1701054: /* ERR_LIFETIME_CONTRIB_LIMITS_NOT_SETUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_lifetime_contrib_limits_not_setup();
			break;
		case 1701055: /* ERR_LINKED_CONTRACT_DIFFERENT */
			conditionObj = new CIFast_IFast_ifastcbo_err_linked_contract_different();
			break;
		case 1701056: /* ERR_LIP_VAL_MSG */
			conditionObj = new CIFast_IFast_ifastcbo_err_lip_val_msg();
			break;
		case 1701057: /* ERR_LLP_REPAYMENT_UNALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_llp_repayment_unallowed();
			break;
		case 1701058: /* ERR_LOAN_NUM_FOR_ACCTHOLDER */
			conditionObj = new CIFast_IFast_ifastcbo_err_loan_num_for_acctholder();
			break;
		case 1701059: /* ERR_LOAN_NUM_MANDATORY */
			conditionObj = new CIFast_IFast_ifastcbo_err_loan_num_mandatory();
			break;
		case 1701060: /* ERR_LOAN_NUMBER_FOR_ESCROW_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_loan_number_for_escrow_account();
			break;
		case 1701061: /* ERR_LOAN_TYPE_FOR_ESCROW */
			conditionObj = new CIFast_IFast_ifastcbo_err_loan_type_for_escrow();
			break;
		case 1701062: /* ERR_LOAN_TYPE_MANDATORY */
			conditionObj = new CIFast_IFast_ifastcbo_err_loan_type_mandatory();
			break;
		case 1701063: /* ERR_LOCKEDIN_TO_NON_LOCKEDIN_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_lockedin_to_non_lockedin_allowed();
			break;
		case 1701064: /* ERR_LOCKEDIN_TO_NON_REGISTED_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_lockedin_to_non_registed_allowed();
			break;
		case 1701065: /* ERR_LSIF_REDEMPTION_NOT_ENOUGH_UNITS_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastcbo_err_lsif_redemption_not_enough_units_available();
			break;
		case 1701066: /* ERR_LWA_AGE_RATE_IS_NOT_APPLICABLE */
			conditionObj = new CIFast_IFast_ifastcbo_err_lwa_age_rate_is_not_applicable();
			break;
		case 1701067: /* ERR_LWA_ELECTION_DATE_LATER_THAN_TRANSFER_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_lwa_election_date_later_than_transfer_date();
			break;
		case 1701068: /* ERR_LWA_OPTION_NOT_MATCH */
			conditionObj = new CIFast_IFast_ifastcbo_err_lwa_option_not_match();
			break;
		case 1701069: /* ERR_MAIL_CANNOT_BE_NO_FOR_NO_WAIVE */
			conditionObj = new CIFast_IFast_ifastcbo_err_mail_cannot_be_no_for_no_waive();
			break;
		case 1701070: /* ERR_MAIL_CANNOT_BE_YES_FOR_YES_WAIVE */
			conditionObj = new CIFast_IFast_ifastcbo_err_mail_cannot_be_yes_for_yes_waive();
			break;
		case 1701071: /* ERR_MAIL_CONSENT_CANNT_BOTH_YES_OR_NO */
			conditionObj = new CIFast_IFast_ifastcbo_err_mail_consent_cannt_both_yes_or_no();
			break;
		case 1701072: /* ERR_MAIL_OPTION_CANNOT_BE_ALL_NO */
			conditionObj = new CIFast_IFast_ifastcbo_err_mail_option_cannot_be_all_no();
			break;
		case 1701073: /* ERR_MANAGEMENT_FEE_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_management_fee_type();
			break;
		case 1701074: /* ERR_MANDATORY_FIELD */
			conditionObj = new CIFast_IFast_ifastcbo_err_mandatory_field();
			break;
		case 1701075: /* ERR_MANUAL_DIVIDEND_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_manual_dividend_not_allowed();
			break;
		case 1701076: /* ERR_MARGIN_CANNOT_BE_REMOVED */
			conditionObj = new CIFast_IFast_ifastcbo_err_margin_cannot_be_removed();
			break;
		case 1701077: /* ERR_MARGIN_LOAN_CANNOT_COEXIST */
			conditionObj = new CIFast_IFast_ifastcbo_err_margin_loan_cannot_coexist();
			break;
		case 1701078: /* ERR_MARGIN_ONLY_FOR_NEW_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_margin_only_for_new_account();
			break;
		case 1701079: /* ERR_MARGIN_PENDING_NOT_ELIGIBLE */
			conditionObj = new CIFast_IFast_ifastcbo_err_margin_pending_not_eligible();
			break;
		case 1701080: /* ERR_MATSWP_EFFECTIVE_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_matswp_effective_date();
			break;
		case 1701081: /* ERR_MATSWP_INSTUCTIONS_IS_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_matswp_instuctions_is_missing();
			break;
		case 1701082: /* ERR_MATURITY_YEAR_GREATER_ZERO */
			conditionObj = new CIFast_IFast_ifastcbo_err_maturity_year_greater_zero();
			break;
		case 1701083: /* ERR_MAX_LESS_THAN_MIN */
			conditionObj = new CIFast_IFast_ifastcbo_err_max_less_than_min();
			break;
		case 1701084: /* ERR_MAX_PAYMENT_EXCEED */
			conditionObj = new CIFast_IFast_ifastcbo_err_max_payment_exceed();
			break;
		case 1701085: /* ERR_MAXIMUM_INPUT_AMT */
			conditionObj = new CIFast_IFast_ifastcbo_err_maximum_input_amt();
			break;
		case 1701086: /* ERR_MAY_NEED_TO_ADD_NEW_GRANT_REQUEST_FOR_TAX_YEAR */
			conditionObj = new CIFast_IFast_ifastcbo_err_may_need_to_add_new_grant_request_for_tax_year();
			break;
		case 1701087: /* ERR_MGMT_CO_NOT_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastcbo_err_mgmt_co_not_available();
			break;
		case 1701088: /* ERR_MGMT_FEE_MODEL_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_mgmt_fee_model_missing();
			break;
		case 1701089: /* ERR_MGMT_FEE_NOT_ALLOWED_FOR_TAXTYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_mgmt_fee_not_allowed_for_taxtype();
			break;
		case 1701090: /* ERR_MGMT_FEE_REBATE_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_mgmt_fee_rebate_not_allowed();
			break;
		case 1701091: /* ERR_MIN_INIT_PURCHASE */
			conditionObj = new CIFast_IFast_ifastcbo_err_min_init_purchase();
			break;
		case 1701092: /* ERR_MIN_INIT_REDEMPTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_min_init_redemption();
			break;
		case 1701093: /* ERR_MIN_SUBS_PURCHASE */
			conditionObj = new CIFast_IFast_ifastcbo_err_min_subs_purchase();
			break;
		case 1701094: /* ERR_MIN_SUBS_REDEMPTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_min_subs_redemption();
			break;
		case 1701095: /* ERR_MIN_TWO_FUNDS */
			conditionObj = new CIFast_IFast_ifastcbo_err_min_two_funds();
			break;
		case 1701096: /* ERR_MINIMUM_FUND_BALANCE */
			conditionObj = new CIFast_IFast_ifastcbo_err_minimum_fund_balance();
			break;
		case 1701097: /* ERR_MINIMUM_INIT_AMT */
			conditionObj = new CIFast_IFast_ifastcbo_err_minimum_init_amt();
			break;
		case 1701098: /* ERR_MINIMUM_SUBSEQUENT_AMT */
			conditionObj = new CIFast_IFast_ifastcbo_err_minimum_subsequent_amt();
			break;
		case 1701099: /* ERR_MISS_BANK_ACCT_INFO */
			conditionObj = new CIFast_IFast_ifastcbo_err_miss_bank_acct_info();
			break;
		case 1701100: /* ERR_MISS_BANK_COUNTRY */
			conditionObj = new CIFast_IFast_ifastcbo_err_miss_bank_country();
			break;
		case 1701101: /* ERR_MISSING_ACCOUNTABLE_PARTY_FOR_TRADEDATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_missing_accountable_party_for_tradedate();
			break;
		case 1701102: /* ERR_MISSING_ACCTHOLDER_DOFBIRTH */
			conditionObj = new CIFast_IFast_ifastcbo_err_missing_acctholder_dofbirth();
			break;
		case 1701103: /* ERR_MISSING_ACTIVITYID */
			conditionObj = new CIFast_IFast_ifastcbo_err_missing_activityid();
			break;
		case 1701104: /* ERR_MISSING_AGGRORDNUM */
			conditionObj = new CIFast_IFast_ifastcbo_err_missing_aggrordnum();
			break;
		case 1701105: /* ERR_MISSING_DEFAULT */
			conditionObj = new CIFast_IFast_ifastcbo_err_missing_default();
			break;
		case 1701106: /* ERR_MISSING_DEFAULT_FND_MGMT_SETTL_INSTR */
			conditionObj = new CIFast_IFast_ifastcbo_err_missing_default_fnd_mgmt_settl_instr();
			break;
		case 1701107: /* ERR_MISSING_DEFAULT_SETTLEMENT_INSTR */
			conditionObj = new CIFast_IFast_ifastcbo_err_missing_default_settlement_instr();
			break;
		case 1701108: /* ERR_MISSING_ENDDATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_missing_enddate();
			break;
		case 1701109: /* ERR_MISSING_MSGPROCESSCATEGORY */
			conditionObj = new CIFast_IFast_ifastcbo_err_missing_msgprocesscategory();
			break;
		case 1701110: /* ERR_MISSING_MSGPROCESSSTATUS */
			conditionObj = new CIFast_IFast_ifastcbo_err_missing_msgprocessstatus();
			break;
		case 1701111: /* ERR_MISSING_MSGPROCESSTYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_missing_msgprocesstype();
			break;
		case 1701112: /* ERR_MISSING_NEQ */
			conditionObj = new CIFast_IFast_ifastcbo_err_missing_neq();
			break;
		case 1701113: /* ERR_MISSING_NETWORKID */
			conditionObj = new CIFast_IFast_ifastcbo_err_missing_networkid();
			break;
		case 1701114: /* ERR_MISSING_PAYMENT_INSTRUCTIONS_FOR_DISTRIBUTIONS */
			conditionObj = new CIFast_IFast_ifastcbo_err_missing_payment_instructions_for_distributions();
			break;
		case 1701115: /* ERR_MISSING_SENDREFNUM */
			conditionObj = new CIFast_IFast_ifastcbo_err_missing_sendrefnum();
			break;
		case 1701116: /* ERR_MISSING_STARTDATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_missing_startdate();
			break;
		case 1701117: /* ERR_MISSING_TRANSNUM */
			conditionObj = new CIFast_IFast_ifastcbo_err_missing_transnum();
			break;
		case 1701118: /* ERR_MOD_ACCT_TYPE_TRANS_EXIST */
			conditionObj = new CIFast_IFast_ifastcbo_err_mod_acct_type_trans_exist();
			break;
		case 1701119: /* ERR_MOD_TAX_TYPE_FOR_ACCT_WITH_TRADES */
			conditionObj = new CIFast_IFast_ifastcbo_err_mod_tax_type_for_acct_with_trades();
			break;
		case 1701120: /* ERR_MONTHEND_MATURITY_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_monthend_maturity_date();
			break;
		case 1701121: /* ERR_MPS_FUND_NOT_ALLOWED_IN_AMS */
			conditionObj = new CIFast_IFast_ifastcbo_err_mps_fund_not_allowed_in_ams();
			break;
		case 1701122: /* ERR_MULTIPLE_ACCOUNT_OWNER_ENTITY_SHOULD_SETUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_multiple_account_owner_entity_should_setup();
			break;
		case 1701123: /* ERR_MULTIPLE_ACCT_OWNER */
			conditionObj = new CIFast_IFast_ifastcbo_err_multiple_acct_owner();
			break;
		case 1701124: /* ERR_MULTIPLE_ACCT_OWNER_NEEDED */
			conditionObj = new CIFast_IFast_ifastcbo_err_multiple_acct_owner_needed();
			break;
		case 1701125: /* ERR_MULTIPLE_ANNUITANT */
			conditionObj = new CIFast_IFast_ifastcbo_err_multiple_annuitant();
			break;
		case 1701126: /* ERR_MULTIPLE_CLEARING_PLATFROM_ID_NOT_ALLOWED_FOR_CLEARING_PLATFORM */
			conditionObj = new CIFast_IFast_ifastcbo_err_multiple_clearing_platfrom_id_not_allowed_for_clearing_platform();
			break;
		case 1701127: /* ERR_MULTIPLE_CPFB_ACCOUNT_NUMBER_NOT_ALLOWED_FOR_AN_ENTITY */
			conditionObj = new CIFast_IFast_ifastcbo_err_multiple_cpfb_account_number_not_allowed_for_an_entity();
			break;
		case 1701128: /* ERR_MULTIPLE_DEFAULT */
			conditionObj = new CIFast_IFast_ifastcbo_err_multiple_default();
			break;
		case 1701129: /* ERR_MULTIPLE_DEFAULT_FND_MGMT_SETTLE_INSTR */
			conditionObj = new CIFast_IFast_ifastcbo_err_multiple_default_fnd_mgmt_settle_instr();
			break;
		case 1701130: /* ERR_MULTIPLE_DEFAULT_SETTLEMENT_INSTR */
			conditionObj = new CIFast_IFast_ifastcbo_err_multiple_default_settlement_instr();
			break;
		case 1701131: /* ERR_MULTIPLE_GIIN_NOT_ALLOWED_FOR_AN_ENTITY */
			conditionObj = new CIFast_IFast_ifastcbo_err_multiple_giin_not_allowed_for_an_entity();
			break;
		case 1701132: /* ERR_MULTIPLE_NATIONAL_ID_NOT_ALLOWED_FOR_AN_ENTITY */
			conditionObj = new CIFast_IFast_ifastcbo_err_multiple_national_id_not_allowed_for_an_entity();
			break;
		case 1701133: /* ERR_MULTIPLE_NOMINEE_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_multiple_nominee_not_allowed();
			break;
		case 1701134: /* ERR_MULTIPLE_REGISTRATION_AGENT_ENTITIES */
			conditionObj = new CIFast_IFast_ifastcbo_err_multiple_registration_agent_entities();
			break;
		case 1701135: /* ERR_MULTIPLE_REMAININGFLAGS_FOUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_multiple_remainingflags_found();
			break;
		case 1701136: /* ERR_MULTIPLE_SAME_CLEARING_PLATFORM_ENTITY_NOT_ALLOWED_FOR_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_multiple_same_clearing_platform_entity_not_allowed_for_account();
			break;
		case 1701137: /* ERR_MULTIPLE_SPOUSAL */
			conditionObj = new CIFast_IFast_ifastcbo_err_multiple_spousal();
			break;
		case 1701138: /* ERR_MUST_BE_BUSINESS_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_must_be_business_date();
			break;
		case 1701139: /* ERR_MUST_HAVE_ACCOUNT_SPECIFIED_WHEN_AMOUNT_0 */
			conditionObj = new CIFast_IFast_ifastcbo_err_must_have_account_specified_when_amount_0();
			break;
		case 1701140: /* ERR_MUST_HAVE_SPECIFIED_ACCT_WHEN_AMOUNT_ZERO */
			conditionObj = new CIFast_IFast_ifastcbo_err_must_have_specified_acct_when_amount_zero();
			break;
		case 1701141: /* ERR_NAME_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_name_required();
			break;
		case 1701142: /* ERR_NATIONAL_ID_OR_PASSPORT_REQUIRED_FOR_TAX_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_national_id_or_passport_required_for_tax_type();
			break;
		case 1701143: /* ERR_NATIONAL_ID_REQUIRED_FOR_TAX_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_national_id_required_for_tax_type();
			break;
		case 1701144: /* ERR_NEG_MM_CAN_BE_REINVESTED_ONLY_SAME_FUNDCLASS */
			conditionObj = new CIFast_IFast_ifastcbo_err_neg_mm_can_be_reinvested_only_same_fundclass();
			break;
		case 1701145: /* ERR_NEG_MONEY_MARKET_INTEREST_NOT_APPLICABLE_FOR_THIS_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_neg_money_market_interest_not_applicable_for_this_fund();
			break;
		case 1701146: /* ERR_NEGATIVE_EXCH_RATE_NOT_ALLOW */
			conditionObj = new CIFast_IFast_ifastcbo_err_negative_exch_rate_not_allow();
			break;
		case 1701147: /* ERR_NEGATIVE_FEE_NOT_ALLOW */
			conditionObj = new CIFast_IFast_ifastcbo_err_negative_fee_not_allow();
			break;
		case 1701148: /* ERR_NET_AMOUNT_LESS_THEN_ZERO */
			conditionObj = new CIFast_IFast_ifastcbo_err_net_amount_less_then_zero();
			break;
		case 1701149: /* ERR_NET_AMOUNT_WITH_ZERO */
			conditionObj = new CIFast_IFast_ifastcbo_err_net_amount_with_zero();
			break;
		case 1701150: /* ERR_NET_ANNUAL_CONTRIBUTION_IS_ZERO */
			conditionObj = new CIFast_IFast_ifastcbo_err_net_annual_contribution_is_zero();
			break;
		case 1701151: /* ERR_NET_NOT_FOR_ALLOCATION */
			conditionObj = new CIFast_IFast_ifastcbo_err_net_not_for_allocation();
			break;
		case 1701152: /* ERR_NET_NOT_FOR_BEL_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_net_not_for_bel_fund();
			break;
		case 1701153: /* ERR_NET_NOT_FOR_MULTICURRENCY */
			conditionObj = new CIFast_IFast_ifastcbo_err_net_not_for_multicurrency();
			break;
		case 1701154: /* ERR_NET_REDEMPTION_OVER_MINIMUM */
			conditionObj = new CIFast_IFast_ifastcbo_err_net_redemption_over_minimum();
			break;
		case 1701155: /* ERR_Net_SETTLEMENT_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_net_settlement_not_allowed();
			break;
		case 1701156: /* ERR_NET_TRADE_NOT_ALLOWED_FOR_THIRD_PARTY_FUNDS */
			conditionObj = new CIFast_IFast_ifastcbo_err_net_trade_not_allowed_for_third_party_funds();
			break;
		case 1701157: /* ERR_NET_TRANS_AMT_CANNOT_BE_EARLIER_THAN_INIT_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_net_trans_amt_cannot_be_earlier_than_init_date();
			break;
		case 1701158: /* ERR_NET_TRANS_AMT_EXCEED_NET_CESG_OWNING */
			conditionObj = new CIFast_IFast_ifastcbo_err_net_trans_amt_exceed_net_cesg_owning();
			break;
		case 1701159: /* ERR_NET_UNIT_PERCENT_NOT_ALLOW */
			conditionObj = new CIFast_IFast_ifastcbo_err_net_unit_percent_not_allow();
			break;
		case 1701160: /* ERR_NET_UNIT_PURCHASE_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_net_unit_purchase_not_allowed();
			break;
		case 1701161: /* ERR_NET_UNIT_REDEEM_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_net_unit_redeem_not_allowed();
			break;
		case 1701162: /* ERR_NETWORKID_NOT_VALID_FOR_MANUAL_TRADES */
			conditionObj = new CIFast_IFast_ifastcbo_err_networkid_not_valid_for_manual_trades();
			break;
		case 1701163: /* ERR_NEW_ACCT_TERM_AND_DEL */
			conditionObj = new CIFast_IFast_ifastcbo_err_new_acct_term_and_del();
			break;
		case 1701164: /* ERR_NEW_ARCH_TRAILER_FEE */
			conditionObj = new CIFast_IFast_ifastcbo_err_new_arch_trailer_fee();
			break;
		case 1701165: /* ERR_NEW_SPLIT_PERIOD_OVERLAPS */
			conditionObj = new CIFast_IFast_ifastcbo_err_new_split_period_overlaps();
			break;
		case 1701166: /* ERR_NEXT_PROC_DATE_COMPARE_LAST_RUN_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_next_proc_date_compare_last_run_date();
			break;
		case 1701167: /* ERR_NEXT_REB_DATE_CANNOT_EARLIER_THAN_EFFECTIVE_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_next_reb_date_cannot_earlier_than_effective_date();
			break;
		case 1701168: /* ERR_NEXT_REB_DATE_CHANGED */
			conditionObj = new CIFast_IFast_ifastcbo_err_next_reb_date_changed();
			break;
		case 1701169: /* ERR_NO_ACCT_OWNER */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_acct_owner();
			break;
		case 1701170: /* ERR_NO_ACTIVE_BATCH */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_active_batch();
			break;
		case 1701171: /* ERR_NO_ADDRESSES_FOR_THIS_SHAREHOLDER */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_addresses_for_this_shareholder();
			break;
		case 1701172: /* ERR_NO_ALLOC_SYSTEMATIC_ON_CLAN_PLAN */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_alloc_systematic_on_clan_plan();
			break;
		case 1701173: /* ERR_NO_ALLOCATION_SETUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_allocation_setup();
			break;
		case 1701174: /* ERR_NO_ALLOWED_FOR_AS_PENSION_PLAN */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_allowed_for_as_pension_plan();
			break;
		case 1701175: /* ERR_NO_APPLICATBLE_FOR_TOFUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_applicatble_for_tofund();
			break;
		case 1701176: /* ERR_NO_BANKING_RECORDS_FOR_PAYMENT_FOR */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_banking_records_for_payment_for();
			break;
		case 1701177: /* ERR_NO_BANKING_RECORDS_FOR_PAYMENT_FOR_AND_CURRENCY */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_banking_records_for_payment_for_and_currency();
			break;
		case 1701178: /* ERR_NO_BROKER_INTER_ADDRESS */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_broker_inter_address();
			break;
		case 1701179: /* ERR_NO_CONTRACT_AVAILABLE_TO_SHAAREHOLDER_GROUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_contract_available_to_shaareholder_group();
			break;
		case 1701180: /* ERR_NO_CURRENY */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_curreny();
			break;
		case 1701181: /* ERR_NO_DATE_OF_BIRTH */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_date_of_birth();
			break;
		case 1701182: /* ERR_NO_DIVTYPE_UNIT_RATE_EXISTS_FOR_THIS_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_divtype_unit_rate_exists_for_this_date();
			break;
		case 1701183: /* ERR_NO_DOFDEATH_FOR_SHAREHOLDER */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_dofdeath_for_shareholder();
			break;
		case 1701184: /* ERR_NO_EMAIL_ADDRESS */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_email_address();
			break;
		case 1701185: /* ERR_NO_EMAIL_ADDRESS_FOR_ENTITY */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_email_address_for_entity();
			break;
		case 1701186: /* ERR_NO_FAX_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_fax_available();
			break;
		case 1701187: /* ERR_NO_FAX_AVAILABLE_FOR_ENTITY */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_fax_available_for_entity();
			break;
		case 1701188: /* ERR_NO_FUNDS_FOR_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_funds_for_account();
			break;
		case 1701189: /* ERR_NO_HOLD_FOR_RETURN_MAIL */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_hold_for_return_mail();
			break;
		case 1701190: /* ERR_NO_HOLDINGS_FOR_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_holdings_for_date();
			break;
		case 1701191: /* ERR_NO_INVESTMENT_SETUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_investment_setup();
			break;
		case 1701192: /* ERR_NO_LIFETIME_CONTRIB_LIMIT_SET_UP */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_lifetime_contrib_limit_set_up();
			break;
		case 1701193: /* ERR_NO_MAIL_TO_SUPPRESS */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_mail_to_suppress();
			break;
		case 1701194: /* ERR_NO_MATCHING_BIC_CODE_FOUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_matching_bic_code_found();
			break;
		case 1701195: /* ERR_NO_ONE_EQUAL_TO_BROKER_CODE */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_one_equal_to_broker_code();
			break;
		case 1701196: /* ERR_NO_ORIGINATING_CONTRIBUTION_SELECTED */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_originating_contribution_selected();
			break;
		case 1701197: /* ERR_NO_PAYMENT_INSTRUCTIONS_RECORD */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_payment_instructions_record();
			break;
		case 1701198: /* ERR_NO_PENSION_INFO */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_pension_info();
			break;
		case 1701199: /* ERR_NO_PENSION_INFORMATION */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_pension_information();
			break;
		case 1701200: /* ERR_NO_RA_MATCHING_TT */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_ra_matching_tt();
			break;
		case 1701201: /* ERR_NO_RA_SELECTED */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_ra_selected();
			break;
		case 1701202: /* ERR_NO_RESP_BENEFICIARY_SELECTED */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_resp_beneficiary_selected();
			break;
		case 1701203: /* ERR_NO_SALES_REP_EXISTS */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_sales_rep_exists();
			break;
		case 1701204: /* ERR_NO_TAX_TYPE_RULES */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_tax_type_rules();
			break;
		case 1701205: /* ERR_NO_TAXTYPE_RULE */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_taxtype_rule();
			break;
		case 1701206: /* ERR_NO_VALID_CONTRACT_FOR_ORIGINAL_TRADE_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_valid_contract_for_original_trade_date();
			break;
		case 1701207: /* ERR_NO_VALID_DECIMAL_VALUE */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_valid_decimal_value();
			break;
		case 1701208: /* ERR_NO_VALID_FUND_ALLOC_RECORD */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_valid_fund_alloc_record();
			break;
		case 1701209: /* ERR_NO_VALUE_FOR_ID */
			conditionObj = new CIFast_IFast_ifastcbo_err_no_value_for_id();
			break;
		case 1701210: /* ERR_NOMINEE_ENTITY_INUSE */
			conditionObj = new CIFast_IFast_ifastcbo_err_nominee_entity_inuse();
			break;
		case 1701211: /* ERR_NOMINEE_INVALID_FOR_ACCT_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_nominee_invalid_for_acct_type();
			break;
		case 1701212: /* ERR_NOMINEE_OWNER_ENTITY_MUST_BE_SETUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_nominee_owner_entity_must_be_setup();
			break;
		case 1701213: /* ERR_NOMINEE_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_nominee_required();
			break;
		case 1701214: /* ERR_NON_AMS_FUND_INELIGIBLE_FOR_AMS_REBALANCING */
			conditionObj = new CIFast_IFast_ifastcbo_err_non_ams_fund_ineligible_for_ams_rebalancing();
			break;
		case 1701215: /* ERR_NON_ASSOCIATED_BENEF_IS_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_non_associated_benef_is_not_allowed();
			break;
		case 1701216: /* ERR_NON_BUSINESS_DAY_FOR_DEAL_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_non_business_day_for_deal_date();
			break;
		case 1701217: /* ERR_NON_HOUSE_BROKER_CAN_NOT_DO_DIRECT_TRADING */
			conditionObj = new CIFast_IFast_ifastcbo_err_non_house_broker_can_not_do_direct_trading();
			break;
		case 1701218: /* ERR_NON_RECEIPT_FLAG_ACTIVE */
			conditionObj = new CIFast_IFast_ifastcbo_err_non_receipt_flag_active();
			break;
		case 1701219: /* ERR_NON_RESIDENT_TAX_JURID */
			conditionObj = new CIFast_IFast_ifastcbo_err_non_resident_tax_jurid();
			break;
		case 1701220: /* ERR_NON_RESIDENT_TAX_JURISD_STOP_PAC */
			conditionObj = new CIFast_IFast_ifastcbo_err_non_resident_tax_jurisd_stop_pac();
			break;
		case 1701221: /* ERR_NON_TRUSTEE_UPDATE_HIST_INFO_REQ */
			conditionObj = new CIFast_IFast_ifastcbo_err_non_trustee_update_hist_info_req();
			break;
		case 1701222: /* ERR_NONRES_EXCHANGE_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_nonres_exchange_not_allowed();
			break;
		case 1701223: /* ERR_NONTRUSTEE_GRANT_REQ_NOT_AVAIL_IN_TAXYEAR */
			conditionObj = new CIFast_IFast_ifastcbo_err_nontrustee_grant_req_not_avail_in_taxyear();
			break;
		case 1701224: /* ERR_NOT_A_RIF_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_not_a_rif_account();
			break;
		case 1701225: /* ERR_NOT_A_VALID_STATUS */
			conditionObj = new CIFast_IFast_ifastcbo_err_not_a_valid_status();
			break;
		case 1701226: /* ERR_NOT_APPLICABLE_DEPTYPE_REDCODE */
			conditionObj = new CIFast_IFast_ifastcbo_err_not_applicable_deptype_redcode();
			break;
		case 1701227: /* ERR_NOT_BACKDATED_NO_HOLDINGS */
			conditionObj = new CIFast_IFast_ifastcbo_err_not_backdated_no_holdings();
			break;
		case 1701228: /* ERR_NOT_CONF_FOR_REBALANCING */
			conditionObj = new CIFast_IFast_ifastcbo_err_not_conf_for_rebalancing();
			break;
		case 1701229: /* ERR_NOT_ENOUGH_GRANT_AMOUNT_FOR_RETURN */
			conditionObj = new CIFast_IFast_ifastcbo_err_not_enough_grant_amount_for_return();
			break;
		case 1701230: /* ERR_NOT_IN_ALLOWABLE_TRANSFER */
			conditionObj = new CIFast_IFast_ifastcbo_err_not_in_allowable_transfer();
			break;
		case 1701231: /* ERR_NOT_IWT_TAX_JURIS */
			conditionObj = new CIFast_IFast_ifastcbo_err_not_iwt_tax_juris();
			break;
		case 1701232: /* ERR_NS_DUPLICATE_BICCODE */
			conditionObj = new CIFast_IFast_ifastcbo_err_ns_duplicate_biccode();
			break;
		case 1701233: /* ERR_NSCC_CURRENCY_INVALID */
			conditionObj = new CIFast_IFast_ifastcbo_err_nscc_currency_invalid();
			break;
		case 1701234: /* ERR_NSM_SETTLE_VALUE_IS_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_nsm_settle_value_is_not_allowed();
			break;
		case 1701235: /* ERR_NUMBER_SIN */
			conditionObj = new CIFast_IFast_ifastcbo_err_number_sin();
			break;
		case 1701236: /* ERR_NUMERIC_BANKIDNUM */
			conditionObj = new CIFast_IFast_ifastcbo_err_numeric_bankidnum();
			break;
		case 1701237: /* ERR_OBJECT_NOT_INITIALIZED */
			conditionObj = new CIFast_IFast_ifastcbo_err_object_not_initialized();
			break;
		case 1701238: /* ERR_OCCUPATION_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_occupation_required();
			break;
		case 1701239: /* ERR_OFFSET_CUTOFFTIME_LATER_THAN_MARKET_CUTOFFTIME */
			conditionObj = new CIFast_IFast_ifastcbo_err_offset_cutofftime_later_than_market_cutofftime();
			break;
		case 1701240: /* ERR_OLDEST_LEGAL_DATE_CANNOT_BE_IN_THE_PAST */
			conditionObj = new CIFast_IFast_ifastcbo_err_oldest_legal_date_cannot_be_in_the_past();
			break;
		case 1701241: /* ERR_ONE_COMPENSATION_AGENT_IS_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_one_compensation_agent_is_allowed();
			break;
		case 1701242: /* ERR_ONE_FS_ALT_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_one_fs_alt_account();
			break;
		case 1701243: /* ERR_ONE_FS_WHERE_USE */
			conditionObj = new CIFast_IFast_ifastcbo_err_one_fs_where_use();
			break;
		case 1701244: /* ERR_ONE_REMAININGFLAG_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_one_remainingflag_required();
			break;
		case 1701245: /* ERR_ONE_RESP_BENEF_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_one_resp_benef_allowed();
			break;
		case 1701246: /* ERR_ONEGI_MULTIPLESEGS_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_onegi_multiplesegs_allowed();
			break;
		case 1701247: /* ERR_ONLY_10_CHARATERS_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_only_10_charaters_allowed();
			break;
		case 1701248: /* ERR_ONLY_20_CHARATERS_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_only_20_charaters_allowed();
			break;
		case 1701249: /* ERR_ONLY_EXCLUDE_MCH_FOR_THIRDPARTYFUNDS */
			conditionObj = new CIFast_IFast_ifastcbo_err_only_exclude_mch_for_thirdpartyfunds();
			break;
		case 1701250: /* ERR_ONLY_GIC_PURCHASES_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_only_gic_purchases_allowed();
			break;
		case 1701251: /* ERR_ONLY_NSCC_PAYTYPE_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_only_nscc_paytype_allowed();
			break;
		case 1701252: /* ERR_ONLY_ONE_ACCOUNT_OWNER_ENTITY_IS_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_only_one_account_owner_entity_is_allowed();
			break;
		case 1701253: /* ERR_ONLY_ONE_ACTIVE_RECORD_NR301 */
			conditionObj = new CIFast_IFast_ifastcbo_err_only_one_active_record_nr301();
			break;
		case 1701254: /* ERR_ONLY_ONE_ACTIVE_RECORD_NR301_NO */
			conditionObj = new CIFast_IFast_ifastcbo_err_only_one_active_record_nr301_no();
			break;
		case 1701255: /* ERR_ONLY_ONE_ACTIVE_RECORD_NR301_NO_AND_NR301 */
			conditionObj = new CIFast_IFast_ifastcbo_err_only_one_active_record_nr301_no_and_nr301();
			break;
		case 1701256: /* ERR_ONLY_ONE_CATEGORY */
			conditionObj = new CIFast_IFast_ifastcbo_err_only_one_category();
			break;
		case 1701257: /* ERR_ONLY_ONE_GIA_FUND_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_only_one_gia_fund_allowed();
			break;
		case 1701258: /* ERR_ONLY_ONE_PARENT_ENTITY_IS_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_only_one_parent_entity_is_allowed();
			break;
		case 1701259: /* ERR_ONLY_PAY_TO_ENTITY_PAYTYPE_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_only_pay_to_entity_paytype_allowed();
			break;
		case 1701260: /* ERR_ONLY_RESP_CAN_HAVE_CORPORATE_AS_ACCOUNTHOLDER */
			conditionObj = new CIFast_IFast_ifastcbo_err_only_resp_can_have_corporate_as_accountholder();
			break;
		case 1701261: /* ERR_ONLY_UNIT_ALLOW_FOR_BEARER_CERTIFICATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_only_unit_allow_for_bearer_certificate();
			break;
		case 1701262: /* ERR_ONLY_WHOLE_UNITS_ALLOWED_FOR_BEARER_CERTS */
			conditionObj = new CIFast_IFast_ifastcbo_err_only_whole_units_allowed_for_bearer_certs();
			break;
		case 1701263: /* ERR_ONLY_WRONG_INSTRUCTIONTYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_only_wrong_instructiontype();
			break;
		case 1701264: /* ERR_ORDER_SRC_INVALID_FOR_WIRE_ORDER */
			conditionObj = new CIFast_IFast_ifastcbo_err_order_src_invalid_for_wire_order();
			break;
		case 1701265: /* ERR_ORDER_SRC_MUST_BE_I_FOR_INTERMEDIARY */
			conditionObj = new CIFast_IFast_ifastcbo_err_order_src_must_be_i_for_intermediary();
			break;
		case 1701266: /* ERR_ORDERSRC_INVALID_FOR_WIRE_ORDER */
			conditionObj = new CIFast_IFast_ifastcbo_err_ordersrc_invalid_for_wire_order();
			break;
		case 1701267: /* ERR_ORDERSRC_MUST_BE_INTERMEDIARY */
			conditionObj = new CIFast_IFast_ifastcbo_err_ordersrc_must_be_intermediary();
			break;
		case 1701268: /* ERR_ORDERTYPE_DIRECT */
			conditionObj = new CIFast_IFast_ifastcbo_err_ordertype_direct();
			break;
		case 1701269: /* ERR_ORDERTYPE_MUST_BE_DIRECT */
			conditionObj = new CIFast_IFast_ifastcbo_err_ordertype_must_be_direct();
			break;
		case 1701270: /* ERR_ORDERTYPE_WIRE */
			conditionObj = new CIFast_IFast_ifastcbo_err_ordertype_wire();
			break;
		case 1701271: /* ERR_OTHER_ENTITY_TYPE_MUST_BE_SETUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_other_entity_type_must_be_setup();
			break;
		case 1701272: /* ERR_OVERRIDE_IS_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_override_is_not_allowed();
			break;
		case 1701273: /* ERR_PAC_LESS_THAN_MINIMUM_ALLOW */
			conditionObj = new CIFast_IFast_ifastcbo_err_pac_less_than_minimum_allow();
			break;
		case 1701274: /* ERR_PAC_STOP_DATE_RESTRICTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_pac_stop_date_restriction();
			break;
		case 1701275: /* ERR_PAC_SWP_ALLOCATION_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_pac_swp_allocation_required();
			break;
		case 1701276: /* ERR_PAC_SWP_UNITS_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_pac_swp_units_not_allowed();
			break;
		case 1701277: /* ERR_PAC_UNITS_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_pac_units_not_allowed();
			break;
		case 1701278: /* ERR_PARENT_ENTITY_SHOULD_BE_SETUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_parent_entity_should_be_setup();
			break;
		case 1701279: /* ERR_PARENT_FUND_CLASS_CANNOT_BE_A_PART_OF_ASSET_ALLOCATION_MIX */
			conditionObj = new CIFast_IFast_ifastcbo_err_parent_fund_class_cannot_be_a_part_of_asset_allocation_mix();
			break;
		case 1701280: /* ERR_PARENT_FUND_CLASS_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_parent_fund_class_required();
			break;
		case 1701281: /* ERR_PARENT_HAS_NOT_BEEN_SETUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_parent_has_not_been_setup();
			break;
		case 1701282: /* ERR_PARTIAL_TRANSFER_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_partial_transfer_not_allowed();
			break;
		case 1701283: /* ERR_PARTICIPANTID_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_participantid_missing();
			break;
		case 1701284: /* ERR_PAY_ENTITY_BANK_NOT_VERIFY */
			conditionObj = new CIFast_IFast_ifastcbo_err_pay_entity_bank_not_verify();
			break;
		case 1701285: /* ERR_PAY_OUT_ADDR_MUST_BE_EQUAL_TO */
			conditionObj = new CIFast_IFast_ifastcbo_err_pay_out_addr_must_be_equal_to();
			break;
		case 1701286: /* ERR_PAYINS_SHOULD_BE_EFT */
			conditionObj = new CIFast_IFast_ifastcbo_err_payins_should_be_eft();
			break;
		case 1701287: /* ERR_PAYMENT_BELOW_MIN */
			conditionObj = new CIFast_IFast_ifastcbo_err_payment_below_min();
			break;
		case 1701288: /* ERR_PAYMENT_INSTRUCTION_FOR_BULK_DISTRIBUTION_EXIST */
			conditionObj = new CIFast_IFast_ifastcbo_err_payment_instruction_for_bulk_distribution_exist();
			break;
		case 1701289: /* ERR_PAYMENT_INSTRUCTION_FOR_BULK_REDEMPTION_EXIST */
			conditionObj = new CIFast_IFast_ifastcbo_err_payment_instruction_for_bulk_redemption_exist();
			break;
		case 1701290: /* ERR_PAYMENT_INSTRUCTION_FOR_INDIVIDUAL_DISTRIBUTION_EXIST */
			conditionObj = new CIFast_IFast_ifastcbo_err_payment_instruction_for_individual_distribution_exist();
			break;
		case 1701291: /* ERR_PAYMENT_INSTRUCTION_FOR_INDIVIDUAL_REDEMPTION_EXIST */
			conditionObj = new CIFast_IFast_ifastcbo_err_payment_instruction_for_individual_redemption_exist();
			break;
		case 1701292: /* ERR_PAYMENT_STATUS_EMPTY */
			conditionObj = new CIFast_IFast_ifastcbo_err_payment_status_empty();
			break;
		case 1701293: /* ERR_PAYMENT_STATUS_IS_OUTSTANDING */
			conditionObj = new CIFast_IFast_ifastcbo_err_payment_status_is_outstanding();
			break;
		case 1701294: /* ERR_PAYTYPE_FROM_EFT_TO_CHQ_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_paytype_from_eft_to_chq_not_allowed();
			break;
		case 1701295: /* ERR_PAYTYPE_NOT_AVAIL_FOR_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_paytype_not_avail_for_fund();
			break;
		case 1701296: /* ERR_PCG_INST_BUSINESS_NUMBER_INVALID */
			conditionObj = new CIFast_IFast_ifastcbo_err_pcg_inst_business_number_invalid();
			break;
		case 1701297: /* ERR_PCG_INST_BUSINESS_NUMBER_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_pcg_inst_business_number_missing();
			break;
		case 1701298: /* ERR_PCG_MISSING_FOR_RESP_ACCOUNTHOLDER */
			conditionObj = new CIFast_IFast_ifastcbo_err_pcg_missing_for_resp_accountholder();
			break;
		case 1701299: /* ERR_PCG_REQURIED_FOR_COPORATE_RESP_ACCT_HOLDER */
			conditionObj = new CIFast_IFast_ifastcbo_err_pcg_requried_for_coporate_resp_acct_holder();
			break;
		case 1701300: /* ERR_PENDING_OR_UNSETTLED_TRADE_EXISTS */
			conditionObj = new CIFast_IFast_ifastcbo_err_pending_or_unsettled_trade_exists();
			break;
		case 1701301: /* ERR_PENDING_TRADES_WITH_AMS */
			conditionObj = new CIFast_IFast_ifastcbo_err_pending_trades_with_ams();
			break;
		case 1701302: /* ERR_PENSION_DISTINCTSEX_PERCENT_MUST_EQ_100 */
			conditionObj = new CIFast_IFast_ifastcbo_err_pension_distinctsex_percent_must_eq_100();
			break;
		case 1701303: /* ERR_PENSION_INVALID_PERCENT */
			conditionObj = new CIFast_IFast_ifastcbo_err_pension_invalid_percent();
			break;
		case 1701304: /* ERR_PENSION_JURIS_IS_MANDATORY */
			conditionObj = new CIFast_IFast_ifastcbo_err_pension_juris_is_mandatory();
			break;
		case 1701305: /* ERR_PENSION_SEX_PRCNT_NOT_ADD_TO_100 */
			conditionObj = new CIFast_IFast_ifastcbo_err_pension_sex_prcnt_not_add_to_100();
			break;
		case 1701306: /* ERR_PENSION_TAX_RULE_NOT_SETUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_pension_tax_rule_not_setup();
			break;
		case 1701307: /* ERR_PENSION_UNISEX_PERCENT_MUST_EQ_100 */
			conditionObj = new CIFast_IFast_ifastcbo_err_pension_unisex_percent_must_eq_100();
			break;
		case 1701308: /* ERR_PENSIONJURIS_TAXTYPE_NOT_PERMITTED */
			conditionObj = new CIFast_IFast_ifastcbo_err_pensionjuris_taxtype_not_permitted();
			break;
		case 1701309: /* ERR_PERCENT_VALUE_INVALID */
			conditionObj = new CIFast_IFast_ifastcbo_err_percent_value_invalid();
			break;
		case 1701310: /* ERR_PERCENTAGE_HOLDINGS_NOT_MORE_THAN_100 */
			conditionObj = new CIFast_IFast_ifastcbo_err_percentage_holdings_not_more_than_100();
			break;
		case 1701311: /* ERR_PERCENTAGE_HOLDINGS_OVER_100 */
			conditionObj = new CIFast_IFast_ifastcbo_err_percentage_holdings_over_100();
			break;
		case 1701312: /* ERR_PERCENTAGE_LESS_THAN_100 */
			conditionObj = new CIFast_IFast_ifastcbo_err_percentage_less_than_100();
			break;
		case 1701313: /* ERR_PERCENTAGE_NOT_EQUAL_100 */
			conditionObj = new CIFast_IFast_ifastcbo_err_percentage_not_equal_100();
			break;
		case 1701314: /* ERR_PHONENUM_ALREADY_EXIST */
			conditionObj = new CIFast_IFast_ifastcbo_err_phonenum_already_exist();
			break;
		case 1701315: /* ERR_PI_DATES_NOT_WITHIN_PE_DATES */
			conditionObj = new CIFast_IFast_ifastcbo_err_pi_dates_not_within_pe_dates();
			break;
		case 1701316: /* ERR_PLAN_TYPE_DONT_MATCH_FOR_IN_KIND_TRANS */
			conditionObj = new CIFast_IFast_ifastcbo_err_plan_type_dont_match_for_in_kind_trans();
			break;
		case 1701317: /* ERR_PLAN_TYPE_MUST_BE_SAME */
			conditionObj = new CIFast_IFast_ifastcbo_err_plan_type_must_be_same();
			break;
		case 1701318: /* ERR_PLAN_TYPE_MUST_SAME_IN_KIND_TRANS */
			conditionObj = new CIFast_IFast_ifastcbo_err_plan_type_must_same_in_kind_trans();
			break;
		case 1701319: /* ERR_PLANHOLDER_MAXIMUM_AGE_LIMIT */
			conditionObj = new CIFast_IFast_ifastcbo_err_planholder_maximum_age_limit();
			break;
		case 1701320: /* ERR_PLANHOLDER_MINIMUM_AGE_LIMIT */
			conditionObj = new CIFast_IFast_ifastcbo_err_planholder_minimum_age_limit();
			break;
		case 1701321: /* ERR_PRCPOSTER_SAME_AS_PRCLOADER */
			conditionObj = new CIFast_IFast_ifastcbo_err_prcposter_same_as_prcloader();
			break;
		case 1701322: /* ERR_PRE_PERCENT_IN_BETWEEN */
			conditionObj = new CIFast_IFast_ifastcbo_err_pre_percent_in_between();
			break;
		case 1701323: /* ERR_PRE_YR_PERCENT */
			conditionObj = new CIFast_IFast_ifastcbo_err_pre_yr_percent();
			break;
		case 1701324: /* ERR_PRICE_CANNOT_BE_ZERO */
			conditionObj = new CIFast_IFast_ifastcbo_err_price_cannot_be_zero();
			break;
		case 1701325: /* ERR_PRICETYPE_DOESNOT_MATCH */
			conditionObj = new CIFast_IFast_ifastcbo_err_pricetype_doesnot_match();
			break;
		case 1701326: /* ERR_PRIMARY_BENEF_PERCENT_SHOULD_ADD_UP_TO_100 */
			conditionObj = new CIFast_IFast_ifastcbo_err_primary_benef_percent_should_add_up_to_100();
			break;
		case 1701327: /* ERR_PRIVATE_ACCOUNT_ACTEGORY_ONLY_FOR_CLIENT */
			conditionObj = new CIFast_IFast_ifastcbo_err_private_account_actegory_only_for_client();
			break;
		case 1701328: /* ERR_PROD_PORTFOLIO_RELATED_FIELDS_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_prod_portfolio_related_fields_required();
			break;
		case 1701329: /* ERR_PROVINCE_BLANK_FOR_USA */
			conditionObj = new CIFast_IFast_ifastcbo_err_province_blank_for_usa();
			break;
		case 1701330: /* ERR_PROVINCE_IS_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_province_is_required();
			break;
		case 1701331: /* ERR_PSE_LEN_INVALID */
			conditionObj = new CIFast_IFast_ifastcbo_err_pse_len_invalid();
			break;
		case 1701332: /* ERR_PSE_TYPE_INVALID */
			conditionObj = new CIFast_IFast_ifastcbo_err_pse_type_invalid();
			break;
		case 1701333: /* ERR_PSE_YEAR_INVALID */
			conditionObj = new CIFast_IFast_ifastcbo_err_pse_year_invalid();
			break;
		case 1701334: /* ERR_PUEV_ENTRY_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_puev_entry_required();
			break;
		case 1701335: /* ERR_PURCH_NAV_ACCT_BEL_FUND_NAV_DEPOSIT_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_purch_nav_acct_bel_fund_nav_deposit_type();
			break;
		case 1701336: /* ERR_PURCH_STOPPED_FOR_PAC */
			conditionObj = new CIFast_IFast_ifastcbo_err_purch_stopped_for_pac();
			break;
		case 1701337: /* ERR_PURCHASE_INVALID_DEPOSIT_TYPE_FOR_ALLOC */
			conditionObj = new CIFast_IFast_ifastcbo_err_purchase_invalid_deposit_type_for_alloc();
			break;
		case 1701338: /* ERR_PURCHASE_NOT_ALLOWED_FOR_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_purchase_not_allowed_for_fund();
			break;
		case 1701339: /* ERR_PW_DIRECT_DPST_INTERESTED_FUND_SUB_CAT */
			conditionObj = new CIFast_IFast_ifastcbo_err_pw_direct_dpst_interested_fund_sub_cat();
			break;
		case 1701340: /* ERR_QESI_AMOUNT_GREATER_THAN_10_PRCNT_OF_EXISTING_QESI_UNASSISTED_AMOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_qesi_amount_greater_than_10_prcnt_of_existing_qesi_unassisted_amount();
			break;
		case 1701341: /* ERR_QESI_BASIC_LIMIT_EXCEEDED_FOR_YEAR */
			conditionObj = new CIFast_IFast_ifastcbo_err_qesi_basic_limit_exceeded_for_year();
			break;
		case 1701342: /* ERR_QESI_DP_RD_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_qesi_dp_rd_not_allowed();
			break;
		case 1701343: /* ERR_QESI_GRANT_REQUEST_NOT_AVAILABLE_FOR_BENEFICIARY */
			conditionObj = new CIFast_IFast_ifastcbo_err_qesi_grant_request_not_available_for_beneficiary();
			break;
		case 1701344: /* ERR_QESI_INCREASE_LIMIT_EXCEEDED_FOR_YEAR */
			conditionObj = new CIFast_IFast_ifastcbo_err_qesi_increase_limit_exceeded_for_year();
			break;
		case 1701345: /* ERR_QESI_LIFE_TIME_GRANT_LIMIT_EXCEEDED */
			conditionObj = new CIFast_IFast_ifastcbo_err_qesi_life_time_grant_limit_exceeded();
			break;
		case 1701346: /* ERR_QESI_LIMIT_EXCEEDED */
			conditionObj = new CIFast_IFast_ifastcbo_err_qesi_limit_exceeded();
			break;
		case 1701347: /* ERR_QESI_TOTAL_TRANSFER_FILED_IS_BLANK */
			conditionObj = new CIFast_IFast_ifastcbo_err_qesi_total_transfer_filed_is_blank();
			break;
		case 1701348: /* ERR_QUARTEREND_MATURITY_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_quarterend_maturity_date();
			break;
		case 1701349: /* ERR_RATE_IS_OUT_OF_RANGE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rate_is_out_of_range();
			break;
		case 1701350: /* ERR_RATE_LESS_THAN_MIN */
			conditionObj = new CIFast_IFast_ifastcbo_err_rate_less_than_min();
			break;
		case 1701351: /* ERR_RB_EFFECTIVEDATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rb_effectivedate();
			break;
		case 1701352: /* ERR_RB_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_rb_not_allowed();
			break;
		case 1701353: /* ERR_REASON_CODE_EMPTY */
			conditionObj = new CIFast_IFast_ifastcbo_err_reason_code_empty();
			break;
		case 1701354: /* ERR_REASONCODE_COLLATERAL */
			conditionObj = new CIFast_IFast_ifastcbo_err_reasoncode_collateral();
			break;
		case 1701355: /* ERR_REASONCODE_RRSP_LOAN */
			conditionObj = new CIFast_IFast_ifastcbo_err_reasoncode_rrsp_loan();
			break;
		case 1701356: /* ERR_REBALANCING_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_rebalancing_not_allowed();
			break;
		case 1701357: /* ERR_REBALANCING_STATUS */
			conditionObj = new CIFast_IFast_ifastcbo_err_rebalancing_status();
			break;
		case 1701358: /* ERR_RECIPIENT_TYPE_NOT_VALID_FOR_JURISDICTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_recipient_type_not_valid_for_jurisdiction();
			break;
		case 1701359: /* ERR_RECORD_VALUE_NOT_MATCH */
			conditionObj = new CIFast_IFast_ifastcbo_err_record_value_not_match();
			break;
		case 1701360: /* ERR_RED_AMT_MORE_THAN_HOLDING */
			conditionObj = new CIFast_IFast_ifastcbo_err_red_amt_more_than_holding();
			break;
		case 1701361: /* ERR_RED_CODE_40_CANNOT_BE_PLACED */
			conditionObj = new CIFast_IFast_ifastcbo_err_red_code_40_cannot_be_placed();
			break;
		case 1701362: /* ERR_RED_CODE_NOT_ALLOWED_FOR_ALLOCATED_TRADE */
			conditionObj = new CIFast_IFast_ifastcbo_err_red_code_not_allowed_for_allocated_trade();
			break;
		case 1701363: /* ERR_REDCODE_AND_TAXJURIS_DO_NOT_MATCH_FOR_BENEFICIARY */
			conditionObj = new CIFast_IFast_ifastcbo_err_redcode_and_taxjuris_do_not_match_for_beneficiary();
			break;
		case 1701364: /* ERR_REDCODE_APPLICABLE_CLIENT */
			conditionObj = new CIFast_IFast_ifastcbo_err_redcode_applicable_client();
			break;
		case 1701365: /* ERR_REDCODE_APPLICABLE_S3_S4 */
			conditionObj = new CIFast_IFast_ifastcbo_err_redcode_applicable_s3_s4();
			break;
		case 1701366: /* ERR_REDCODE_EMPTY */
			conditionObj = new CIFast_IFast_ifastcbo_err_redcode_empty();
			break;
		case 1701367: /* ERR_REDCODE_NOT_APPLICABLE_TO_STTRADING */
			conditionObj = new CIFast_IFast_ifastcbo_err_redcode_not_applicable_to_sttrading();
			break;
		case 1701368: /* ERR_REDEMP_CONTRARY_CLIENT_GUAGUARD_PROTECTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_redemp_contrary_client_guaguard_protection();
			break;
		case 1701369: /* ERR_REDEMP_STOPPED_FOR_SWP */
			conditionObj = new CIFast_IFast_ifastcbo_err_redemp_stopped_for_swp();
			break;
		case 1701370: /* ERR_REDEMPT_AMT_EXCEEDED_QESI_AMT_RECEIVED */
			conditionObj = new CIFast_IFast_ifastcbo_err_redempt_amt_exceeded_qesi_amt_received();
			break;
		case 1701371: /* ERR_REDEMPTION_AMOUNT_FOR_ADJUSTMENT_OF_QESI_BASIC_HAS_EXCEEDED */
			conditionObj = new CIFast_IFast_ifastcbo_err_redemption_amount_for_adjustment_of_qesi_basic_has_exceeded();
			break;
		case 1701372: /* ERR_REDEMPTION_AMOUNT_FOR_ADJUSTMENT_OF_QESI_INCREASE_HAS_EXCEEDED */
			conditionObj = new CIFast_IFast_ifastcbo_err_redemption_amount_for_adjustment_of_qesi_increase_has_exceeded();
			break;
		case 1701373: /* ERR_REDEMPTION_CODE_APPLICABLE_ONLY_FOR_NON_RESIDENT_BENEFICIARIES */
			conditionObj = new CIFast_IFast_ifastcbo_err_redemption_code_applicable_only_for_non_resident_beneficiaries();
			break;
		case 1701374: /* ERR_REDEMPTION_CODE_IS_INVALID_BENEFICIARY_IS_NON_RESIDENT */
			conditionObj = new CIFast_IFast_ifastcbo_err_redemption_code_is_invalid_beneficiary_is_non_resident();
			break;
		case 1701375: /* ERR_REDEMPTION_CODE_IS_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_redemption_code_is_not_allowed();
			break;
		case 1701376: /* ERR_REDEMPTION_CODE_RULES_NOT_SETUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_redemption_code_rules_not_setup();
			break;
		case 1701377: /* ERR_REDEMPTION_DEPOSIT_CODE_NOT_VALID */
			conditionObj = new CIFast_IFast_ifastcbo_err_redemption_deposit_code_not_valid();
			break;
		case 1701378: /* ERR_REDEMPTION_EXCEED_REMAINING_CONTRIB */
			conditionObj = new CIFast_IFast_ifastcbo_err_redemption_exceed_remaining_contrib();
			break;
		case 1701379: /* ERR_REDEMPTION_EXCEEDS_GRANT_PLUS_EARNINGS */
			conditionObj = new CIFast_IFast_ifastcbo_err_redemption_exceeds_grant_plus_earnings();
			break;
		case 1701380: /* ERR_REDEMPTION_FEE_SETUP_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_redemption_fee_setup_missing();
			break;
		case 1701381: /* ERR_REDEMPTION_SUPPRESS_CODE_INVALID_FOR_NON_CLEARING_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_redemption_suppress_code_invalid_for_non_clearing_account();
			break;
		case 1701382: /* ERR_REDEMPTION_SUPPRESS_CODE_INVALID_FOR_NON_CLEARING_PAY_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_redemption_suppress_code_invalid_for_non_clearing_pay_type();
			break;
		case 1701383: /* ERR_REDEMPTION_SUPPRESS_CODE_MUST_BE_CLEARING_FOR_CLEARING_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_redemption_suppress_code_must_be_clearing_for_clearing_account();
			break;
		case 1701384: /* ERR_REDEMPTION_TOTAL_TAX_RATE_GREATER_THAN_100 */
			conditionObj = new CIFast_IFast_ifastcbo_err_redemption_total_tax_rate_greater_than_100();
			break;
		case 1701385: /* ERR_REDIRECT_TO_PAY_ENTITY_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_redirect_to_pay_entity_not_allowed();
			break;
		case 1701386: /* ERR_REDIRECT_TO_REG_AGENT_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_redirect_to_reg_agent_not_allowed();
			break;
		case 1701387: /* ERR_REDIRECTING_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_redirecting_not_allowed();
			break;
		case 1701388: /* ERR_REFERENCE_NO_IS_MANDATORY_FOR_SOURCE_OF_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_reference_no_is_mandatory_for_source_of_fund();
			break;
		case 1701389: /* ERR_REFNUMBER_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastcbo_err_refnumber_not_exist();
			break;
		case 1701390: /* ERR_REFUND_OF_SPECIAL_TAXES_EXCEED_REDEMPTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_refund_of_special_taxes_exceed_redemption();
			break;
		case 1701391: /* ERR_REG_ADDRESS_CODE_IS_NOT_APPLICABLE_FOR_ADDRESSCODE */
			conditionObj = new CIFast_IFast_ifastcbo_err_reg_address_code_is_not_applicable_for_addresscode();
			break;
		case 1701392: /* ERR_REG_ADDRESS_CODE_IS_NOT_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastcbo_err_reg_address_code_is_not_available();
			break;
		case 1701393: /* ERR_REG_ADDRESS_CODE_IS_NOT_BLANK */
			conditionObj = new CIFast_IFast_ifastcbo_err_reg_address_code_is_not_blank();
			break;
		case 1701394: /* ERR_REG_AGENT_NOT_ASSOCIATED */
			conditionObj = new CIFast_IFast_ifastcbo_err_reg_agent_not_associated();
			break;
		case 1701395: /* ERR_REG_AGENT_TAX_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_reg_agent_tax_type();
			break;
		case 1701396: /* ERR_REGAGENT_BANKING_UNAVILABLE */
			conditionObj = new CIFast_IFast_ifastcbo_err_regagent_banking_unavilable();
			break;
		case 1701397: /* ERR_REGISTER_ADDRESS_FOR_BROKER_CANNOT_BE_CHANGED */
			conditionObj = new CIFast_IFast_ifastcbo_err_register_address_for_broker_cannot_be_changed();
			break;
		case 1701398: /* ERR_REGULAR_ACQ_FEE_OPTION_DOES_NOT_APPLY */
			conditionObj = new CIFast_IFast_ifastcbo_err_regular_acq_fee_option_does_not_apply();
			break;
		case 1701399: /* ERR_REGULATORY_DOC_STATUS_NEEDS_TO_BE_MANUALLY_UPDATED */
			conditionObj = new CIFast_IFast_ifastcbo_err_regulatory_doc_status_needs_to_be_manually_updated();
			break;
		case 1701400: /* ERR_REINVESTMENT_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_reinvestment_not_allowed();
			break;
		case 1701401: /* ERR_RELATE_CODE_EMPTY */
			conditionObj = new CIFast_IFast_ifastcbo_err_relate_code_empty();
			break;
		case 1701402: /* ERR_RELATE_CODE_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_relate_code_required();
			break;
		case 1701403: /* ERR_RELATIONSHIP_IDVALUE_NOT_CONSISTENT */
			conditionObj = new CIFast_IFast_ifastcbo_err_relationship_idvalue_not_consistent();
			break;
		case 1701404: /* ERR_REMAIN_ACCT_BALANCE */
			conditionObj = new CIFast_IFast_ifastcbo_err_remain_acct_balance();
			break;
		case 1701405: /* ERR_REMAIN_AMOUNT_MUSTBE_PAID */
			conditionObj = new CIFast_IFast_ifastcbo_err_remain_amount_mustbe_paid();
			break;
		case 1701406: /* ERR_REMOVE_SPOUSE_LINK_BEFORE_DELETE_OWNER */
			conditionObj = new CIFast_IFast_ifastcbo_err_remove_spouse_link_before_delete_owner();
			break;
		case 1701407: /* ERR_REP_BY_BRANCH_CFG */
			conditionObj = new CIFast_IFast_ifastcbo_err_rep_by_branch_cfg();
			break;
		case 1701408: /* ERR_REPORTING_FFI_IS_REQURIED */
			conditionObj = new CIFast_IFast_ifastcbo_err_reporting_ffi_is_requried();
			break;
		case 1701409: /* ERR_REQ_FIELD_EMPTY */
			conditionObj = new CIFast_IFast_ifastcbo_err_req_field_empty();
			break;
		case 1701410: /* ERR_REQUIRED_FUND_CODE_FOR_ACCT_CATEGORY_FUND_ON_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_required_fund_code_for_acct_category_fund_on_fund();
			break;
		case 1701411: /* ERR_REQUIRED_NEW_GRANT_REQUEST_FOR_TAX_YEAR */
			conditionObj = new CIFast_IFast_ifastcbo_err_required_new_grant_request_for_tax_year();
			break;
		case 1701412: /* ERR_REQUIRED_TO_STOP_GRANT_REQUEST_FOR_TAX_YEAR */
			conditionObj = new CIFast_IFast_ifastcbo_err_required_to_stop_grant_request_for_tax_year();
			break;
		case 1701413: /* ERR_RESET_DATE_LATER_CUR_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_reset_date_later_cur_date();
			break;
		case 1701414: /* ERR_RESET_DONE */
			conditionObj = new CIFast_IFast_ifastcbo_err_reset_done();
			break;
		case 1701415: /* ERR_RESET_ENTITY_EXCEED_AGE_LIMIT */
			conditionObj = new CIFast_IFast_ifastcbo_err_reset_entity_exceed_age_limit();
			break;
		case 1701416: /* ERR_RESET_EXCEED_MAX */
			conditionObj = new CIFast_IFast_ifastcbo_err_reset_exceed_max();
			break;
		case 1701417: /* ERR_RESET_HAS_OCCURED */
			conditionObj = new CIFast_IFast_ifastcbo_err_reset_has_occured();
			break;
		case 1701418: /* ERR_RESET_OVERRIDE_IS_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_reset_override_is_not_allowed();
			break;
		case 1701419: /* ERR_RESIDENCE_PROVINCE_EMPTY */
			conditionObj = new CIFast_IFast_ifastcbo_err_residence_province_empty();
			break;
		case 1701420: /* ERR_RESP_ACCOUNT_INFO_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_resp_account_info_missing();
			break;
		case 1701421: /* ERR_RESP_BENEF_ALLOCATIONS_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_resp_benef_allocations_missing();
			break;
		case 1701422: /* ERR_RESP_BENEF_IS_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_resp_benef_is_missing();
			break;
		case 1701423: /* ERR_RESP_BENEF_OVER21 */
			conditionObj = new CIFast_IFast_ifastcbo_err_resp_benef_over21();
			break;
		case 1701424: /* ERR_RESP_BENEF_OVER31 */
			conditionObj = new CIFast_IFast_ifastcbo_err_resp_benef_over31();
			break;
		case 1701425: /* ERR_RESP_BENEF_REASON_CANNOT_BE_MODIFIED */
			conditionObj = new CIFast_IFast_ifastcbo_err_resp_benef_reason_cannot_be_modified();
			break;
		case 1701426: /* ERR_RESP_BENEF_REASON_MUST_BE_CURRENT_BENEF_FOR_NEW_ENTITY */
			conditionObj = new CIFast_IFast_ifastcbo_err_resp_benef_reason_must_be_current_benef_for_new_entity();
			break;
		case 1701427: /* ERR_RESP_BENEFICIARY_ENTITY_IS_NOT_ALLOWED_FOR_THIS_TAX_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_resp_beneficiary_entity_is_not_allowed_for_this_tax_type();
			break;
		case 1701428: /* ERR_RESP_BENEFICIARY_ENTITY_MUST_BE_SETUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_resp_beneficiary_entity_must_be_setup();
			break;
		case 1701429: /* ERR_RESP_BENEFICIARY_SIN_INVALID */
			conditionObj = new CIFast_IFast_ifastcbo_err_resp_beneficiary_sin_invalid();
			break;
		case 1701430: /* ERR_RESP_BENEFICIARY_SIN_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_resp_beneficiary_sin_missing();
			break;
		case 1701431: /* ERR_RESP_DATE_MUST_BE_12319999 */
			conditionObj = new CIFast_IFast_ifastcbo_err_resp_date_must_be_12319999();
			break;
		case 1701432: /* ERR_RESP_DATE_MUST_BE_ENTERED */
			conditionObj = new CIFast_IFast_ifastcbo_err_resp_date_must_be_entered();
			break;
		case 1701433: /* ERR_RESP_DESIGNATED_INSTIT_ENTITY_SHOULD_BE_SETUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_resp_designated_instit_entity_should_be_setup();
			break;
		case 1701434: /* ERR_RESP_INFOCOMPLETED_IS_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_resp_infocompleted_is_missing();
			break;
		case 1701435: /* ERR_RESP_LETTER_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_resp_letter_missing();
			break;
		case 1701436: /* ERR_RESP_NASU_NOT_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastcbo_err_resp_nasu_not_available();
			break;
		case 1701437: /* ERR_RESP_ONLY_ACT_BENF_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_resp_only_act_benf_missing();
			break;
		case 1701438: /* ERR_RESP_ONLY_ONE_BENF_ALLOW */
			conditionObj = new CIFast_IFast_ifastcbo_err_resp_only_one_benf_allow();
			break;
		case 1701439: /* ERR_RESP_PCG_INDIV_SIN_INVALID */
			conditionObj = new CIFast_IFast_ifastcbo_err_resp_pcg_indiv_sin_invalid();
			break;
		case 1701440: /* ERR_RESP_PCG_INDIV_SIN_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_resp_pcg_indiv_sin_missing();
			break;
		case 1701441: /* ERR_RESP_REDEMPTION_EXCEED_CONTRIBUTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_resp_redemption_exceed_contribution();
			break;
		case 1701442: /* ERR_RESP_REDEMPTION_EXCEED_EARNINGS */
			conditionObj = new CIFast_IFast_ifastcbo_err_resp_redemption_exceed_earnings();
			break;
		case 1701443: /* ERR_RESP_SPECIFIC_EDIT_CHECK_NOT_PERFORMED */
			conditionObj = new CIFast_IFast_ifastcbo_err_resp_specific_edit_check_not_performed();
			break;
		case 1701444: /* ERR_RESP_TRADE_NOT_ALLOW */
			conditionObj = new CIFast_IFast_ifastcbo_err_resp_trade_not_allow();
			break;
		case 1701445: /* ERR_RETMAIL_MUST_BE_NO_WHEN_ADDRESS_CHANGED */
			conditionObj = new CIFast_IFast_ifastcbo_err_retmail_must_be_no_when_address_changed();
			break;
		case 1701446: /* ERR_REVERSAL_CODE_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_reversal_code_required();
			break;
		case 1701447: /* ERR_RIF_AMS_FUND_FUND_CODE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_ams_fund_fund_code();
			break;
		case 1701448: /* ERR_RIF_AMTTYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_amttype();
			break;
		case 1701449: /* ERR_RIF_BAD_RECORD */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_bad_record();
			break;
		case 1701450: /* ERR_RIF_CASH_FUND_CODE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_cash_fund_code();
			break;
		case 1701451: /* ERR_RIF_DIFF_CALC_VALUE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_diff_calc_value();
			break;
		case 1701452: /* ERR_RIF_EMPTY_EFFECTIVE_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_empty_effective_date();
			break;
		case 1701453: /* ERR_RIF_EOM_EFFECTIVE_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_eom_effective_date();
			break;
		case 1701454: /* ERR_RIF_EOM_MONTH_END */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_eom_month_end();
			break;
		case 1701455: /* ERR_RIF_FED_RATE_LESS_THAN_DEFAULT */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_fed_rate_less_than_default();
			break;
		case 1701456: /* ERR_RIF_FUTURE_BIRTHDATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_future_birthdate();
			break;
		case 1701457: /* ERR_RIF_FUTURE_EFFECTIVE_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_future_effective_date();
			break;
		case 1701458: /* ERR_RIF_INVALID_COMBINATION_FUND_CODE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_invalid_combination_fund_code();
			break;
		case 1701459: /* ERR_RIF_INVALID_GROSS_NET_METHOD_AFTER_NETOFFEES_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_invalid_gross_net_method_after_netoffees_date();
			break;
		case 1701460: /* ERR_RIF_INVALID_GROSS_NET_METHOD_BEFORE_NETOFFEES_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_invalid_gross_net_method_before_netoffees_date();
			break;
		case 1701461: /* ERR_RIF_INVALID_GROSS_OR_NET */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_invalid_gross_or_net();
			break;
		case 1701462: /* ERR_RIF_INVALID_PAY_OPTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_invalid_pay_option();
			break;
		case 1701463: /* ERR_RIF_INVALID_PAY_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_invalid_pay_type();
			break;
		case 1701464: /* ERR_RIF_INVALID_RATE_PUD */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_invalid_rate_pud();
			break;
		case 1701465: /* ERR_RIF_INVALID_RIF_SRC_OF_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_invalid_rif_src_of_fund();
			break;
		case 1701466: /* ERR_RIF_MANDATORY_MIN_WITH_AGE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_mandatory_min_with_age();
			break;
		case 1701467: /* ERR_RIF_MANDATORY_PAY_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_mandatory_pay_type();
			break;
		case 1701468: /* ERR_RIF_MAX_AMOUNT_LESS_THAN_UNUSED_AMOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_max_amount_less_than_unused_amount();
			break;
		case 1701469: /* ERR_RIF_MONTH */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_month();
			break;
		case 1701470: /* ERR_RIF_NEGATIVE_AMOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_negative_amount();
			break;
		case 1701471: /* ERR_RIF_NO_FLAG_ON_FUND_CODE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_no_flag_on_fund_code();
			break;
		case 1701472: /* ERR_RIF_NO_MAXIMUM_PAY_OPTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_no_maximum_pay_option();
			break;
		case 1701473: /* ERR_RIF_NO_PAYMENT_MONTH_END */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_no_payment_month_end();
			break;
		case 1701474: /* ERR_RIF_NO_SHAREHOLDER_BIRTHDATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_no_shareholder_birthdate();
			break;
		case 1701475: /* ERR_RIF_NON_100_TOTAL_PERCENTAGE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_non_100_total_percentage();
			break;
		case 1701476: /* ERR_RIF_NON_FRACTIONAL */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_non_fractional();
			break;
		case 1701477: /* ERR_RIF_NON_ZERO_INDEX_RATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_non_zero_index_rate();
			break;
		case 1701478: /* ERR_RIF_NON_ZERO_RATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_non_zero_rate();
			break;
		case 1701479: /* ERR_RIF_NOT_MIN_AMOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_not_min_amount();
			break;
		case 1701480: /* ERR_RIF_NOT_UNIQUE_FUND_CODE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_not_unique_fund_code();
			break;
		case 1701481: /* ERR_RIF_ONLY_ONE_GOOD_RECORD */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_only_one_good_record();
			break;
		case 1701482: /* ERR_RIF_OUT_OF_LIMITS_ALLOC_AMOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_out_of_limits_alloc_amount();
			break;
		case 1701483: /* ERR_RIF_OUT_OF_LIMITS_PERCENTAGE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_out_of_limits_percentage();
			break;
		case 1701484: /* ERR_RIF_OUT_OF_RANGE_INDEX_RATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_out_of_range_index_rate();
			break;
		case 1701485: /* ERR_RIF_PAST_EFFECTIVE_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_past_effective_date();
			break;
		case 1701486: /* ERR_RIF_PROV_RATE_LESS_THAN_DEFAULT */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_prov_rate_less_than_default();
			break;
		case 1701487: /* ERR_RIF_QUALIFIED */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_qualified();
			break;
		case 1701488: /* ERR_RIF_SPOUSE_OLDER_BIRTHDATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_spouse_older_birthdate();
			break;
		case 1701489: /* ERR_RIF_SPOUSE_OLDER_THAN_SHAREHOLDER */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_spouse_older_than_shareholder();
			break;
		case 1701490: /* ERR_RIF_STOP_RED_NOT_OFF_FUND_CODE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_stop_red_not_off_fund_code();
			break;
		case 1701491: /* ERR_RIF_SUM_TOO_BIG1_RATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_sum_too_big1_rate();
			break;
		case 1701492: /* ERR_RIF_SUM_TOO_BIG2_RATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_sum_too_big2_rate();
			break;
		case 1701493: /* ERR_RIF_TOO_BIG_AMOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_too_big_amount();
			break;
		case 1701494: /* ERR_RIF_TOO_BIG_MAND_AMT_YR */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_too_big_mand_amt_yr();
			break;
		case 1701495: /* ERR_RIF_TOO_BIG_MAX_AMT_YR */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_too_big_max_amt_yr();
			break;
		case 1701496: /* ERR_RIF_TOO_BIG_MIN_WITH_AGE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_too_big_min_with_age();
			break;
		case 1701497: /* ERR_RIF_TOO_BIG_RATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_too_big_rate();
			break;
		case 1701498: /* ERR_RIF_TOO_MANY_DECIMALS_RATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_too_many_decimals_rate();
			break;
		case 1701499: /* ERR_RIF_TOO_MANY_FUND_CODE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_too_many_fund_code();
			break;
		case 1701500: /* ERR_RIF_TOO_SMALL_AMOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_too_small_amount();
			break;
		case 1701501: /* ERR_RIF_TOO_SMALL_MAX_AMT_YR */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_too_small_max_amt_yr();
			break;
		case 1701502: /* ERR_RIF_UNKNOWN_ADDRESS_CODE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_unknown_address_code();
			break;
		case 1701503: /* ERR_RIF_UNUSED_AMT_CANNOT_BE_NEGATIVE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_unused_amt_cannot_be_negative();
			break;
		case 1701504: /* ERR_RIF_WARN_NO_SHAREHOLDER_BIRTHDATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_warn_no_shareholder_birthdate();
			break;
		case 1701505: /* ERR_RIF_WRONG_CURRENCY_FUND_CODE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_wrong_currency_fund_code();
			break;
		case 1701506: /* ERR_RIF_WRONG_RATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_wrong_rate();
			break;
		case 1701507: /* ERR_RIF_WRONG_STOP_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_wrong_stop_date();
			break;
		case 1701508: /* ERR_RIF_WRONG_VALUE_MAND_AMT_YR */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_wrong_value_mand_amt_yr();
			break;
		case 1701509: /* ERR_RIF_ZERO_ALLOC_AMOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_zero_alloc_amount();
			break;
		case 1701510: /* ERR_RIF_ZERO_OR_NEGATIVE_AMOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_rif_zero_or_negative_amount();
			break;
		case 1701511: /* ERR_RIGHT_TO_CANCEL_NOTALLWD */
			conditionObj = new CIFast_IFast_ifastcbo_err_right_to_cancel_notallwd();
			break;
		case 1701512: /* ERR_RO_EFF_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_ro_eff_date();
			break;
		case 1701513: /* ERR_ROLLOVER_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_rollover_not_allowed();
			break;
		case 1701514: /* ERR_ROLLOVER_NOT_SAME_ACCOUNT_OWNER */
			conditionObj = new CIFast_IFast_ifastcbo_err_rollover_not_same_account_owner();
			break;
		case 1701515: /* ERR_ROLLOVER_SAME_CURRENCY_FUNDS */
			conditionObj = new CIFast_IFast_ifastcbo_err_rollover_same_currency_funds();
			break;
		case 1701516: /* ERR_ROUND_FUND_CLASS_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_round_fund_class_required();
			break;
		case 1701517: /* ERR_RRIF_ALLOCATION_SETUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_rrif_allocation_setup();
			break;
		case 1701518: /* ERR_RRIF_CANNOT_BESETUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_rrif_cannot_besetup();
			break;
		case 1701519: /* ERR_RRIF_EXIST_IN_SAME_YEAR */
			conditionObj = new CIFast_IFast_ifastcbo_err_rrif_exist_in_same_year();
			break;
		case 1701520: /* ERR_RRIF_LIF_RATE_PUID */
			conditionObj = new CIFast_IFast_ifastcbo_err_rrif_lif_rate_puid();
			break;
		case 1701521: /* ERR_RRIF_ONE_MONTH_INDICATE_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_rrif_one_month_indicate_missing();
			break;
		case 1701522: /* ERR_RRIF_ONE_MONTH_INDICATE_MISSING2 */
			conditionObj = new CIFast_IFast_ifastcbo_err_rrif_one_month_indicate_missing2();
			break;
		case 1701523: /* ERR_RRIF_PayOptionMaximumNotAllowed */
			conditionObj = new CIFast_IFast_ifastcbo_err_rrif_payoptionmaximumnotallowed();
			break;
		case 1701524: /* ERR_RRIF_SUPPORTS_ONLY_CDN */
			conditionObj = new CIFast_IFast_ifastcbo_err_rrif_supports_only_cdn();
			break;
		case 1701525: /* ERR_RRIFAmountCannotBeLessEqualZero */
			conditionObj = new CIFast_IFast_ifastcbo_err_rrifamountcannotbelessequalzero();
			break;
		case 1701526: /* ERR_RULE_TYPE_RECORD_FOR_STOP_TRFER_IN_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_rule_type_record_for_stop_trfer_in_required();
			break;
		case 1701527: /* ERR_SAGES_ASSISTED_CONTRIBUTION_AMOUNT_IS_ZERO */
			conditionObj = new CIFast_IFast_ifastcbo_err_sages_assisted_contribution_amount_is_zero();
			break;
		case 1701528: /* ERR_SALES_CODE_CAN_NOT_LONGER_THAN_6 */
			conditionObj = new CIFast_IFast_ifastcbo_err_sales_code_can_not_longer_than_6();
			break;
		case 1701529: /* ERR_SALES_REP_EMPTY */
			conditionObj = new CIFast_IFast_ifastcbo_err_sales_rep_empty();
			break;
		case 1701530: /* ERR_SALESPERSON_IS_NOT_PERMITTED */
			conditionObj = new CIFast_IFast_ifastcbo_err_salesperson_is_not_permitted();
			break;
		case 1701531: /* ERR_SALESREP_MIN_BALANCE */
			conditionObj = new CIFast_IFast_ifastcbo_err_salesrep_min_balance();
			break;
		case 1701532: /* ERR_SALS_CODE_HAS_TO_BE_5 */
			conditionObj = new CIFast_IFast_ifastcbo_err_sals_code_has_to_be_5();
			break;
		case 1701533: /* ERR_SAME_ANNUITANT_AND_NOMINEE */
			conditionObj = new CIFast_IFast_ifastcbo_err_same_annuitant_and_nominee();
			break;
		case 1701534: /* ERR_SAME_FROM_TO_FUND_CLASS_NOT_ALLOW */
			conditionObj = new CIFast_IFast_ifastcbo_err_same_from_to_fund_class_not_allow();
			break;
		case 1701535: /* ERR_SAME_FUND_CLASS_FOR_REALIGNMENT_TR */
			conditionObj = new CIFast_IFast_ifastcbo_err_same_fund_class_for_realignment_tr();
			break;
		case 1701536: /* ERR_SAVINGS_DIRECTIVE_SUBSEQUENT_MONEY_OUT_EXISTS */
			conditionObj = new CIFast_IFast_ifastcbo_err_savings_directive_subsequent_money_out_exists();
			break;
		case 1701537: /* ERR_SCALE_RATE_TOO_LARGE */
			conditionObj = new CIFast_IFast_ifastcbo_err_scale_rate_too_large();
			break;
		case 1701538: /* ERR_SCHEDULED_PAYMENT_NOT_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastcbo_err_scheduled_payment_not_available();
			break;
		case 1701539: /* ERR_SECOND_DATE_EARLIER */
			conditionObj = new CIFast_IFast_ifastcbo_err_second_date_earlier();
			break;
		case 1701540: /* ERR_SECONDARY_BENEF_PERCENT_SHOULD_ADD_UP_TO_100 */
			conditionObj = new CIFast_IFast_ifastcbo_err_secondary_benef_percent_should_add_up_to_100();
			break;
		case 1701541: /* ERR_SECONDARY_BENEFICIARY_ENTITY_ONLY_ALLOWED_IF_PRIMARY_ENTITY_EXIST */
			conditionObj = new CIFast_IFast_ifastcbo_err_secondary_beneficiary_entity_only_allowed_if_primary_entity_exist();
			break;
		case 1701542: /* ERR_SEG_VALIDATION_BACKDATED_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_seg_validation_backdated_not_allowed();
			break;
		case 1701543: /* ERR_SELAMOUNT_LESSTHAN_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_selamount_lessthan_required();
			break;
		case 1701544: /* ERR_SENDER_REF_NUM_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_sender_ref_num_required();
			break;
		case 1701545: /* ERR_SERVICE_AGENT_CHANGED_BY_COMPENSATION_AGENT */
			conditionObj = new CIFast_IFast_ifastcbo_err_service_agent_changed_by_compensation_agent();
			break;
		case 1701546: /* ERR_SERVICE_AGENT_MUST_BE_CHANGED */
			conditionObj = new CIFast_IFast_ifastcbo_err_service_agent_must_be_changed();
			break;
		case 1701547: /* ERR_SETTL_LOC_IS_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_settl_loc_is_missing();
			break;
		case 1701548: /* ERR_SETTLE_CURRENCY_MANDATORY */
			conditionObj = new CIFast_IFast_ifastcbo_err_settle_currency_mandatory();
			break;
		case 1701549: /* ERR_SETTLE_FUTURE_TRADE_NOT_ALLOWED_FOR_EPA_TRADE */
			conditionObj = new CIFast_IFast_ifastcbo_err_settle_future_trade_not_allowed_for_epa_trade();
			break;
		case 1701550: /* ERR_SETTLE_NETWORK_APPLIED_TO_CANCELLATION_AND_REBOOK */
			conditionObj = new CIFast_IFast_ifastcbo_err_settle_network_applied_to_cancellation_and_rebook();
			break;
		case 1701551: /* ERR_SETTLE_TYPE_INDIVIDUAL_NOT_ALLOW_THROUGH_FUNDSERV */
			conditionObj = new CIFast_IFast_ifastcbo_err_settle_type_individual_not_allow_through_fundserv();
			break;
		case 1701552: /* ERR_SETTLEDATE_EARLIER_THAN_NEXT_CYCLEDATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_settledate_earlier_than_next_cycledate();
			break;
		case 1701553: /* ERR_SETTLEDATE_EARLIER_THAN_TRADEDATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_settledate_earlier_than_tradedate();
			break;
		case 1701554: /* ERR_SETTLEMENT_AMOUNT_DOES_NOT_MATCH */
			conditionObj = new CIFast_IFast_ifastcbo_err_settlement_amount_does_not_match();
			break;
		case 1701555: /* ERR_SETTLEMENT_DATE_DOES_NOT_MATCH */
			conditionObj = new CIFast_IFast_ifastcbo_err_settlement_date_does_not_match();
			break;
		case 1701556: /* ERR_SETTLEMENT_INSTRUCTIONS_EXPIRED_AS_OF */
			conditionObj = new CIFast_IFast_ifastcbo_err_settlement_instructions_expired_as_of();
			break;
		case 1701557: /* ERR_SETTLEMENT_INSUFFICIENT_SETTLED_UNITS */
			conditionObj = new CIFast_IFast_ifastcbo_err_settlement_insufficient_settled_units();
			break;
		case 1701558: /* ERR_SETTLEMENT_LOCATION_CODE_FOR_ACCOUNT_DOES_NOT_EXIST_AT_SYSTEM_LEVEL */
			conditionObj = new CIFast_IFast_ifastcbo_err_settlement_location_code_for_account_does_not_exist_at_system_level();
			break;
		case 1701559: /* ERR_SETTLEMENT_PAY_TYPE_CLEARING_CANNOT_BE_SELECTED */
			conditionObj = new CIFast_IFast_ifastcbo_err_settlement_pay_type_clearing_cannot_be_selected();
			break;
		case 1701560: /* ERR_SETTLEMENT_PAY_TYPE_DIRECT_DEPOSIT_CANNOT_BE_SELECTED */
			conditionObj = new CIFast_IFast_ifastcbo_err_settlement_pay_type_direct_deposit_cannot_be_selected();
			break;
		case 1701561: /* ERR_SETTLEMENT_RULE_EFFECTIVE_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_settlement_rule_effective_date();
			break;
		case 1701562: /* ERR_SETTLEMENT_RULE_INVALID_SETTLE_DAYS_VALUE */
			conditionObj = new CIFast_IFast_ifastcbo_err_settlement_rule_invalid_settle_days_value();
			break;
		case 1701563: /* ERR_SETTLEMENT_SOURCE_NOT_FOR_ACCT_DESIGNATION */
			conditionObj = new CIFast_IFast_ifastcbo_err_settlement_source_not_for_acct_designation();
			break;
		case 1701564: /* ERR_SETTLEMENT_SOURCE_NOT_UPDATABLE */
			conditionObj = new CIFast_IFast_ifastcbo_err_settlement_source_not_updatable();
			break;
		case 1701565: /* ERR_SETTLEMENT_SUPPRESS_CODE_CLEARING_CANNOT_BE_SELECTED */
			conditionObj = new CIFast_IFast_ifastcbo_err_settlement_suppress_code_clearing_cannot_be_selected();
			break;
		case 1701566: /* ERR_SETTLEMENT_VALUE_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_settlement_value_date();
			break;
		case 1701567: /* ERR_SETTLING_GRANT_REPAYMENT_BY_UNIT_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_settling_grant_repayment_by_unit_not_allowed();
			break;
		case 1701568: /* ERR_SHARE_HOLDER_HOLD_MULTIPLE_ACCOUNTS */
			conditionObj = new CIFast_IFast_ifastcbo_err_share_holder_hold_multiple_accounts();
			break;
		case 1701569: /* ERR_SHAREHOLDER_BELOW_69 */
			conditionObj = new CIFast_IFast_ifastcbo_err_shareholder_below_69();
			break;
		case 1701570: /* ERR_SHAREHOLDER_DECEASED */
			conditionObj = new CIFast_IFast_ifastcbo_err_shareholder_deceased();
			break;
		case 1701571: /* ERR_SHAREHOLDER_NUM_CANNOT_BE_LEFT_EMPTY */
			conditionObj = new CIFast_IFast_ifastcbo_err_shareholder_num_cannot_be_left_empty();
			break;
		case 1701572: /* ERR_SHAREHOLDER_NUMBER_CANNOT_START_WITH_ZERO */
			conditionObj = new CIFast_IFast_ifastcbo_err_shareholder_number_cannot_start_with_zero();
			break;
		case 1701573: /* ERR_SHAREHOLDER_NUMBER_EMPTY */
			conditionObj = new CIFast_IFast_ifastcbo_err_shareholder_number_empty();
			break;
		case 1701574: /* ERR_SHAREHOLDER_NUMBER_EXISTS */
			conditionObj = new CIFast_IFast_ifastcbo_err_shareholder_number_exists();
			break;
		case 1701575: /* ERR_SHAREHOLDER_TAXJUR_RESPROV_UNASSIGNED */
			conditionObj = new CIFast_IFast_ifastcbo_err_shareholder_taxjur_resprov_unassigned();
			break;
		case 1701576: /* ERR_ShareholderFeeModelCodeIsRequired */
			conditionObj = new CIFast_IFast_ifastcbo_err_shareholderfeemodelcodeisrequired();
			break;
		case 1701577: /* ERR_SIGNATURE_DATE_LATER */
			conditionObj = new CIFast_IFast_ifastcbo_err_signature_date_later();
			break;
		case 1701578: /* ERR_SIGNATURE_DATE_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_signature_date_required();
			break;
		case 1701579: /* ERR_SIN_DIFFERENT_FOR_TRF_PROTECTEDFUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_sin_different_for_trf_protectedfund();
			break;
		case 1701580: /* ERR_SIN_DUPLIATE_WITH_OTHER_ACCOUNT_ENTITY */
			conditionObj = new CIFast_IFast_ifastcbo_err_sin_dupliate_with_other_account_entity();
			break;
		case 1701581: /* ERR_SIN_EFFECTIVE_DATE_CANNOT_BE_EARLIER_THAN_DOFB */
			conditionObj = new CIFast_IFast_ifastcbo_err_sin_effective_date_cannot_be_earlier_than_dofb();
			break;
		case 1701582: /* ERR_SIN_EFFECTIVE_DATE_CANNOT_BE_FUTURE_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_sin_effective_date_cannot_be_future_date();
			break;
		case 1701583: /* ERR_SIN_EFFECTIVE_DATE_CANNOT_BE_UNKNOWN */
			conditionObj = new CIFast_IFast_ifastcbo_err_sin_effective_date_cannot_be_unknown();
			break;
		case 1701584: /* ERR_SIN_EFFECTIVE_DATE_IS_MANDATORY */
			conditionObj = new CIFast_IFast_ifastcbo_err_sin_effective_date_is_mandatory();
			break;
		case 1701585: /* ERR_SIN_MISSING_FOR_SPOUSE */
			conditionObj = new CIFast_IFast_ifastcbo_err_sin_missing_for_spouse();
			break;
		case 1701586: /* ERR_SIN_MISSING_FOR_TRADING_PROTECTED_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_sin_missing_for_trading_protected_fund();
			break;
		case 1701587: /* ERR_SIN_MISSING_SPOUSAL_TRANSFEREE */
			conditionObj = new CIFast_IFast_ifastcbo_err_sin_missing_spousal_transferee();
			break;
		case 1701588: /* ERR_SIN_NUMBER_SAME_ENTITY_1_ENTITY_2 */
			conditionObj = new CIFast_IFast_ifastcbo_err_sin_number_same_entity_1_entity_2();
			break;
		case 1701589: /* ERR_SLSREP_FROM_TRANSFER_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_slsrep_from_transfer_not_allowed();
			break;
		case 1701590: /* ERR_SLSREP_INVALID_AS_OF_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_slsrep_invalid_as_of_date();
			break;
		case 1701591: /* ERR_SLSREP_MIN_ALLOWABLE_PURCHASE */
			conditionObj = new CIFast_IFast_ifastcbo_err_slsrep_min_allowable_purchase();
			break;
		case 1701592: /* ERR_SLSREP_MIN_INIT_PURCHASE */
			conditionObj = new CIFast_IFast_ifastcbo_err_slsrep_min_init_purchase();
			break;
		case 1701593: /* ERR_SLSREP_PURCHASE_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_slsrep_purchase_not_allowed();
			break;
		case 1701594: /* ERR_SLSREP_REDEMPTION_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_slsrep_redemption_not_allowed();
			break;
		case 1701595: /* ERR_SLSREP_TO_TRANSFER_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_slsrep_to_transfer_not_allowed();
			break;
		case 1701596: /* ERR_SOCIAL_CODE_NOT_APPLICABLE */
			conditionObj = new CIFast_IFast_ifastcbo_err_social_code_not_applicable();
			break;
		case 1701597: /* ERR_SPECIFIE_FUND_WHEN_AMOUNT_IS_ZERO */
			conditionObj = new CIFast_IFast_ifastcbo_err_specifie_fund_when_amount_is_zero();
			break;
		case 1701598: /* ERR_SPLIT_COMMISSION_ONLY_DISCOUNTS_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_split_commission_only_discounts_allowed();
			break;
		case 1701599: /* ERR_SPLIT_RENUNCIATION */
			conditionObj = new CIFast_IFast_ifastcbo_err_split_renunciation();
			break;
		case 1701600: /* ERR_SPOUSAL_CONSENT_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_spousal_consent_required();
			break;
		case 1701601: /* ERR_SPOUSAL_CONSENT_WAIVER_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_spousal_consent_waiver_required();
			break;
		case 1701602: /* ERR_SPOUSAL_CONTRIBUTOR_ENTITY_SHOULD_BE_SETUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_spousal_contributor_entity_should_be_setup();
			break;
		case 1701603: /* ERR_SPOUSAL_INVALID_FOR_ACCT_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_spousal_invalid_for_acct_type();
			break;
		case 1701604: /* ERR_SPOUSE_BIRTHDAY_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_spouse_birthday_missing();
			break;
		case 1701605: /* ERR_SPOUSE_SIN_INVALID */
			conditionObj = new CIFast_IFast_ifastcbo_err_spouse_sin_invalid();
			break;
		case 1701606: /* ERR_SPOUSE_SIN_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_spouse_sin_missing();
			break;
		case 1701607: /* ERR_SRVCE_AGENT_BELONGS_TO_FUNDSERV_BROKER */
			conditionObj = new CIFast_IFast_ifastcbo_err_srvce_agent_belongs_to_fundserv_broker();
			break;
		case 1701608: /* ERR_START_DATE_AFTER_SYSTEM_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_start_date_after_system_date();
			break;
		case 1701609: /* ERR_START_DATE_BEFORE_EFFECTIVE_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_start_date_before_effective_date();
			break;
		case 1701610: /* ERR_START_DATE_BEFORE_EFFECTIVE_DATE_OF_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_start_date_before_effective_date_of_fund();
			break;
		case 1701611: /* ERR_START_DATE_BEFORE_LAST_DIV_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_start_date_before_last_div_date();
			break;
		case 1701612: /* ERR_START_DATE_BEFORE_LAST_PROCESS_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_start_date_before_last_process_date();
			break;
		case 1701613: /* ERR_START_DATE_DISTRIBUTION_DAY */
			conditionObj = new CIFast_IFast_ifastcbo_err_start_date_distribution_day();
			break;
		case 1701614: /* ERR_START_DATE_EARLEAR_THAN_LAST_DIVIDEND_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_start_date_earlear_than_last_dividend_date();
			break;
		case 1701615: /* ERR_START_DATE_LATE_THAN_STOP_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_start_date_late_than_stop_date();
			break;
		case 1701616: /* ERR_START_DATE_MUST_BE_PRIOR_TO_LAST_PROCESSED_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_start_date_must_be_prior_to_last_processed_date();
			break;
		case 1701617: /* ERR_START_DATE_USED */
			conditionObj = new CIFast_IFast_ifastcbo_err_start_date_used();
			break;
		case 1701618: /* ERR_START_STOP_DATE_MUST_BE_WITHIN_REGPORTING_FFI */
			conditionObj = new CIFast_IFast_ifastcbo_err_start_stop_date_must_be_within_regporting_ffi();
			break;
		case 1701619: /* ERR_STATUS_CHANGED */
			conditionObj = new CIFast_IFast_ifastcbo_err_status_changed();
			break;
		case 1701620: /* ERR_STATUS_IS_BLANK */
			conditionObj = new CIFast_IFast_ifastcbo_err_status_is_blank();
			break;
		case 1701621: /* ERR_STATUS_MAY_NEED_TO_FLIP_OR_NEW_REQUEST_MAY_BE_REQUIRED_FOR_TAX_YEAR */
			conditionObj = new CIFast_IFast_ifastcbo_err_status_may_need_to_flip_or_new_request_may_be_required_for_tax_year();
			break;
		case 1701622: /* ERR_STATUS_NOT_ALLOWED_FOR_ACCT_DEATH_OR_DEATH_TRANSFER */
			conditionObj = new CIFast_IFast_ifastcbo_err_status_not_allowed_for_acct_death_or_death_transfer();
			break;
		case 1701623: /* ERR_STOP_ADJDATE_GREATER_THAN_EFFECTIVEDATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_stop_adjdate_greater_than_effectivedate();
			break;
		case 1701624: /* ERR_STOP_DATE_BACKWARD */
			conditionObj = new CIFast_IFast_ifastcbo_err_stop_date_backward();
			break;
		case 1701625: /* ERR_STOP_DATE_BEFORE_BUSSINESDAY */
			conditionObj = new CIFast_IFast_ifastcbo_err_stop_date_before_bussinesday();
			break;
		case 1701626: /* ERR_STOP_DATE_EARLIER_EFFDATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_stop_date_earlier_effdate();
			break;
		case 1701627: /* ERR_STOP_DATE_LESS_THAN_DEFF */
			conditionObj = new CIFast_IFast_ifastcbo_err_stop_date_less_than_deff();
			break;
		case 1701628: /* ERR_STOP_DATE_MUST_BE_WITHIN_FFI_STOP_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_stop_date_must_be_within_ffi_stop_date();
			break;
		case 1701629: /* ERR_STOP_FLAG_ACTIVE */
			conditionObj = new CIFast_IFast_ifastcbo_err_stop_flag_active();
			break;
		case 1701630: /* ERR_STOP_FLAG_ACTIVE_IGNORED */
			conditionObj = new CIFast_IFast_ifastcbo_err_stop_flag_active_ignored();
			break;
		case 1701631: /* ERR_STOP_FLAG_SET_FOR_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_stop_flag_set_for_fund();
			break;
		case 1701632: /* ERR_STOP_MONEY_IN_FOR_TAX_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_stop_money_in_for_tax_type();
			break;
		case 1701633: /* ERR_STOP_SETTLE_REDEMPTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_stop_settle_redemption();
			break;
		case 1701634: /* ERR_STOPDATE_INVALID_FOR_BUYATNAV */
			conditionObj = new CIFast_IFast_ifastcbo_err_stopdate_invalid_for_buyatnav();
			break;
		case 1701635: /* ERR_STOPDATE_NOT_VALID */
			conditionObj = new CIFast_IFast_ifastcbo_err_stopdate_not_valid();
			break;
		case 1701636: /* ERR_SUBSEQUENT_EVENTS_TAKEN_PLACE_AT_BACKDATING */
			conditionObj = new CIFast_IFast_ifastcbo_err_subsequent_events_taken_place_at_backdating();
			break;
		case 1701637: /* ERR_SUM_OF_ALLOC_PERCENTAGES_NOT_100 */
			conditionObj = new CIFast_IFast_ifastcbo_err_sum_of_alloc_percentages_not_100();
			break;
		case 1701638: /* ERR_SUM_OF_BENEF_ALLOC_PERCENTAGES_NOT_100 */
			conditionObj = new CIFast_IFast_ifastcbo_err_sum_of_benef_alloc_percentages_not_100();
			break;
		case 1701639: /* ERR_SUM_OF_DISTRIBUTION_RATES_NOT_RECENT_DISTRIBUTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_sum_of_distribution_rates_not_recent_distribution();
			break;
		case 1701640: /* ERR_SUM_OF_PERCENTAGES_NOT_0 */
			conditionObj = new CIFast_IFast_ifastcbo_err_sum_of_percentages_not_0();
			break;
		case 1701641: /* ERR_SUM_OF_PERCENTAGES_NOT_100 */
			conditionObj = new CIFast_IFast_ifastcbo_err_sum_of_percentages_not_100();
			break;
		case 1701642: /* ERR_SUM_OF_PERCENTAGES_NOT_100_OR_0 */
			conditionObj = new CIFast_IFast_ifastcbo_err_sum_of_percentages_not_100_or_0();
			break;
		case 1701643: /* ERR_SUPP_CODE_NOT_ALLOWED_FOR_TRANS_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_supp_code_not_allowed_for_trans_type();
			break;
		case 1701644: /* ERR_SUPPRESS_PAYTYPE_REQUIRED_FOR_FUND_SOURCE */
			conditionObj = new CIFast_IFast_ifastcbo_err_suppress_paytype_required_for_fund_source();
			break;
		case 1701645: /* ERR_SWIFTCODE_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastcbo_err_swiftcode_not_exist();
			break;
		case 1701646: /* ERR_SWP_CANNOT_BESETUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_swp_cannot_besetup();
			break;
		case 1701647: /* ERR_SWP_FUND_BLANK */
			conditionObj = new CIFast_IFast_ifastcbo_err_swp_fund_blank();
			break;
		case 1701648: /* ERR_SWP_LESS_THAN_MINIMUM_ALLOW */
			conditionObj = new CIFast_IFast_ifastcbo_err_swp_less_than_minimum_allow();
			break;
		case 1701649: /* ERR_SWP_NON_GMWB_FUNDS */
			conditionObj = new CIFast_IFast_ifastcbo_err_swp_non_gmwb_funds();
			break;
		case 1701650: /* ERR_SWP_PAYOPTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_swp_payoption();
			break;
		case 1701651: /* ERR_SWP_UNDER_REGISTERED_ACCT */
			conditionObj = new CIFast_IFast_ifastcbo_err_swp_under_registered_acct();
			break;
		case 1701652: /* ERR_SWP_UNITS_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_swp_units_not_allowed();
			break;
		case 1701653: /* ERR_SYS_DEFF_LESS_THAN_ACCT_DEFF */
			conditionObj = new CIFast_IFast_ifastcbo_err_sys_deff_less_than_acct_deff();
			break;
		case 1701654: /* ERR_SYS_FEE_INVALID_GWB_BASEDON */
			conditionObj = new CIFast_IFast_ifastcbo_err_sys_fee_invalid_gwb_basedon();
			break;
		case 1701655: /* ERR_SYS_TRIG_AMEND_AND_RECAL_QESI_NOTIONAL_BALANCE */
			conditionObj = new CIFast_IFast_ifastcbo_err_sys_trig_amend_and_recal_qesi_notional_balance();
			break;
		case 1701656: /* ERR_SYSTEM_ACCT_CATEGORY */
			conditionObj = new CIFast_IFast_ifastcbo_err_system_acct_category();
			break;
		case 1701657: /* ERR_SYSTEM_REBALANCING_STATUS */
			conditionObj = new CIFast_IFast_ifastcbo_err_system_rebalancing_status();
			break;
		case 1701658: /* ERR_SYSTEM_STOP_REASON */
			conditionObj = new CIFast_IFast_ifastcbo_err_system_stop_reason();
			break;
		case 1701659: /* ERR_TAINTED_FIELD_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_tainted_field_required();
			break;
		case 1701660: /* ERR_TAX_AMOUNT_GREATER_THAN_AMOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_tax_amount_greater_than_amount();
			break;
		case 1701661: /* ERR_TAX_AMOUNT_NEGATIVE */
			conditionObj = new CIFast_IFast_ifastcbo_err_tax_amount_negative();
			break;
		case 1701662: /* ERR_TAX_ID_NUMBER_NOT_PROVIDED */
			conditionObj = new CIFast_IFast_ifastcbo_err_tax_id_number_not_provided();
			break;
		case 1701663: /* ERR_TAX_JURIS_EMPTY */
			conditionObj = new CIFast_IFast_ifastcbo_err_tax_juris_empty();
			break;
		case 1701664: /* ERR_TAX_JURIS_INVALID */
			conditionObj = new CIFast_IFast_ifastcbo_err_tax_juris_invalid();
			break;
		case 1701665: /* ERR_TAX_RATE_LESS_THAN_ZERO_OR_GREATER_THAN_100 */
			conditionObj = new CIFast_IFast_ifastcbo_err_tax_rate_less_than_zero_or_greater_than_100();
			break;
		case 1701666: /* ERR_TAX_TYPE_CANNOT_TRADE_IN_THE_CURRENCY */
			conditionObj = new CIFast_IFast_ifastcbo_err_tax_type_cannot_trade_in_the_currency();
			break;
		case 1701667: /* ERR_TAX_TYPE_EMTPY */
			conditionObj = new CIFast_IFast_ifastcbo_err_tax_type_emtpy();
			break;
		case 1701668: /* ERR_TAX_TYPE_IS_NOT_ALLOWED_TO_TRADE_IN_FUND_CURRENCY */
			conditionObj = new CIFast_IFast_ifastcbo_err_tax_type_is_not_allowed_to_trade_in_fund_currency();
			break;
		case 1701669: /* ERR_TAX_TYPE_LIMIT_RULE_NOT_SUPPORTED_BEFORE_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_tax_type_limit_rule_not_supported_before_date();
			break;
		case 1701670: /* ERR_TAX_TYPE_NO_LONGER_SUPPORTED_AFTER_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_tax_type_no_longer_supported_after_date();
			break;
		case 1701671: /* ERR_TAX_TYPE_NO_NON_REGISTER */
			conditionObj = new CIFast_IFast_ifastcbo_err_tax_type_no_non_register();
			break;
		case 1701672: /* ERR_TAX_TYPE_NOT_FOR_ACCT_DESIGNATION */
			conditionObj = new CIFast_IFast_ifastcbo_err_tax_type_not_for_acct_designation();
			break;
		case 1701673: /* ERR_TAX_YEAR_EMPTY */
			conditionObj = new CIFast_IFast_ifastcbo_err_tax_year_empty();
			break;
		case 1701674: /* ERR_TAX_YEAR_FUTURE_DATED */
			conditionObj = new CIFast_IFast_ifastcbo_err_tax_year_future_dated();
			break;
		case 1701675: /* ERR_TaxOnMin_SuppFedTax_SuppProvTax */
			conditionObj = new CIFast_IFast_ifastcbo_err_taxonmin_suppfedtax_suppprovtax();
			break;
		case 1701676: /* ERR_TAXTYPE_IS_NOT_ALLOWED_TRADING */
			conditionObj = new CIFast_IFast_ifastcbo_err_taxtype_is_not_allowed_trading();
			break;
		case 1701677: /* ERR_TFR_PROTECTED_FUND_TO_DIFFERENT_SIN */
			conditionObj = new CIFast_IFast_ifastcbo_err_tfr_protected_fund_to_different_sin();
			break;
		case 1701678: /* ERR_THE_AMS_MODEL_ASSOCIATED_WITH_ANOTHER_ACCT_SAME_SHRHLDR */
			conditionObj = new CIFast_IFast_ifastcbo_err_the_ams_model_associated_with_another_acct_same_shrhldr();
			break;
		case 1701679: /* ERR_THIS_FUND_HAS_NO_MGT_FEE */
			conditionObj = new CIFast_IFast_ifastcbo_err_this_fund_has_no_mgt_fee();
			break;
		case 1701680: /* ERR_THIS_FUND_HAS_NO_MGT_REBATE_FEE */
			conditionObj = new CIFast_IFast_ifastcbo_err_this_fund_has_no_mgt_rebate_fee();
			break;
		case 1701681: /* ERR_TIK_WITH_GUARANTEE_OVERRIDE_SAME_FUND_CLASS */
			conditionObj = new CIFast_IFast_ifastcbo_err_tik_with_guarantee_override_same_fund_class();
			break;
		case 1701682: /* ERR_TO_ACCOUNT_CANNOT_BE_SAME_AS_FROM_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_to_account_cannot_be_same_as_from_account();
			break;
		case 1701683: /* ERR_TO_ACCT_MUST_DIFF_FROM_ACCT_FOR_IN_KIND_TRANS */
			conditionObj = new CIFast_IFast_ifastcbo_err_to_acct_must_diff_from_acct_for_in_kind_trans();
			break;
		case 1701684: /* ERR_TO_ACCT_MUST_DIFF_FROM_ACCT_FOR_TRANSFER */
			conditionObj = new CIFast_IFast_ifastcbo_err_to_acct_must_diff_from_acct_for_transfer();
			break;
		case 1701685: /* ERR_TO_BENEF_IS_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_to_benef_is_missing();
			break;
		case 1701686: /* ERR_TO_CLEARING_METHOD_CCY_ONLY_FOR_SAME_SETTLE_CURR_FUND_CURR */
			conditionObj = new CIFast_IFast_ifastcbo_err_to_clearing_method_ccy_only_for_same_settle_curr_fund_curr();
			break;
		case 1701687: /* ERR_TO_CLEARING_METHOD_REALIGNMENT_ONLY_FOR_SAME_FROM_TO_CLASS */
			conditionObj = new CIFast_IFast_ifastcbo_err_to_clearing_method_realignment_only_for_same_from_to_class();
			break;
		case 1701688: /* ERR_TO_CLEARING_METHOD_REALIGNMENT_ONLY_FOR_SAME_FROM_TO_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_to_clearing_method_realignment_only_for_same_from_to_fund();
			break;
		case 1701689: /* ERR_TO_DELIVERY_TO_MUST_BE_SUPPLIED_FOR_CLEARING_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_to_delivery_to_must_be_supplied_for_clearing_account();
			break;
		case 1701690: /* ERR_TOCLASSCODE_TOACCOUNT_FOR_INDICATIE_ALLOCATION */
			conditionObj = new CIFast_IFast_ifastcbo_err_toclasscode_toaccount_for_indicatie_allocation();
			break;
		case 1701691: /* ERR_TODATE_AFTER_CURBUS_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_todate_after_curbus_date();
			break;
		case 1701692: /* ERR_TOFUND_SAME_OR_CASH */
			conditionObj = new CIFast_IFast_ifastcbo_err_tofund_same_or_cash();
			break;
		case 1701693: /* ERR_TOTAL_AMT_ON_SETTLINSTR */
			conditionObj = new CIFast_IFast_ifastcbo_err_total_amt_on_settlinstr();
			break;
		case 1701694: /* ERR_TOTAL_KYC_PRCNT_MUST_BE_0_OR_100 */
			conditionObj = new CIFast_IFast_ifastcbo_err_total_kyc_prcnt_must_be_0_or_100();
			break;
		case 1701695: /* ERR_TOTAL_REDEMPTION_EXCEEDS_MAXIMUM */
			conditionObj = new CIFast_IFast_ifastcbo_err_total_redemption_exceeds_maximum();
			break;
		case 1701696: /* ERR_TOTAL_SPLIT_COMMISION_RATE_EXCEEDS_FEE_DEFAULT */
			conditionObj = new CIFast_IFast_ifastcbo_err_total_split_commision_rate_exceeds_fee_default();
			break;
		case 1701697: /* ERR_TOTAL_SPLIT_COMMISION_RATE_EXCEEDS_FEE_MAX */
			conditionObj = new CIFast_IFast_ifastcbo_err_total_split_commision_rate_exceeds_fee_max();
			break;
		case 1701698: /* ERR_TOTAL_TAX_AMOUNT_GREATER_THAN_AMOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_total_tax_amount_greater_than_amount();
			break;
		case 1701699: /* ERR_TPA_INVALID */
			conditionObj = new CIFast_IFast_ifastcbo_err_tpa_invalid();
			break;
		case 1701700: /* ERR_TPA_NOT_RELATED_TO_CLEARINGFIRM */
			conditionObj = new CIFast_IFast_ifastcbo_err_tpa_not_related_to_clearingfirm();
			break;
		case 1701701: /* ERR_TR_INVALID_RED_CODE */
			conditionObj = new CIFast_IFast_ifastcbo_err_tr_invalid_red_code();
			break;
		case 1701702: /* ERR_TR_NOT_ALLOW_FROM_TAXTYPE_TO_TAXTYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_tr_not_allow_from_taxtype_to_taxtype();
			break;
		case 1701703: /* ERR_TRADE_BACKDATED_SUBSEQUENT_OUT_EXISTS */
			conditionObj = new CIFast_IFast_ifastcbo_err_trade_backdated_subsequent_out_exists();
			break;
		case 1701704: /* ERR_TRADE_DATE_DOESNOT_MATCH */
			conditionObj = new CIFast_IFast_ifastcbo_err_trade_date_doesnot_match();
			break;
		case 1701705: /* ERR_TRADE_DATE_FUTURE_DATED */
			conditionObj = new CIFast_IFast_ifastcbo_err_trade_date_future_dated();
			break;
		case 1701706: /* ERR_TRADE_DATE_IN_PRIOR_YEAR */
			conditionObj = new CIFast_IFast_ifastcbo_err_trade_date_in_prior_year();
			break;
		case 1701707: /* ERR_TRADE_DATE_MUST_BE_EQUAL_OR_GREATER_THAN_SAGESDEFF */
			conditionObj = new CIFast_IFast_ifastcbo_err_trade_date_must_be_equal_or_greater_than_sagesdeff();
			break;
		case 1701708: /* ERR_TRADE_DATE_NOT_VALUATION_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_trade_date_not_valuation_date();
			break;
		case 1701709: /* ERR_TRADE_DATE_OUTSIDE_MIN_MAX */
			conditionObj = new CIFast_IFast_ifastcbo_err_trade_date_outside_min_max();
			break;
		case 1701710: /* ERR_TRADE_EXIST_FOR_TAX_YEAR */
			conditionObj = new CIFast_IFast_ifastcbo_err_trade_exist_for_tax_year();
			break;
		case 1701711: /* ERR_TRADE_EXITS_IN_ACCT */
			conditionObj = new CIFast_IFast_ifastcbo_err_trade_exits_in_acct();
			break;
		case 1701712: /* ERR_TRADE_FOR_PRIOR_TAX_YEAR */
			conditionObj = new CIFast_IFast_ifastcbo_err_trade_for_prior_tax_year();
			break;
		case 1701713: /* ERR_TRADE_FROM_SETTLEMENT_INSTRUCTIONS_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_trade_from_settlement_instructions_missing();
			break;
		case 1701714: /* ERR_TRADE_IS_A_GRANT */
			conditionObj = new CIFast_IFast_ifastcbo_err_trade_is_a_grant();
			break;
		case 1701715: /* ERR_TRADE_IS_PART_OF_DM_EVENT */
			conditionObj = new CIFast_IFast_ifastcbo_err_trade_is_part_of_dm_event();
			break;
		case 1701716: /* ERR_TRADE_NOT_ALLOWED_TO_CANCEL */
			conditionObj = new CIFast_IFast_ifastcbo_err_trade_not_allowed_to_cancel();
			break;
		case 1701717: /* ERR_TRADE_PAY_TYPE_INVALID_FOR_NON_CLEARING_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_trade_pay_type_invalid_for_non_clearing_account();
			break;
		case 1701718: /* ERR_TRADE_SETTLEMENT_IS_RESTRICTED_DUE_TO */
			conditionObj = new CIFast_IFast_ifastcbo_err_trade_settlement_is_restricted_due_to();
			break;
		case 1701719: /* ERR_TRADE_TO_SETTLEMENT_INSTRUCTIONS_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_trade_to_settlement_instructions_missing();
			break;
		case 1701720: /* ERR_TRADED_UNIT_POSITION */
			conditionObj = new CIFast_IFast_ifastcbo_err_traded_unit_position();
			break;
		case 1701721: /* ERR_TRADING_NOT_ALLOWED_WITHOUT_ACCT_SPLIT_COMM */
			conditionObj = new CIFast_IFast_ifastcbo_err_trading_not_allowed_without_acct_split_comm();
			break;
		case 1701722: /* ERR_TRADING_SETTLEMENT_LOCATION_HAS_NOT_BEEN_SETUP_FOR_CLEARING_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_trading_settlement_location_has_not_been_setup_for_clearing_account();
			break;
		case 1701723: /* ERR_TRADING_SETTLEMENT_LOCATION_INVALID_CODE_FOR_CLEARING_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_trading_settlement_location_invalid_code_for_clearing_account();
			break;
		case 1701724: /* ERR_TRANFER_TANSACTION_RESUBMITTED */
			conditionObj = new CIFast_IFast_ifastcbo_err_tranfer_tansaction_resubmitted();
			break;
		case 1701725: /* ERR_TRANS_REPRINT_ALL_COPIES_INACTIVE */
			conditionObj = new CIFast_IFast_ifastcbo_err_trans_reprint_all_copies_inactive();
			break;
		case 1701726: /* ERR_TRANSACTION_NOT_ALLOWED_AFTER_69 */
			conditionObj = new CIFast_IFast_ifastcbo_err_transaction_not_allowed_after_69();
			break;
		case 1701727: /* ERR_TRANSFER_BETWEEN_RRSP_INDIV_AND_RRSP_SPOUSAL_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_transfer_between_rrsp_indiv_and_rrsp_spousal_not_allowed();
			break;
		case 1701728: /* ERR_TRANSFER_CONTRARY_CLIENT_GUAGUARD_PROTECTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_transfer_contrary_client_guaguard_protection();
			break;
		case 1701729: /* ERR_TRANSFER_DEPOSIT_TYPE_NOT_APPLICABLE */
			conditionObj = new CIFast_IFast_ifastcbo_err_transfer_deposit_type_not_applicable();
			break;
		case 1701730: /* ERR_TRANSFER_DIFFERENT_TO_FROM_FUND_CLASS */
			conditionObj = new CIFast_IFast_ifastcbo_err_transfer_different_to_from_fund_class();
			break;
		case 1701731: /* ERR_TRANSFER_EXCH_STOPPED_FOR_AT */
			conditionObj = new CIFast_IFast_ifastcbo_err_transfer_exch_stopped_for_at();
			break;
		case 1701732: /* ERR_TRANSFER_FUNDS_INVALID_FOR_TIK */
			conditionObj = new CIFast_IFast_ifastcbo_err_transfer_funds_invalid_for_tik();
			break;
		case 1701733: /* ERR_TRANSFER_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_transfer_not_allowed();
			break;
		case 1701734: /* ERR_TRANSFER_NOT_ALLOWED_CONTRACT_TYPE_AND_OR_VERSION_NOT_THE_SAME */
			conditionObj = new CIFast_IFast_ifastcbo_err_transfer_not_allowed_contract_type_and_or_version_not_the_same();
			break;
		case 1701735: /* ERR_TRANSFER_NOT_ALLOWED_INTO_THIS_FUND_CLASS */
			conditionObj = new CIFast_IFast_ifastcbo_err_transfer_not_allowed_into_this_fund_class();
			break;
		case 1701736: /* ERR_TRANSFER_OUT_NOT_ALLOWED_FOR_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_transfer_out_not_allowed_for_fund();
			break;
		case 1701737: /* ERR_TRANSFER_TAX_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_transfer_tax_type();
			break;
		case 1701738: /* ERR_TRANSFER_TO_ACCOUNT_IS_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_transfer_to_account_is_not_allowed();
			break;
		case 1701739: /* ERR_TRANSFER_TO_LIRA_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_transfer_to_lira_not_allowed();
			break;
		case 1701740: /* ERR_TRANSFER_TO_LIRA_NOT_ALLOWED_FOR_SHAREHOLDER_69 */
			conditionObj = new CIFast_IFast_ifastcbo_err_transfer_to_lira_not_allowed_for_shareholder_69();
			break;
		case 1701741: /* ERR_TRANSFER_TO_LRSP_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_transfer_to_lrsp_not_allowed();
			break;
		case 1701742: /* ERR_TRANSFER_TO_LRSP_NOT_ALLOWED_FOR_SHAREHOLDER_69 */
			conditionObj = new CIFast_IFast_ifastcbo_err_transfer_to_lrsp_not_allowed_for_shareholder_69();
			break;
		case 1701743: /* ERR_TRANSFER_TO_PENSION_JURISDICTION_NOT_SAME */
			conditionObj = new CIFast_IFast_ifastcbo_err_transfer_to_pension_jurisdiction_not_same();
			break;
		case 1701744: /* ERR_TRANSFERIN_NOT_ALLOWED_FOR_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_transferin_not_allowed_for_fund();
			break;
		case 1701745: /* ERR_TRANSITNO_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastcbo_err_transitno_not_exist();
			break;
		case 1701746: /* ERR_TRANSITNO_NUMERIC */
			conditionObj = new CIFast_IFast_ifastcbo_err_transitno_numeric();
			break;
		case 1701747: /* ERR_TRANSITNO_TOO_BIG */
			conditionObj = new CIFast_IFast_ifastcbo_err_transitno_too_big();
			break;
		case 1701748: /* ERR_TRANSTYPE_DOES_NOT_MATCH */
			conditionObj = new CIFast_IFast_ifastcbo_err_transtype_does_not_match();
			break;
		case 1701749: /* ERR_TRFX_AGE_DIFF_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_trfx_age_diff_not_allowed();
			break;
		case 1701750: /* ERR_TRUST_ACCOUNT_NUMBER_FORMAT_IS_INVALID */
			conditionObj = new CIFast_IFast_ifastcbo_err_trust_account_number_format_is_invalid();
			break;
		case 1701751: /* ERR_TRUSTEE_ENTITY_SHOULD_BE_SETUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_trustee_entity_should_be_setup();
			break;
		case 1701752: /* ERR_TRUSTEE_INVALID_FOR_ACCT_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_trustee_invalid_for_acct_type();
			break;
		case 1701753: /* ERR_TRX_NOTINAL_BALANCE */
			conditionObj = new CIFast_IFast_ifastcbo_err_trx_notinal_balance();
			break;
		case 1701754: /* ERR_TRX_TIERED_AND_NON_TIERED_ACCOUNT_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_trx_tiered_and_non_tiered_account_not_allowed();
			break;
		case 1701755: /* ERR_TUP_CALCULATION_ERROR */
			conditionObj = new CIFast_IFast_ifastcbo_err_tup_calculation_error();
			break;
		case 1701756: /* ERR_TUP_ESTIMATED_UNITS */
			conditionObj = new CIFast_IFast_ifastcbo_err_tup_estimated_units();
			break;
		case 1701757: /* ERR_TUP_SHARES */
			conditionObj = new CIFast_IFast_ifastcbo_err_tup_shares();
			break;
		case 1701758: /* ERR_TWO_DECIMAL_POINT_ONLY */
			conditionObj = new CIFast_IFast_ifastcbo_err_two_decimal_point_only();
			break;
		case 1701759: /* ERR_UC_AMT_LESS_THAN_RES_AMT */
			conditionObj = new CIFast_IFast_ifastcbo_err_uc_amt_less_than_res_amt();
			break;
		case 1701760: /* ERR_UNABLE_GET_FEE_VALUE_RESP_GRANT */
			conditionObj = new CIFast_IFast_ifastcbo_err_unable_get_fee_value_resp_grant();
			break;
		case 1701761: /* ERR_UNABLE_TO_ADD_ESTATE_OF_DECEASED_TO_NON_ESTATE_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_unable_to_add_estate_of_deceased_to_non_estate_account();
			break;
		case 1701762: /* ERR_UNABLE_TO_CHANGE_ACCT_PORTFOLIO */
			conditionObj = new CIFast_IFast_ifastcbo_err_unable_to_change_acct_portfolio();
			break;
		case 1701763: /* ERR_UNABLE_TO_CHANGE_GROUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_unable_to_change_group();
			break;
		case 1701764: /* ERR_UNIT_NOT_FOR_ALLOCATION */
			conditionObj = new CIFast_IFast_ifastcbo_err_unit_not_for_allocation();
			break;
		case 1701765: /* ERR_UNIT_NOT_FOR_NET_REDEMPTIONS */
			conditionObj = new CIFast_IFast_ifastcbo_err_unit_not_for_net_redemptions();
			break;
		case 1701766: /* ERR_UNIT_PURCHASE_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_unit_purchase_not_allowed();
			break;
		case 1701767: /* ERR_UNKNOWN_ADDRESS_CODE */
			conditionObj = new CIFast_IFast_ifastcbo_err_unknown_address_code();
			break;
		case 1701768: /* ERR_UNSEIZABLE_ACCOUNT_TRANSFER */
			conditionObj = new CIFast_IFast_ifastcbo_err_unseizable_account_transfer();
			break;
		case 1701769: /* ERR_UNSETTLED_TRADES_WITH_AMS */
			conditionObj = new CIFast_IFast_ifastcbo_err_unsettled_trades_with_ams();
			break;
		case 1701770: /* ERR_UNVERIFIED_BANK */
			conditionObj = new CIFast_IFast_ifastcbo_err_unverified_bank();
			break;
		case 1701771: /* ERR_UNVERIFIED_BANK_INSTR */
			conditionObj = new CIFast_IFast_ifastcbo_err_unverified_bank_instr();
			break;
		case 1701772: /* ERR_UNVERIFIED_DELETED_BEING_DUPLICATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_unverified_deleted_being_duplicate();
			break;
		case 1701773: /* ERR_UPBOUND_LESS_THAN_LOWER_BOUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_upbound_less_than_lower_bound();
			break;
		case 1701774: /* ERR_USER_DEF_MAT_GREATER */
			conditionObj = new CIFast_IFast_ifastcbo_err_user_def_mat_greater();
			break;
		case 1701775: /* ERR_USER_DEF_MAT_LESS */
			conditionObj = new CIFast_IFast_ifastcbo_err_user_def_mat_less();
			break;
		case 1701776: /* ERR_USER_DEFINED_MATURITY_DATE_CANNOT_BE_BLANK */
			conditionObj = new CIFast_IFast_ifastcbo_err_user_defined_maturity_date_cannot_be_blank();
			break;
		case 1701777: /* ERR_USER_DEFINED_MATURITY_DATE_LESS_THAN_MATURITY_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_user_defined_maturity_date_less_than_maturity_date();
			break;
		case 1701778: /* ERR_USER_DEFINED_MATURITY_DATE_LESS_THAN_MIN_TERM */
			conditionObj = new CIFast_IFast_ifastcbo_err_user_defined_maturity_date_less_than_min_term();
			break;
		case 1701779: /* ERR_USER_DEFINED_MATURITY_DATE_SHOULD_BE_BETWEEN_MIN_MAX_AGE */
			conditionObj = new CIFast_IFast_ifastcbo_err_user_defined_maturity_date_should_be_between_min_max_age();
			break;
		case 1701780: /* ERR_USER_DEFINED_MATURITY_DATE_SHOULD_BE_GREATER_THAN_MIN_TERM */
			conditionObj = new CIFast_IFast_ifastcbo_err_user_defined_maturity_date_should_be_greater_than_min_term();
			break;
		case 1701781: /* ERR_USER_DOES_NOT_HAVE_PERMISSION_TO_ADD_EPP */
			conditionObj = new CIFast_IFast_ifastcbo_err_user_does_not_have_permission_to_add_epp();
			break;
		case 1701782: /* ERR_USER_MATURITY_DATE_EMPTY */
			conditionObj = new CIFast_IFast_ifastcbo_err_user_maturity_date_empty();
			break;
		case 1701783: /* ERR_VALUE_BETWEEN_0_AND_100 */
			conditionObj = new CIFast_IFast_ifastcbo_err_value_between_0_and_100();
			break;
		case 1701784: /* ERR_VALUE_BETWEEN_TWO_REOCRDS */
			conditionObj = new CIFast_IFast_ifastcbo_err_value_between_two_reocrds();
			break;
		case 1701785: /* ERR_VALUE_CANNOT_BE_MINUS */
			conditionObj = new CIFast_IFast_ifastcbo_err_value_cannot_be_minus();
			break;
		case 1701786: /* ERR_VALUE_CANNOT_BE_ZERO */
			conditionObj = new CIFast_IFast_ifastcbo_err_value_cannot_be_zero();
			break;
		case 1701787: /* ERR_VALUE_DATE_EARLIER_THAN_CYCLE */
			conditionObj = new CIFast_IFast_ifastcbo_err_value_date_earlier_than_cycle();
			break;
		case 1701788: /* ERR_VALUE_NOT_EQUAL_100_PER */
			conditionObj = new CIFast_IFast_ifastcbo_err_value_not_equal_100_per();
			break;
		case 1701789: /* ERR_VALUE_ZERO */
			conditionObj = new CIFast_IFast_ifastcbo_err_value_zero();
			break;
		case 1701790: /* ERR_VALUEDATE_CANNOT_EARLIER_THAN_CURRENT_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_valuedate_cannot_earlier_than_current_date();
			break;
		case 1701791: /* ERR_VARIABLE_DSC_FEE_AMOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_variable_dsc_fee_amount();
			break;
		case 1701792: /* ERR_W_ENTITY_AGE_OVER_69 */
			conditionObj = new CIFast_IFast_ifastcbo_err_w_entity_age_over_69();
			break;
		case 1701793: /* ERR_W_ID_VALUE_IS_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_w_id_value_is_missing();
			break;
		case 1701794: /* ERR_W_INVALID_ID_VALUE */
			conditionObj = new CIFast_IFast_ifastcbo_err_w_invalid_id_value();
			break;
		case 1701795: /* ERR_W_INVALID_SIN */
			conditionObj = new CIFast_IFast_ifastcbo_err_w_invalid_sin();
			break;
		case 1701796: /* ERR_W_SIN_IS_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_w_sin_is_missing();
			break;
		case 1701797: /* ERR_W8_W9_CANNOT_CREATE_MANUALLY */
			conditionObj = new CIFast_IFast_ifastcbo_err_w8_w9_cannot_create_manually();
			break;
		case 1701798: /* ERR_WAIVE_PAPER_CANNOT_BE_YES */
			conditionObj = new CIFast_IFast_ifastcbo_err_waive_paper_cannot_be_yes();
			break;
		case 1701799: /* ERR_WARN_ACCOUNT_OWNER_AGE_OVER_69 */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_account_owner_age_over_69();
			break;
		case 1701800: /* ERR_WARN_ACCOUNT_REDEMPTION_FLAG_ENABLED */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_account_redemption_flag_enabled();
			break;
		case 1701801: /* ERR_WARN_ACCOUNT_TYPE_MUST_BE_INDIVIDUAL_FOR_RIF_LRIF_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_account_type_must_be_individual_for_rif_lrif_account();
			break;
		case 1701802: /* ERR_WARN_ACCOUNT_TYPE_MUST_BE_INDIVIDUAL_SPOUSE */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_account_type_must_be_individual_spouse();
			break;
		case 1701803: /* ERR_WARN_ACCT_ASSIGNED_COMMITTEE_POWERATTNY */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_acct_assigned_committee_powerattny();
			break;
		case 1701804: /* ERR_WARN_ACCT_LOCKED_NO_REDEMPTION_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_acct_locked_no_redemption_available();
			break;
		case 1701805: /* ERR_WARN_ACCTHOLDER_BIRTHDAY_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_acctholder_birthday_missing();
			break;
		case 1701806: /* ERR_WARN_ACCTHOLDER_BIRTHDAY_MISSING_NOCHECK */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_acctholder_birthday_missing_nocheck();
			break;
		case 1701807: /* ERR_WARN_AS_PENSION_ACCT */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_as_pension_acct();
			break;
		case 1701808: /* ERR_WARN_AS_PENSION_ELIGIBLE */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_as_pension_eligible();
			break;
		case 1701809: /* ERR_WARN_ASSIGNMENT_REDEEM_NOT_ALLOW */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_assignment_redeem_not_allow();
			break;
		case 1701810: /* ERR_WARN_CANNOT_TRANSFER_FROM_RRIF */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_cannot_transfer_from_rrif();
			break;
		case 1701811: /* ERR_WARN_CANNOT_TRANSFER_TO_DIFF */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_cannot_transfer_to_diff();
			break;
		case 1701812: /* ERR_WARN_CERT_UNITS_EXISTS */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_cert_units_exists();
			break;
		case 1701813: /* ERR_WARN_CLIENT_BIRTHDAY_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_client_birthday_missing();
			break;
		case 1701814: /* ERR_WARN_CONTRACT_ACCT_STATUS_ACTIVE */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_contract_acct_status_active();
			break;
		case 1701815: /* ERR_WARN_CONTRACT_ACCT_STATUS_INACTIVE */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_contract_acct_status_inactive();
			break;
		case 1701816: /* ERR_WARN_DATE_OF_BIRTH_REQUIRED_FOR_CASH_REDEMPTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_date_of_birth_required_for_cash_redemption();
			break;
		case 1701817: /* ERR_WARN_DEATH_CLAIM_REDEMPTION_CODE */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_death_claim_redemption_code();
			break;
		case 1701818: /* ERR_WARN_DEPOSIT_TYPE_07_INDICATES_EXCESS_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_deposit_type_07_indicates_excess_fund();
			break;
		case 1701819: /* ERR_WARN_DUPLICATE_ALTACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_duplicate_altaccount();
			break;
		case 1701820: /* ERR_WARN_DUPLICATE_SYSTEMATIC */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_duplicate_systematic();
			break;
		case 1701821: /* ERR_WARN_ENTIRE_ACCT_ASSIGNED */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_entire_acct_assigned();
			break;
		case 1701822: /* ERR_WARN_ESCROW_AMT_EQUALS_HOLDING */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_escrow_amt_equals_holding();
			break;
		case 1701823: /* ERR_WARN_ESCROW_AMT_EXCESS_HOLDING */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_escrow_amt_excess_holding();
			break;
		case 1701824: /* ERR_WARN_ESCROW_UNITS_EXCESS_HOLDING */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_escrow_units_excess_holding();
			break;
		case 1701825: /* ERR_WARN_EX_AMT_MORE_THAN_HOLDING */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_ex_amt_more_than_holding();
			break;
		case 1701826: /* ERR_WARN_EXCHANGE_DIFFERENT_AS_FUND_ACCT */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_exchange_different_as_fund_acct();
			break;
		case 1701827: /* ERR_WARN_EXCHANGE_DIFFERENT_AS_NON_AS_FUND_ACCT */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_exchange_different_as_non_as_fund_acct();
			break;
		case 1701828: /* ERR_WARN_FOREIGN_FUND_CLASS_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_foreign_fund_class_required();
			break;
		case 1701829: /* ERR_WARN_FULL_MONEY_MARKET */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_full_money_market();
			break;
		case 1701830: /* ERR_WARN_FUND_CLASS_EXCHANGEIN_STOP_FLAG_ON */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_fund_class_exchangein_stop_flag_on();
			break;
		case 1701831: /* ERR_WARN_FUND_CLASS_EXCHANGEOUT_STOP_FLAG_ON */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_fund_class_exchangeout_stop_flag_on();
			break;
		case 1701832: /* ERR_WARN_FUND_CLASS_PAC_STOP_FLAG_ON */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_fund_class_pac_stop_flag_on();
			break;
		case 1701833: /* ERR_WARN_FUND_CLASS_PURCHASE_STOP_FLAG_ON */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_fund_class_purchase_stop_flag_on();
			break;
		case 1701834: /* ERR_WARN_FUND_CLASS_REDEMPTION_STOP_FLAG_ON */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_fund_class_redemption_stop_flag_on();
			break;
		case 1701835: /* ERR_WARN_FUND_CLASS_SWP_STOP_FLAG_ON */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_fund_class_swp_stop_flag_on();
			break;
		case 1701836: /* ERR_WARN_FUND_CLASS_SYSGENTRFIN_STOP_FLAG_ON */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_fund_class_sysgentrfin_stop_flag_on();
			break;
		case 1701837: /* ERR_WARN_FUND_CLASS_SYSGENTRFOUT_STOP_FLAG_ON */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_fund_class_sysgentrfout_stop_flag_on();
			break;
		case 1701838: /* ERR_WARN_FUND_CLASS_TRANSFERIN_STOP_FLAG_ON */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_fund_class_transferin_stop_flag_on();
			break;
		case 1701839: /* ERR_WARN_FUND_CLASS_TRANSFEROUT_STOP_FLAG_ON */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_fund_class_transferout_stop_flag_on();
			break;
		case 1701840: /* ERR_WARN_FUND_IN_FOREIGN_CURRENCY */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_fund_in_foreign_currency();
			break;
		case 1701841: /* ERR_WARN_HAS_NO_SETTLE_PERMISSION */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_has_no_settle_permission();
			break;
		case 1701842: /* ERR_WARN_IN_KIND_TRANS_ACB */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_in_kind_trans_acb();
			break;
		case 1701843: /* ERR_WARN_INVALID_DEALER_FOR_ORDER_SETTLEMENT_BY_INTERMEDIARY */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_invalid_dealer_for_order_settlement_by_intermediary();
			break;
		case 1701844: /* ERR_WARN_INVALID_INTERMEDIARY_FOR_MONEY_MARKET_WIRE_ORDERS */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_invalid_intermediary_for_money_market_wire_orders();
			break;
		case 1701845: /* ERR_WARN_INVALID_INTERMEDIARY_FOR_WIRE_ORDERS */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_invalid_intermediary_for_wire_orders();
			break;
		case 1701846: /* ERR_WARN_INVALID_ORDERSRC_FOR_ACCT_DESIGNATION */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_invalid_ordersrc_for_acct_designation();
			break;
		case 1701847: /* ERR_WARN_INVALID_SETTLEMENT_TYPE_FOR_DEALER_OR_INTERMEDIARY */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_invalid_settlement_type_for_dealer_or_intermediary();
			break;
		case 1701848: /* ERR_WARN_LAST_QUARTER_AS_PENSION */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_last_quarter_as_pension();
			break;
		case 1701849: /* ERR_WARN_LLP_REPAYMENT_EXCEED */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_llp_repayment_exceed();
			break;
		case 1701850: /* ERR_WARN_LLP_REPAYMENT_PREVENT */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_llp_repayment_prevent();
			break;
		case 1701851: /* ERR_WARN_MAXMIN_AMT_RECALCULATION */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_maxmin_amt_recalculation();
			break;
		case 1701852: /* ERR_WARN_MAYBE_MIN_ACCOUNT_BALANCE */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_maybe_min_account_balance();
			break;
		case 1701853: /* ERR_WARN_MAYBE_MIN_FUND_BALANCE */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_maybe_min_fund_balance();
			break;
		case 1701854: /* ERR_WARN_MAYBE_MIN_INIT_PURCHASE */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_maybe_min_init_purchase();
			break;
		case 1701855: /* ERR_WARN_MAYBE_MIN_INIT_REDEMPTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_maybe_min_init_redemption();
			break;
		case 1701856: /* ERR_WARN_MAYBE_MIN_SUBS_PURCHASE */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_maybe_min_subs_purchase();
			break;
		case 1701857: /* ERR_WARN_MAYBE_MIN_SUBS_REDEMPTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_maybe_min_subs_redemption();
			break;
		case 1701858: /* ERR_WARN_MIN_ACCOUNT_BALANCE */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_min_account_balance();
			break;
		case 1701859: /* ERR_WARN_MIN_FUND_BALANCE */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_min_fund_balance();
			break;
		case 1701860: /* ERR_WARN_MIN_INIT_PURCHASE */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_min_init_purchase();
			break;
		case 1701861: /* ERR_WARN_MIN_INIT_REDEMPTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_min_init_redemption();
			break;
		case 1701862: /* ERR_WARN_MIN_SUBS_PURCHASE */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_min_subs_purchase();
			break;
		case 1701863: /* ERR_WARN_MIN_SUBS_REDEMPTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_min_subs_redemption();
			break;
		case 1701864: /* ERR_WARN_MONTHEND_MATURITY_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_monthend_maturity_date();
			break;
		case 1701865: /* ERR_WARN_NEXT_PROC_DATE_AFTER_STOP_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_next_proc_date_after_stop_date();
			break;
		case 1701866: /* ERR_WARN_NEXT_PROC_DATE_BEFORE_EFFECTIVE_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_next_proc_date_before_effective_date();
			break;
		case 1701867: /* ERR_WARN_PENDING_TRADE_EXISTS */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_pending_trade_exists();
			break;
		case 1701868: /* ERR_WARN_PLANHOLDER_MINIMUM_AGE_LIMIT */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_planholder_minimum_age_limit();
			break;
		case 1701869: /* ERR_WARN_PRIMARY_BENEFICIARY_NOT_ENTERED */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_primary_beneficiary_not_entered();
			break;
		case 1701870: /* ERR_WARN_QUARTEREND_MATURITY_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_quarterend_maturity_date();
			break;
		case 1701871: /* ERR_WARN_RED_AMT_MORE_THAN_HOLDING */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_red_amt_more_than_holding();
			break;
		case 1701872: /* ERR_WARN_RIF_SameMonthLastProcDateAsCurBusDate */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_rif_samemonthlastprocdateascurbusdate();
			break;
		case 1701873: /* ERR_WARN_ROUND_FUND_CLASS_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_round_fund_class_required();
			break;
		case 1701874: /* ERR_WARN_SCHEDULED_PAYMENT_NOT_ENTERED */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_scheduled_payment_not_entered();
			break;
		case 1701875: /* ERR_WARN_SETTLEMENT_SOURCE_NOT_FOR_ACCT_DESIGNATION */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_settlement_source_not_for_acct_designation();
			break;
		case 1701876: /* ERR_WARN_SHAREHOLDER_YOUNGER_THAN_18 */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_shareholder_younger_than_18();
			break;
		case 1701877: /* ERR_WARN_SPLICCOMAMOUNT_IS_GREATER */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_spliccomamount_is_greater();
			break;
		case 1701878: /* ERR_WARN_SPOUSAL_CONSENT_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_spousal_consent_required();
			break;
		case 1701879: /* ERR_WARN_SPOUSAL_CONSENT_WAIVER_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_spousal_consent_waiver_required();
			break;
		case 1701880: /* ERR_WARN_SPOUSE_BIRTHDAY_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_spouse_birthday_missing();
			break;
		case 1701881: /* ERR_WARN_SWP_LESS_THAN_MINIMUM_ALLOW */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_swp_less_than_minimum_allow();
			break;
		case 1701882: /* ERR_WARN_SWP_STOP_FOR_ESCROW */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_swp_stop_for_escrow();
			break;
		case 1701883: /* ERR_WARN_TOTAL_REDEMPTION_EXCEEDS_MAXIMUM */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_total_redemption_exceeds_maximum();
			break;
		case 1701884: /* ERR_WARN_TRANSFER_TO_DIFF */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_transfer_to_diff();
			break;
		case 1701885: /* ERR_WARN_WRONG_COMBINATION_TAXTYPE_JURISDICTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_warn_wrong_combination_taxtype_jurisdiction();
			break;
		case 1701886: /* ERR_WARNING_ALL_FUND_TRANSFER */
			conditionObj = new CIFast_IFast_ifastcbo_err_warning_all_fund_transfer();
			break;
		case 1701887: /* ERR_WARNING_AMS_ALLOCATION_CHANGE */
			conditionObj = new CIFast_IFast_ifastcbo_err_warning_ams_allocation_change();
			break;
		case 1701888: /* ERR_WARNING_FUND_FOREIGN_CURRENCY */
			conditionObj = new CIFast_IFast_ifastcbo_err_warning_fund_foreign_currency();
			break;
		case 1701889: /* ERR_WHERE_USE_TYPE_ACCOUNT_INVALID */
			conditionObj = new CIFast_IFast_ifastcbo_err_where_use_type_account_invalid();
			break;
		case 1701890: /* ERR_WHERE_USE_TYPE_FUND_BROKER_INVALID */
			conditionObj = new CIFast_IFast_ifastcbo_err_where_use_type_fund_broker_invalid();
			break;
		case 1701891: /* ERR_WHERE_USE_TYPE_FUND_INVALID */
			conditionObj = new CIFast_IFast_ifastcbo_err_where_use_type_fund_invalid();
			break;
		case 1701892: /* ERR_WIRE_NUM_NOT_NUMERIC */
			conditionObj = new CIFast_IFast_ifastcbo_err_wire_num_not_numeric();
			break;
		case 1701893: /* ERR_WIRE_ORDER_NOT_ALLOWED_FOR_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_wire_order_not_allowed_for_fund();
			break;
		case 1701894: /* ERR_WIRE_ORDER_NUM_MUST_BE_NUMERIC */
			conditionObj = new CIFast_IFast_ifastcbo_err_wire_order_num_must_be_numeric();
			break;
		case 1701895: /* ERR_WIRE_ORDER_NUMBER_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_wire_order_number_required();
			break;
		case 1701896: /* ERR_WRAP_CANNOT_BE_REMOVED */
			conditionObj = new CIFast_IFast_ifastcbo_err_wrap_cannot_be_removed();
			break;
		case 1701897: /* ERR_WRONG_AMOUNT_TYPE_FOR_FULL_TRANSFER */
			conditionObj = new CIFast_IFast_ifastcbo_err_wrong_amount_type_for_full_transfer();
			break;
		case 1701898: /* ERR_WRONG_COMBINATION_TAXTYPE_JURISDICTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_wrong_combination_taxtype_jurisdiction();
			break;
		case 1701899: /* ERR_WRONG_FRACTION_FORMAT */
			conditionObj = new CIFast_IFast_ifastcbo_err_wrong_fraction_format();
			break;
		case 1701900: /* ERR_WRONG_INTCREDFREQ */
			conditionObj = new CIFast_IFast_ifastcbo_err_wrong_intcredfreq();
			break;
		case 1701901: /* ERR_WRONG_VERIFY_STATUS */
			conditionObj = new CIFast_IFast_ifastcbo_err_wrong_verify_status();
			break;
		case 1701902: /* ERR_YTD_CONTRIBUTION_WILL_BE_NEGATIVE */
			conditionObj = new CIFast_IFast_ifastcbo_err_ytd_contribution_will_be_negative();
			break;
		case 1701903: /* ERR_ZERO_AMOUNT_ALL_FREE_UNITS */
			conditionObj = new CIFast_IFast_ifastcbo_err_zero_amount_all_free_units();
			break;
		case 1701904: /* IFASTCBO_CND_VERSION */
			conditionObj = new CIFast_IFast_ifastcbo_ifastcbo_cnd_version();
			break;
		case 1701905: /* INFO_SERVICE_AGENT_CHANGED */
			conditionObj = new CIFast_IFast_ifastcbo_info_service_agent_changed();
			break;
		case 1701906: /* INFO_SHAREHOLDER_HAS_MULTIPLE_ADDRESSES */
			conditionObj = new CIFast_IFast_ifastcbo_info_shareholder_has_multiple_addresses();
			break;
		case 1701907: /* OBJECT_DOES_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastcbo_object_does_not_exist();
			break;
		case 1701908: /* WAR_BRANCH_CODE_HAS_TO_BE_5 */
			conditionObj = new CIFast_IFast_ifastcbo_war_branch_code_has_to_be_5();
			break;
		case 1701909: /* WAR_BROKER_CODE_HAS_TO_BE_5 */
			conditionObj = new CIFast_IFast_ifastcbo_war_broker_code_has_to_be_5();
			break;
		case 1701910: /* WAR_SALS_CODE_HAS_TO_BE_5 */
			conditionObj = new CIFast_IFast_ifastcbo_war_sals_code_has_to_be_5();
			break;
		case 1701911: /* WARN_ACCOUNT_ATTATCHED_TFR_NEED_TO_BE_STOPPED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_account_attatched_tfr_need_to_be_stopped();
			break;
		case 1701912: /* WARN_ACCOUNT_ESCROW_FLAG_IS_ACTIVE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_account_escrow_flag_is_active();
			break;
		case 1701913: /* WARN_ACCOUNT_HAS_STOP_REDEMPTION */
			conditionObj = new CIFast_IFast_ifastcbo_warn_account_has_stop_redemption();
			break;
		case 1701914: /* WARN_ACCOUNT_IS_BEING_ACTIVATED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_account_is_being_activated();
			break;
		case 1701915: /* WARN_ACCOUNT_NOTINALS_ARE_ZERO */
			conditionObj = new CIFast_IFast_ifastcbo_warn_account_notinals_are_zero();
			break;
		case 1701916: /* WARN_ACCOUNTS_HAVE_DIFFERENT_SIBLINGONLY_STATUS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_accounts_have_different_siblingonly_status();
			break;
		case 1701917: /* WARN_ACCT_ASSIGNED_AMCU */
			conditionObj = new CIFast_IFast_ifastcbo_warn_acct_assigned_amcu();
			break;
		case 1701918: /* WARN_ACCT_ASSIGNED_CDIC_FULL_HOLD */
			conditionObj = new CIFast_IFast_ifastcbo_warn_acct_assigned_cdic_full_hold();
			break;
		case 1701919: /* WARN_ACCT_ASSIGNED_CDIC_PARTIAL_HOLD */
			conditionObj = new CIFast_IFast_ifastcbo_warn_acct_assigned_cdic_partial_hold();
			break;
		case 1701920: /* WARN_ACCT_ASSIGNED_CHEQUE_HOLDBACK */
			conditionObj = new CIFast_IFast_ifastcbo_warn_acct_assigned_cheque_holdback();
			break;
		case 1701921: /* WARN_ACCT_ASSIGNED_CONVERTED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_acct_assigned_converted();
			break;
		case 1701922: /* WARN_ACCT_ASSIGNED_CQ */
			conditionObj = new CIFast_IFast_ifastcbo_warn_acct_assigned_cq();
			break;
		case 1701923: /* WARN_ACCT_ASSIGNED_CURATEL */
			conditionObj = new CIFast_IFast_ifastcbo_warn_acct_assigned_curatel();
			break;
		case 1701924: /* WARN_ACCT_ASSIGNED_DPSP */
			conditionObj = new CIFast_IFast_ifastcbo_warn_acct_assigned_dpsp();
			break;
		case 1701925: /* WARN_ACCT_ASSIGNED_KEAN */
			conditionObj = new CIFast_IFast_ifastcbo_warn_acct_assigned_kean();
			break;
		case 1701926: /* WARN_ACCT_ASSIGNED_MEMO */
			conditionObj = new CIFast_IFast_ifastcbo_warn_acct_assigned_memo();
			break;
		case 1701927: /* WARN_ACCT_ASSIGNED_MI_FULL_HOLD */
			conditionObj = new CIFast_IFast_ifastcbo_warn_acct_assigned_mi_full_hold();
			break;
		case 1701928: /* WARN_ACCT_ASSIGNED_MI_PARTIAL_HOLD */
			conditionObj = new CIFast_IFast_ifastcbo_warn_acct_assigned_mi_partial_hold();
			break;
		case 1701929: /* WARN_ACCT_ASSIGNED_MORTGAGE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_acct_assigned_mortgage();
			break;
		case 1701930: /* WARN_ACCT_ASSIGNED_PAC_HOLDBACK */
			conditionObj = new CIFast_IFast_ifastcbo_warn_acct_assigned_pac_holdback();
			break;
		case 1701931: /* WARN_ACCT_ASSIGNED_VDAY */
			conditionObj = new CIFast_IFast_ifastcbo_warn_acct_assigned_vday();
			break;
		case 1701932: /* WARN_ACCT_CATEG_NAV_SHARE_LOTS_ADDED_PENDING_TRADES_EXIST */
			conditionObj = new CIFast_IFast_ifastcbo_warn_acct_categ_nav_share_lots_added_pending_trades_exist();
			break;
		case 1701933: /* WARN_ACCT_CATEG_NAV_SHARE_LOTS_DELETED_PENDING_TRADES_EXIST */
			conditionObj = new CIFast_IFast_ifastcbo_warn_acct_categ_nav_share_lots_deleted_pending_trades_exist();
			break;
		case 1701934: /* WARN_ACCT_CATEG_PUEV_SHOULD_BE_SETUP_BASED_ON_CLEARINGID */
			conditionObj = new CIFast_IFast_ifastcbo_warn_acct_categ_puev_should_be_setup_based_on_clearingid();
			break;
		case 1701935: /* WARN_ACCT_FROM_TRANSFER_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_acct_from_transfer_not_allowed();
			break;
		case 1701936: /* WARN_ACCT_MIN_ALLOWABLE_PURCHASE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_acct_min_allowable_purchase();
			break;
		case 1701937: /* WARN_ACCT_MIN_BALANCE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_acct_min_balance();
			break;
		case 1701938: /* WARN_ACCT_MIN_INIT_PURCHASE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_acct_min_init_purchase();
			break;
		case 1701939: /* WARN_ACCT_NO_HOLDINGS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_acct_no_holdings();
			break;
		case 1701940: /* WARN_ACCT_PURCHASE_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_acct_purchase_not_allowed();
			break;
		case 1701941: /* WARN_ACCT_REDEMPTION_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_acct_redemption_not_allowed();
			break;
		case 1701942: /* WARN_ACCT_SWITCH_TO_NON_NSCC_BROKER */
			conditionObj = new CIFast_IFast_ifastcbo_warn_acct_switch_to_non_nscc_broker();
			break;
		case 1701943: /* WARN_ACCT_SWITCH_TO_NSCC_BROKER */
			conditionObj = new CIFast_IFast_ifastcbo_warn_acct_switch_to_nscc_broker();
			break;
		case 1701944: /* WARN_ACCT_TO_TRANSFER_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_acct_to_transfer_not_allowed();
			break;
		case 1701945: /* WARN_ACCT_VALUE_RECORD_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastcbo_warn_acct_value_record_not_exist();
			break;
		case 1701946: /* WARN_ACCT_VALUE_ZERO */
			conditionObj = new CIFast_IFast_ifastcbo_warn_acct_value_zero();
			break;
		case 1701947: /* WARN_ACCTOUNTIBILITY_BACKDATEDREASON_ARE_REQUIRED_FOR_DILUTION */
			conditionObj = new CIFast_IFast_ifastcbo_warn_acctountibility_backdatedreason_are_required_for_dilution();
			break;
		case 1701948: /* WARN_ACTIVE_SWP_AMTTYPE_EXISTS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_active_swp_amttype_exists();
			break;
		case 1701949: /* WARN_ACTIVE_SWP_CONTTYPE_EXISTS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_active_swp_conttype_exists();
			break;
		case 1701950: /* WARN_ADDRESS_CODE_NOT_EFFECTIVE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_address_code_not_effective();
			break;
		case 1701951: /* WARN_ADDRESS_NOT_VERIFY */
			conditionObj = new CIFast_IFast_ifastcbo_warn_address_not_verify();
			break;
		case 1701952: /* WARN_ADJUSTMENT_MAY_BE_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_adjustment_may_be_required();
			break;
		case 1701953: /* WARN_AIP_TO_NONRESIDENT_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_aip_to_nonresident_not_allowed();
			break;
		case 1701954: /* WARN_AIP_WITHDRAWAL_EXISTS_TX_TO_ANOTHER_RESP_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_aip_withdrawal_exists_tx_to_another_resp_not_allowed();
			break;
		case 1701955: /* WARN_ALL_FUND_ACCRUAL */
			conditionObj = new CIFast_IFast_ifastcbo_warn_all_fund_accrual();
			break;
		case 1701956: /* WARN_ALLOC_AMT_EXCEEDS_INVESTMENT_ACCRUEDINT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_alloc_amt_exceeds_investment_accruedint();
			break;
		case 1701957: /* WARN_ALLOC_AMT_EXCEEDS_INVESTMENT_MV */
			conditionObj = new CIFast_IFast_ifastcbo_warn_alloc_amt_exceeds_investment_mv();
			break;
		case 1701958: /* WARN_ALLOC_AMT_EXCEEDS_INVESTMENT_REMAININGPRINCIPAL */
			conditionObj = new CIFast_IFast_ifastcbo_warn_alloc_amt_exceeds_investment_remainingprincipal();
			break;
		case 1701959: /* WARN_ALLOC_CHANGE_RATE_OF_RETURN */
			conditionObj = new CIFast_IFast_ifastcbo_warn_alloc_change_rate_of_return();
			break;
		case 1701960: /* WARN_ALTACCOUNT_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_warn_altaccount_missing();
			break;
		case 1701961: /* WARN_AMENDMENT_MAY_BE_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_amendment_may_be_required();
			break;
		case 1701962: /* WARN_AMOUNT_IS_LESS_THEN_MINIMUM_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_amount_is_less_then_minimum_required();
			break;
		case 1701963: /* WARN_AMOUNT_IS_OVER_THRESHOLD */
			conditionObj = new CIFast_IFast_ifastcbo_warn_amount_is_over_threshold();
			break;
		case 1701964: /* WARN_AMS_ACCOUNT_HOLD_GIC */
			conditionObj = new CIFast_IFast_ifastcbo_warn_ams_account_hold_gic();
			break;
		case 1701965: /* WARN_AMS_ACCT_SHOULD_CLONE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_ams_acct_should_clone();
			break;
		case 1701966: /* WARN_AMS_ACTIVE_CERTS_EXIST */
			conditionObj = new CIFast_IFast_ifastcbo_warn_ams_active_certs_exist();
			break;
		case 1701967: /* WARN_AMS_CANNOT_SETUP_FOR_ACCOUNT_HOLDING_MULTICURRENCY_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_warn_ams_cannot_setup_for_account_holding_multicurrency_fund();
			break;
		case 1701968: /* WARN_AMS_ESCROW_FOR_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_ams_escrow_for_account();
			break;
		case 1701969: /* WARN_AMS_GAP_BETWEEN_RECCORDS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_ams_gap_between_reccords();
			break;
		case 1701970: /* WARN_AMS_MKT_REBALANCING_LIMITATION_RULE_NOT_MET */
			conditionObj = new CIFast_IFast_ifastcbo_warn_ams_mkt_rebalancing_limitation_rule_not_met();
			break;
		case 1701971: /* WARN_AMS_SETUP_FOR_PAC */
			conditionObj = new CIFast_IFast_ifastcbo_warn_ams_setup_for_pac();
			break;
		case 1701972: /* WARN_AMS_SETUP_FOR_SWP */
			conditionObj = new CIFast_IFast_ifastcbo_warn_ams_setup_for_swp();
			break;
		case 1701973: /* WARN_AMS_SETUP_NOT_ALLOWED_FOR_INSTITUTIONAL */
			conditionObj = new CIFast_IFast_ifastcbo_warn_ams_setup_not_allowed_for_institutional();
			break;
		case 1701974: /* WARN_AMS_SETUP_NOT_ALLOWED_FOR_INSTITUTIONAL_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_ams_setup_not_allowed_for_institutional_account();
			break;
		case 1701975: /* WARN_AMS_SETUP_NOT_ALLOWED_IF_STOP_PURCH_REDEM */
			conditionObj = new CIFast_IFast_ifastcbo_warn_ams_setup_not_allowed_if_stop_purch_redem();
			break;
		case 1701976: /* WARN_ANNUAL_CONTRIB_LIMITS_NOT_SETUP */
			conditionObj = new CIFast_IFast_ifastcbo_warn_annual_contrib_limits_not_setup();
			break;
		case 1701977: /* WARN_APPLICABLE_ACCT_LEVEL_STOP_FLAG_MUST_BE_RELEASED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_applicable_acct_level_stop_flag_must_be_released();
			break;
		case 1701978: /* WARN_ASSISTED_AMT_IS_ZERO */
			conditionObj = new CIFast_IFast_ifastcbo_warn_assisted_amt_is_zero();
			break;
		case 1701979: /* WARN_ASSISTED_CONTRIBUTION_AMOUNT_MORE_THAN_AVAILABLE_ASSISTED_AMOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_assisted_contribution_amount_more_than_available_assisted_amount();
			break;
		case 1701980: /* WARN_ASSISTED_CONTRIBUTION_AMOUNT_MORE_THAN_UNASSISTED_AMOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_assisted_contribution_amount_more_than_unassisted_amount();
			break;
		case 1701981: /* WARN_ASSISTED_VALUE_IS_ZERO */
			conditionObj = new CIFast_IFast_ifastcbo_warn_assisted_value_is_zero();
			break;
		case 1701982: /* WARN_ASSOCIATED_ENTITY_NOT_PROVIDED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_associated_entity_not_provided();
			break;
		case 1701983: /* WARN_ASSOCIATED_GRANT_TRADE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_associated_grant_trade();
			break;
		case 1701984: /* WARN_BACK_DATE_TRADE_NOT_ALLOWED_BEFORE_LWA */
			conditionObj = new CIFast_IFast_ifastcbo_warn_back_date_trade_not_allowed_before_lwa();
			break;
		case 1701985: /* WARN_BALANCE_LESS_THEN_ENTERED_TRANS_AMOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_balance_less_then_entered_trans_amount();
			break;
		case 1701986: /* WARN_BALANCE_LESS_THEN_TRANS_AMOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_balance_less_then_trans_amount();
			break;
		case 1701987: /* WARN_BANK_COUNTRY_CODE_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_bank_country_code_required();
			break;
		case 1701988: /* WARN_BANK_IN_USE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_bank_in_use();
			break;
		case 1701989: /* WARN_BANK_INSTRUCTIONS_OVERLAP */
			conditionObj = new CIFast_IFast_ifastcbo_warn_bank_instructions_overlap();
			break;
		case 1701990: /* WARN_BANKING_IDYPE_MANDATORY_FOR_PAC */
			conditionObj = new CIFast_IFast_ifastcbo_warn_banking_idype_mandatory_for_pac();
			break;
		case 1701991: /* WARN_BATCH_NAME_HAS_BEEN_CHANGED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_batch_name_has_been_changed();
			break;
		case 1701992: /* WARN_BENEF_ADDRESS_IS_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_warn_benef_address_is_missing();
			break;
		case 1701993: /* WARN_BENEF_NOT_ELIGIBLE_FOR_CLB */
			conditionObj = new CIFast_IFast_ifastcbo_warn_benef_not_eligible_for_clb();
			break;
		case 1701994: /* WARN_BENEF_VALIDATION */
			conditionObj = new CIFast_IFast_ifastcbo_warn_benef_validation();
			break;
		case 1701995: /* WARN_BENEFICIARY_IS_NOT_LINKED_TO_PCG */
			conditionObj = new CIFast_IFast_ifastcbo_warn_beneficiary_is_not_linked_to_pcg();
			break;
		case 1701996: /* WARN_BENEFICIARY_IS_OVER_18 */
			conditionObj = new CIFast_IFast_ifastcbo_warn_beneficiary_is_over_18();
			break;
		case 1701997: /* WARN_BENEFICIARY_NOT_ELIGIBLE_FOR_QESI_INCREASE_NOT_SIBLINGONLY */
			conditionObj = new CIFast_IFast_ifastcbo_warn_beneficiary_not_eligible_for_qesi_increase_not_siblingonly();
			break;
		case 1701998: /* WARN_BENEFICIARY_NOT_QUEBEC_RESIDENT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_beneficiary_not_quebec_resident();
			break;
		case 1701999: /* WARN_BENEFICIARY_NOT_SASKATCHEWAN_RESIDENT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_beneficiary_not_saskatchewan_resident();
			break;
		case 1702000: /* WARN_BLANK_CNTRY_OF_ISSUE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_blank_cntry_of_issue();
			break;
		case 1702001: /* WARN_BLANK_REG_STANDARD */
			conditionObj = new CIFast_IFast_ifastcbo_warn_blank_reg_standard();
			break;
		case 1702002: /* WARN_BRANCH_FROM_TRANSFER_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_branch_from_transfer_not_allowed();
			break;
		case 1702003: /* WARN_BRANCH_MIN_ALLOWABLE_PURCHASE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_branch_min_allowable_purchase();
			break;
		case 1702004: /* WARN_BRANCH_MIN_BALANCE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_branch_min_balance();
			break;
		case 1702005: /* WARN_BRANCH_MIN_INIT_PURCHASE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_branch_min_init_purchase();
			break;
		case 1702006: /* WARN_BRANCH_PURCHASE_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_branch_purchase_not_allowed();
			break;
		case 1702007: /* WARN_BRANCH_REDEMPTION_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_branch_redemption_not_allowed();
			break;
		case 1702008: /* WARN_BRANCH_TO_TRANSFER_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_branch_to_transfer_not_allowed();
			break;
		case 1702009: /* WARN_BRKBRREP_INACTIVE_CURRBUSDATE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_brkbrrep_inactive_currbusdate();
			break;
		case 1702010: /* WARN_BROKER_DIFFERENT_THAN_ACCOUNT_BROKER */
			conditionObj = new CIFast_IFast_ifastcbo_warn_broker_different_than_account_broker();
			break;
		case 1702011: /* WARN_BROKER_FROM_TRANSFER_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_broker_from_transfer_not_allowed();
			break;
		case 1702012: /* WARN_BROKER_MIN_ALLOWABLE_PURCHASE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_broker_min_allowable_purchase();
			break;
		case 1702013: /* WARN_BROKER_MIN_BALANCE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_broker_min_balance();
			break;
		case 1702014: /* WARN_BROKER_MIN_INIT_PURCHASE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_broker_min_init_purchase();
			break;
		case 1702015: /* WARN_BROKER_PAYMENT_FOR_SETUP_NOT_IN_PAIR */
			conditionObj = new CIFast_IFast_ifastcbo_warn_broker_payment_for_setup_not_in_pair();
			break;
		case 1702016: /* WARN_BROKER_PAYMENT_INSTRUCTIONS_FOR_DISTRIBUTION_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_warn_broker_payment_instructions_for_distribution_missing();
			break;
		case 1702017: /* WARN_BROKER_PAYMENT_INSTRUCTIONS_FOR_REDEMPTION_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_warn_broker_payment_instructions_for_redemption_missing();
			break;
		case 1702018: /* WARN_BROKER_PURCHASE_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_broker_purchase_not_allowed();
			break;
		case 1702019: /* WARN_BROKER_REDEMPTION_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_broker_redemption_not_allowed();
			break;
		case 1702020: /* WARN_BROKER_TO_TRANSFER_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_broker_to_transfer_not_allowed();
			break;
		case 1702021: /* WARN_CAN_TRANSFER_ONLY_TO_RRSP_RRIF */
			conditionObj = new CIFast_IFast_ifastcbo_warn_can_transfer_only_to_rrsp_rrif();
			break;
		case 1702022: /* WARN_CANCEL_BATCH_MUST_BE_PREFIXED_SP_DC */
			conditionObj = new CIFast_IFast_ifastcbo_warn_cancel_batch_must_be_prefixed_sp_dc();
			break;
		case 1702023: /* WARN_CANCEL_GUAR_ADJ_EXIST_FOR_ACCT_CONTRACT_AFTR_TRADE_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_cancel_guar_adj_exist_for_acct_contract_aftr_trade_date();
			break;
		case 1702024: /* WARN_CASH_DIVIDEND_PAID_AFTER */
			conditionObj = new CIFast_IFast_ifastcbo_warn_cash_dividend_paid_after();
			break;
		case 1702025: /* WARN_CASH_INSTR_NOT_ALLOWED_FOR_REG_ACC */
			conditionObj = new CIFast_IFast_ifastcbo_warn_cash_instr_not_allowed_for_reg_acc();
			break;
		case 1702026: /* WARN_CESG_AMOUNT_BE_RETURNED_BECAUSE_REDEMPTION */
			conditionObj = new CIFast_IFast_ifastcbo_warn_cesg_amount_be_returned_because_redemption();
			break;
		case 1702027: /* WARN_CESG_LIMIT_EXCEEDED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_cesg_limit_exceeded();
			break;
		case 1702028: /* WARN_CHANGE_CLEARINFID_PENDING */
			conditionObj = new CIFast_IFast_ifastcbo_warn_change_clearinfid_pending();
			break;
		case 1702029: /* WARN_CHANGE_REPS_IS_NOT_APPLICABLE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_change_reps_is_not_applicable();
			break;
		case 1702030: /* WARN_CHARGE_EARLY_REDEMPTION_FEE_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_charge_early_redemption_fee_allowed();
			break;
		case 1702031: /* WARN_CHARGE_SHORT_TERM_TRANSFER_FEE_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_charge_short_term_transfer_fee_allowed();
			break;
		case 1702032: /* WARN_CLB_AMOUNT_CANNOT_BE_TRANSFERED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_clb_amount_cannot_be_transfered();
			break;
		case 1702033: /* WARN_CLIENT_CONDITION_RATE_IS_ZERO */
			conditionObj = new CIFast_IFast_ifastcbo_warn_client_condition_rate_is_zero();
			break;
		case 1702034: /* WARN_CLNT_MTH_STMT_SHOULD_BELONG_ACCT_NON_MFDA */
			conditionObj = new CIFast_IFast_ifastcbo_warn_clnt_mth_stmt_should_belong_acct_non_mfda();
			break;
		case 1702035: /* WARN_CMD_LATER_THAN_LEGAL_MATURITY_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_cmd_later_than_legal_maturity_date();
			break;
		case 1702036: /* WARN_CNTRY_OF_ISSUE_IS_BLANK */
			conditionObj = new CIFast_IFast_ifastcbo_warn_cntry_of_issue_is_blank();
			break;
		case 1702037: /* WARN_COMPENSATION_AGENT_MUST_BE_CHANGED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_compensation_agent_must_be_changed();
			break;
		case 1702038: /* WARN_CONTR_MATURITY_RED_100_PERCENT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_contr_maturity_red_100_percent();
			break;
		case 1702039: /* WARN_CONTRACT_CLOSED_FOR_NEW_BUSINESS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_contract_closed_for_new_business();
			break;
		case 1702040: /* WARN_CONTRACT_TYPE_AND_VERSION_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_contract_type_and_version_required();
			break;
		case 1702041: /* WARN_CONTRIBUTION_NOT_ALLOWED_FOR_NON_RESIDENT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_contribution_not_allowed_for_non_resident();
			break;
		case 1702042: /* WARN_CORRESPONDING_DISTRIBUTION_PAYMENT_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_warn_corresponding_distribution_payment_missing();
			break;
		case 1702043: /* WARN_CORRESPONDING_REDEMPTION_PAYMENT_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_warn_corresponding_redemption_payment_missing();
			break;
		case 1702044: /* WARN_COUNTRY_OF_ISSUE_IS_REQUIRED_FOR_BUSINESS_NUMBER_AND_TRUST_NUMBER */
			conditionObj = new CIFast_IFast_ifastcbo_warn_country_of_issue_is_required_for_business_number_and_trust_number();
			break;
		case 1702045: /* WARN_CREATE_ESCROW */
			conditionObj = new CIFast_IFast_ifastcbo_warn_create_escrow();
			break;
		case 1702046: /* WARN_CURRENT_DATE_SUBSCRIBED_UNITS_INCLUDED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_current_date_subscribed_units_included();
			break;
		case 1702047: /* WARN_CUSTOM_TRADING_SCHEDULE_IS_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_warn_custom_trading_schedule_is_missing();
			break;
		case 1702048: /* WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_OEIC */
			conditionObj = new CIFast_IFast_ifastcbo_warn_data_update_impacts_external_env_oeic();
			break;
		case 1702049: /* WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_SICAV */
			conditionObj = new CIFast_IFast_ifastcbo_warn_data_update_impacts_external_env_sicav();
			break;
		case 1702050: /* WARN_DATE_MUST_BE_EQUAL_OR_EARLIER_THAN_2ND_DIPLOMA_COMM_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_date_must_be_equal_or_earlier_than_2nd_diploma_comm_date();
			break;
		case 1702051: /* WARN_DATE_MUST_BE_EQUAL_OR_GREATER_THAN_CURR_DATE_PLUS_3_BUSS_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_date_must_be_equal_or_greater_than_curr_date_plus_3_buss_date();
			break;
		case 1702052: /* WARN_DATE_OF_BIRTH_EMPTY */
			conditionObj = new CIFast_IFast_ifastcbo_warn_date_of_birth_empty();
			break;
		case 1702053: /* WARN_DAYS_BASIS_EMPTY */
			conditionObj = new CIFast_IFast_ifastcbo_warn_days_basis_empty();
			break;
		case 1702054: /* WARN_DEALER_INFO_MISSING_FOR_BROKER */
			conditionObj = new CIFast_IFast_ifastcbo_warn_dealer_info_missing_for_broker();
			break;
		case 1702055: /* WARN_DEATH_CLAIM_UPDATE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_death_claim_update();
			break;
		case 1702056: /* WARN_DEATH_SETTLEMENT_STAMPED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_death_settlement_stamped();
			break;
		case 1702057: /* WARN_DEAULT_SHARE_HOLDER_BANK_INFO_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastcbo_warn_deault_share_holder_bank_info_not_found();
			break;
		case 1702058: /* WARN_DEF_CONSOL_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_def_consol_type();
			break;
		case 1702059: /* WARN_DEFAULT_BANK_INFO_FOR_ACCT_DISTRIB_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastcbo_warn_default_bank_info_for_acct_distrib_not_found();
			break;
		case 1702060: /* WARN_DEFAULT_FUND_BRKR_REQUIRED_FOR_TRADE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_default_fund_brkr_required_for_trade();
			break;
		case 1702061: /* WARN_DEPOSIT_CODE_IS_APPLICABLE_FOR_SIBLING_ONLY_ACCOUNTS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_deposit_code_is_applicable_for_sibling_only_accounts();
			break;
		case 1702062: /* WARN_DEPOSIT_TYPE_40_CANNOT_BE_PLACED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_deposit_type_40_cannot_be_placed();
			break;
		case 1702063: /* WARN_DEPOSIT_TYPE_NOT_ALLOWED_FOR_REDCODE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_deposit_type_not_allowed_for_redcode();
			break;
		case 1702064: /* WARN_DEPTYPE_REDCODE_CAN_ONLY_BE_USED_FOR_RESP_TO_RESP_TX */
			conditionObj = new CIFast_IFast_ifastcbo_warn_deptype_redcode_can_only_be_used_for_resp_to_resp_tx();
			break;
		case 1702065: /* WARN_DEPTYPE_REDCODE_NOT_ALLOWED_IN_RESP_TO_RESP_TRANSFER */
			conditionObj = new CIFast_IFast_ifastcbo_warn_deptype_redcode_not_allowed_in_resp_to_resp_transfer();
			break;
		case 1702066: /* WARN_DEPTYPE_REDCODE_NOT_ALLOWED_IN_TRANSFER */
			conditionObj = new CIFast_IFast_ifastcbo_warn_deptype_redcode_not_allowed_in_transfer();
			break;
		case 1702067: /* WARN_DIFFERENT_ACCOUNTABLE_THAN_CANCELLATION_NOT_THROUGH_FUNDSERV */
			conditionObj = new CIFast_IFast_ifastcbo_warn_different_accountable_than_cancellation_not_through_fundserv();
			break;
		case 1702068: /* WARN_DIFFERENT_REG_AGENT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_different_reg_agent();
			break;
		case 1702069: /* WARN_DIFFERENT_SIBLINGONLY_STATUS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_different_siblingonly_status();
			break;
		case 1702070: /* WARN_DIFFERNT_SETTLESOURCE_THAN_CANCELLATION */
			conditionObj = new CIFast_IFast_ifastcbo_warn_differnt_settlesource_than_cancellation();
			break;
		case 1702071: /* WARN_DIRECT_DEPOSIT_BANK_INVESTOR_AUTHORIZE_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_warn_direct_deposit_bank_investor_authorize_missing();
			break;
		case 1702072: /* WARN_DIRECT_DEPOSIT_BNK_INFO_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_warn_direct_deposit_bnk_info_missing();
			break;
		case 1702073: /* WARN_DIRECT_DEPST_BANK_FOR_CAN_BANK_ONLY */
			conditionObj = new CIFast_IFast_ifastcbo_warn_direct_depst_bank_for_can_bank_only();
			break;
		case 1702074: /* WARN_DIRECT_DEPST_BANK_FOR_CAN_CUR_BANK_ACCT_ONLY */
			conditionObj = new CIFast_IFast_ifastcbo_warn_direct_depst_bank_for_can_cur_bank_acct_only();
			break;
		case 1702075: /* WARN_DIRECT_DEPST_SHRHLDR_ONLY */
			conditionObj = new CIFast_IFast_ifastcbo_warn_direct_depst_shrhldr_only();
			break;
		case 1702076: /* WARN_DISTRIBUTION_BULKING_BENEFICIAL */
			conditionObj = new CIFast_IFast_ifastcbo_warn_distribution_bulking_beneficial();
			break;
		case 1702077: /* WARN_DIV_TYPE_IS_NOT_AVAIL_FOR_FUNDCLASS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_div_type_is_not_avail_for_fundclass();
			break;
		case 1702078: /* WARN_DM_EVENT_HAS_OCCURED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_dm_event_has_occured();
			break;
		case 1702079: /* WARN_DMD_LATER_THAN_LEGAL_MATURITY_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_dmd_later_than_legal_maturity_date();
			break;
		case 1702080: /* WARN_DOB_RESP_BENEF_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_dob_resp_benef_required();
			break;
		case 1702081: /* WARN_DOCLIST_UPDATE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_doclist_update();
			break;
		case 1702082: /* WARN_DOD_ENTITY_TYPE_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_warn_dod_entity_type_missing();
			break;
		case 1702083: /* WARN_DUPLICATE_BICCODE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_duplicate_biccode();
			break;
		case 1702084: /* WARN_DUPLICATE_EFT_PURCHASE_CURRENCY */
			conditionObj = new CIFast_IFast_ifastcbo_warn_duplicate_eft_purchase_currency();
			break;
		case 1702085: /* WARN_DUPLICATE_EFT_REDEMPTION_CURRENCY */
			conditionObj = new CIFast_IFast_ifastcbo_warn_duplicate_eft_redemption_currency();
			break;
		case 1702086: /* WARN_DUPLICATE_HURDLE_ENTRY */
			conditionObj = new CIFast_IFast_ifastcbo_warn_duplicate_hurdle_entry();
			break;
		case 1702087: /* WARN_DUPLICATE_LOAN_NUM */
			conditionObj = new CIFast_IFast_ifastcbo_warn_duplicate_loan_num();
			break;
		case 1702088: /* WARN_DUPLICATE_LOAN_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_duplicate_loan_type();
			break;
		case 1702089: /* WARN_DUPLICATE_NEQ */
			conditionObj = new CIFast_IFast_ifastcbo_warn_duplicate_neq();
			break;
		case 1702090: /* WARN_DUPLICATE_PARENT_FUND_CLASS_WITH_ANOTHER_ACTIVE_AMS_MODEL */
			conditionObj = new CIFast_IFast_ifastcbo_warn_duplicate_parent_fund_class_with_another_active_ams_model();
			break;
		case 1702091: /* WARN_DUPLICATE_SIN */
			conditionObj = new CIFast_IFast_ifastcbo_warn_duplicate_sin();
			break;
		case 1702092: /* WARN_DUPLICATE_SIN_DIFFERENT_ENTITY */
			conditionObj = new CIFast_IFast_ifastcbo_warn_duplicate_sin_different_entity();
			break;
		case 1702093: /* WARN_EAP_AMOUNT_EXCEEDS_MARKET_VALUE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_eap_amount_exceeds_market_value();
			break;
		case 1702094: /* WARN_EAP_REDEMPT_EXCEEDED_EARNING */
			conditionObj = new CIFast_IFast_ifastcbo_warn_eap_redempt_exceeded_earning();
			break;
		case 1702095: /* WARN_EFFECTIVE_DATE_AFTER_STOP_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_effective_date_after_stop_date();
			break;
		case 1702096: /* WARN_EFFECTIVE_DATE_BACKWARD */
			conditionObj = new CIFast_IFast_ifastcbo_warn_effective_date_backward();
			break;
		case 1702097: /* WARN_EFFECTIVE_DATE_BEFORE_CURBUSDATE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_effective_date_before_curbusdate();
			break;
		case 1702098: /* WARN_EFT_PUR_CURRENCY_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_warn_eft_pur_currency_missing();
			break;
		case 1702099: /* WARN_EFT_RED_CURRENCY_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_warn_eft_red_currency_missing();
			break;
		case 1702100: /* WARN_EITHER_CUSTODY_TRADING_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_either_custody_trading_required();
			break;
		case 1702101: /* WARN_ELECTION_LWA_AGE_RATE_ALLOWED_ONLY_LWA_RATES_ARE_THE_SAME */
			conditionObj = new CIFast_IFast_ifastcbo_warn_election_lwa_age_rate_allowed_only_lwa_rates_are_the_same();
			break;
		case 1702102: /* WARN_ELIGIBLE_TRANSFER_FILED_IS_NO */
			conditionObj = new CIFast_IFast_ifastcbo_warn_eligible_transfer_filed_is_no();
			break;
		case 1702103: /* WARN_ELIGIBLE_TRANSFER_FLAG_CHANGED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_eligible_transfer_flag_changed();
			break;
		case 1702104: /* WARN_EMPLOYEE_AGENT_BONUS_PURCHASE_ONLY_APPLICABLE_FOR_EMPLOY_AGENT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_employee_agent_bonus_purchase_only_applicable_for_employ_agent();
			break;
		case 1702105: /* WARN_EMPLOYEE_AGENT_BONUS_PURCHASE_ONLY_APPLICABLE_FOR_SEG_FUNDS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_employee_agent_bonus_purchase_only_applicable_for_seg_funds();
			break;
		case 1702106: /* WARN_EMPLOYEE_AGENT_NOT_ALLOW_FOR_BALANCE_ACCT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_employee_agent_not_allow_for_balance_acct();
			break;
		case 1702107: /* WARN_EMPLOYEE_AGENT_ONLY_APPICABLE_FOR_CLIENT_ACCT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_employee_agent_only_appicable_for_client_acct();
			break;
		case 1702108: /* WARN_EMPTY_AREA_CODE_PHONE_NUMBER */
			conditionObj = new CIFast_IFast_ifastcbo_warn_empty_area_code_phone_number();
			break;
		case 1702109: /* WARN_ENSURE_PAC_IS_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_ensure_pac_is_allowed();
			break;
		case 1702110: /* WARN_ENTITY_ADDRESS_IS_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_warn_entity_address_is_missing();
			break;
		case 1702111: /* WARN_ENTITY_CATEGORY_IS_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_entity_category_is_required();
			break;
		case 1702112: /* WARN_ENTITY_NATIONALITY_BLANK */
			conditionObj = new CIFast_IFast_ifastcbo_warn_entity_nationality_blank();
			break;
		case 1702113: /* WARN_ERISA_PROHIBITED_FUND_CANNOT_BE_TRADED_IN_ERISA_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_erisa_prohibited_fund_cannot_be_traded_in_erisa_account();
			break;
		case 1702114: /* WARN_EVENT_RECIEPT_DATE_AND_TIME_EMPTY */
			conditionObj = new CIFast_IFast_ifastcbo_warn_event_reciept_date_and_time_empty();
			break;
		case 1702115: /* WARN_FEE_CODE_NOT_DEFINED_UNABLE_STORE_DEDUCTION_FEE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_fee_code_not_defined_unable_store_deduction_fee();
			break;
		case 1702116: /* WARN_FEE_MODEL_CODE_MUST_BELONG_TO_A_VALID_COMM_GROUP */
			conditionObj = new CIFast_IFast_ifastcbo_warn_fee_model_code_must_belong_to_a_valid_comm_group();
			break;
		case 1702117: /* WARN_FEE_MODEL_CODE_MUST_BELONG_TO_A_VALID_COMM_GROUP_OR_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_warn_fee_model_code_must_belong_to_a_valid_comm_group_or_fund();
			break;
		case 1702118: /* WARN_FEE_MODEL_DEFF_NOT_APPLIC_TO_ACCT_ASSOC */
			conditionObj = new CIFast_IFast_ifastcbo_warn_fee_model_deff_not_applic_to_acct_assoc();
			break;
		case 1702119: /* WARN_FEE_MODEL_OVERRIDDEN */
			conditionObj = new CIFast_IFast_ifastcbo_warn_fee_model_overridden();
			break;
		case 1702120: /* WARN_FEE_MODEL_STOP_DATE_NOT_APPLIC_TO_ACCT_ASSOC */
			conditionObj = new CIFast_IFast_ifastcbo_warn_fee_model_stop_date_not_applic_to_acct_assoc();
			break;
		case 1702121: /* WARN_FEECODE_NOT_APPLY_TO_MODELOPTION */
			conditionObj = new CIFast_IFast_ifastcbo_warn_feecode_not_apply_to_modeloption();
			break;
		case 1702122: /* WARN_FEETYPE_NOT_SUPPORTED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_feetype_not_supported();
			break;
		case 1702123: /* WARN_FIELD_IS_BLANK */
			conditionObj = new CIFast_IFast_ifastcbo_warn_field_is_blank();
			break;
		case 1702124: /* WARN_FIELD_REQUIRED_PLS_SELECT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_field_required_pls_select();
			break;
		case 1702125: /* WARN_FIRST_TRADE_MUST_BE_TRANSFER */
			conditionObj = new CIFast_IFast_ifastcbo_warn_first_trade_must_be_transfer();
			break;
		case 1702126: /* WARN_FROM_TO_CLASSES_NOT_BELONG_TO_SAME_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_warn_from_to_classes_not_belong_to_same_fund();
			break;
		case 1702127: /* WARN_FULL_REDEMPTION_NOT_ALLOW */
			conditionObj = new CIFast_IFast_ifastcbo_warn_full_redemption_not_allow();
			break;
		case 1702128: /* WARN_FULL_ROLLOVER_EXCHANGE_FOR_OMNIBUS_ACCT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_full_rollover_exchange_for_omnibus_acct();
			break;
		case 1702129: /* WARN_FUND_BROKER_INVESTRO_CAPABLE_WHILE_FUND_IS_NOT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_fund_broker_investro_capable_while_fund_is_not();
			break;
		case 1702130: /* WARN_FUND_CAPPED_AT_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_fund_capped_at_account();
			break;
		case 1702131: /* WARN_FUND_CAPPED_AT_FND_CLS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_fund_capped_at_fnd_cls();
			break;
		case 1702132: /* WARN_FUND_CLASS_AMOUNT_TRADE_STOP_FLAG_ON */
			conditionObj = new CIFast_IFast_ifastcbo_warn_fund_class_amount_trade_stop_flag_on();
			break;
		case 1702133: /* WARN_FUND_CLASS_CANNOT_PARENT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_fund_class_cannot_parent();
			break;
		case 1702134: /* WARN_FUND_CLASS_MUST_BE_AMS_PARENT_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_warn_fund_class_must_be_ams_parent_fund();
			break;
		case 1702135: /* WARN_FUND_CLASS_MUST_BE_PARENT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_fund_class_must_be_parent();
			break;
		case 1702136: /* WARN_FUND_CLASS_NOT_ALLOWED_TO_EXCHANGE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_fund_class_not_allowed_to_exchange();
			break;
		case 1702137: /* WARN_FUND_CLASS_NOT_ALLOWED_UNDER_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_fund_class_not_allowed_under_account();
			break;
		case 1702138: /* WARN_FUND_CLASS_NOT_AVAILABLE_FOR_PURCHASE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_fund_class_not_available_for_purchase();
			break;
		case 1702139: /* WARN_FUND_HAS_CERTIFICATE_UNITS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_fund_has_certificate_units();
			break;
		case 1702140: /* WARN_FUND_INVESTRO_CAPABLE_WHILE_FUND_BROKER_IS_NOT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_fund_investro_capable_while_fund_broker_is_not();
			break;
		case 1702141: /* WARN_FUND_LOAD_GRP_NOT_SAME_UNDER_AMS_ALLOC_SETUP */
			conditionObj = new CIFast_IFast_ifastcbo_warn_fund_load_grp_not_same_under_ams_alloc_setup();
			break;
		case 1702142: /* WARN_FUTURE_DATED_STOPDATE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_future_dated_stopdate();
			break;
		case 1702143: /* WARN_FX_RATE_IS_EMPTY */
			conditionObj = new CIFast_IFast_ifastcbo_warn_fx_rate_is_empty();
			break;
		case 1702144: /* WARN_GENDER_CANNOT_BE_BLANK_FOR_NMCR_SINGLE_LIFE_CONTRACT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_gender_cannot_be_blank_for_nmcr_single_life_contract();
			break;
		case 1702145: /* WARN_GENDER_CHANGE_NOT_ALLOWED_FOR_ELECTED_SINGLE_LIFE_NMCR_CONTRACT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_gender_change_not_allowed_for_elected_single_life_nmcr_contract();
			break;
		case 1702146: /* WARN_GENDER_REQUIRED_FOR_ENTITY_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_gender_required_for_entity_type();
			break;
		case 1702147: /* WARN_GI_FUND_IS_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_gi_fund_is_not_allowed();
			break;
		case 1702148: /* WARN_GMWB_PAYOPTION */
			conditionObj = new CIFast_IFast_ifastcbo_warn_gmwb_payoption();
			break;
		case 1702149: /* WARN_GRANT_AMOUNT_NOT_APPLICABLE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_grant_amount_not_applicable();
			break;
		case 1702150: /* WARN_GRANT_ASSOC_WITH_TRADE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_grant_assoc_with_trade();
			break;
		case 1702151: /* WARN_GRANT_REPAYMENT_NOT_REPORTED_HRDC */
			conditionObj = new CIFast_IFast_ifastcbo_warn_grant_repayment_not_reported_hrdc();
			break;
		case 1702152: /* WARN_GRANT_TRADE_DETAILS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_grant_trade_details();
			break;
		case 1702153: /* WARN_GROSS_REDEMPTION_MINIMUM_APPLIES */
			conditionObj = new CIFast_IFast_ifastcbo_warn_gross_redemption_minimum_applies();
			break;
		case 1702154: /* WARN_GUAGUARD_NOT_SAME_BETWEEN_TO_TI */
			conditionObj = new CIFast_IFast_ifastcbo_warn_guaguard_not_same_between_to_ti();
			break;
		case 1702155: /* WARN_GUARANTEE_ADJUSTMENT_EXISTS_AFTER_TRADE_DATE_INA */
			conditionObj = new CIFast_IFast_ifastcbo_warn_guarantee_adjustment_exists_after_trade_date_ina();
			break;
		case 1702156: /* WARN_GUARANTEE_OVERRIDE_FLAG_IS_NO */
			conditionObj = new CIFast_IFast_ifastcbo_warn_guarantee_override_flag_is_no();
			break;
		case 1702157: /* WARN_GUARANTEE_OVERRIDE_FLAG_IS_YES */
			conditionObj = new CIFast_IFast_ifastcbo_warn_guarantee_override_flag_is_yes();
			break;
		case 1702158: /* WARN_HOLD_ENT_EFFECTIVE_DATE_APPIES_TO_THE_TREE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_hold_ent_effective_date_appies_to_the_tree();
			break;
		case 1702159: /* WARN_HOLD_ENT_STOP_DATE_APPIES_TO_THE_TREE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_hold_ent_stop_date_appies_to_the_tree();
			break;
		case 1702160: /* WARN_HURDLE_BETWEEN_TWO_REOCRDS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_hurdle_between_two_reocrds();
			break;
		case 1702161: /* WARN_HURDLE_CALCULATED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_hurdle_calculated();
			break;
		case 1702162: /* WARN_HURDLE_RATE_ZERO */
			conditionObj = new CIFast_IFast_ifastcbo_warn_hurdle_rate_zero();
			break;
		case 1702163: /* WARN_IA_BRK_BRNCH_SLSREP_NOT_SAME_WITH_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_ia_brk_brnch_slsrep_not_same_with_account();
			break;
		case 1702164: /* WARN_ID_TYPE_IS_NOT_APPLICABLE_FOR_ENTITY_CATEGORY */
			conditionObj = new CIFast_IFast_ifastcbo_warn_id_type_is_not_applicable_for_entity_category();
			break;
		case 1702165: /* WARN_ID_TYPE_IS_REQUIRED_FOR_ENTITY_CATEGORY */
			conditionObj = new CIFast_IFast_ifastcbo_warn_id_type_is_required_for_entity_category();
			break;
		case 1702166: /* WARN_ID_TYPE_NOT_APPLICABLE_FOR_ACCOUNT_PROPRIETORY */
			conditionObj = new CIFast_IFast_ifastcbo_warn_id_type_not_applicable_for_account_proprietory();
			break;
		case 1702167: /* WARN_IDTYPE_FOR_COUNTRY_EXISTED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_idtype_for_country_existed();
			break;
		case 1702168: /* WARN_INELIG_RESP_TRANSFER_TRIGGER_GRANT_REPAYMENT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_inelig_resp_transfer_trigger_grant_repayment();
			break;
		case 1702169: /* WARN_INSUFFICENT_UNITS_FOR_UC_TRANSFER_TRADES */
			conditionObj = new CIFast_IFast_ifastcbo_warn_insufficent_units_for_uc_transfer_trades();
			break;
		case 1702170: /* WARN_INSUFFICIENT_QESI_GRANTS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_insufficient_qesi_grants();
			break;
		case 1702171: /* WARN_INTEREST_EXCEEDS_FIFTEEN */
			conditionObj = new CIFast_IFast_ifastcbo_warn_interest_exceeds_fifteen();
			break;
		case 1702172: /* WARN_INVALID_AGE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_invalid_age();
			break;
		case 1702173: /* WARN_INVALID_AREA_CODE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_invalid_area_code();
			break;
		case 1702174: /* WARN_INVALID_BROKER_FOR_MONEY_MARKET_WIRE_ORDERS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_invalid_broker_for_money_market_wire_orders();
			break;
		case 1702175: /* WARN_INVALID_BUSINESSNO */
			conditionObj = new CIFast_IFast_ifastcbo_warn_invalid_businessno();
			break;
		case 1702176: /* WARN_INVALID_CESG_REPAYMENT_REASON_CODE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_invalid_cesg_repayment_reason_code();
			break;
		case 1702177: /* WARN_INVALID_COMBINATION_ACCT_TYPE_ENTITY_CATEGORY */
			conditionObj = new CIFast_IFast_ifastcbo_warn_invalid_combination_acct_type_entity_category();
			break;
		case 1702178: /* WARN_INVALID_FUND_CODE_FOR_ACCT_CATEGORY_FUND_ON_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_warn_invalid_fund_code_for_acct_category_fund_on_fund();
			break;
		case 1702179: /* WARN_INVALID_FUND_NUMBER */
			conditionObj = new CIFast_IFast_ifastcbo_warn_invalid_fund_number();
			break;
		case 1702180: /* WARN_INVALID_GIIN_FORMAT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_invalid_giin_format();
			break;
		case 1702181: /* WARN_INVALID_HKID */
			conditionObj = new CIFast_IFast_ifastcbo_warn_invalid_hkid();
			break;
		case 1702182: /* WARN_INVALID_ISIN_NUMBER */
			conditionObj = new CIFast_IFast_ifastcbo_warn_invalid_isin_number();
			break;
		case 1702183: /* WARN_INVALID_MF_PAYMENT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_invalid_mf_payment();
			break;
		case 1702184: /* WARN_INVALID_NRIC */
			conditionObj = new CIFast_IFast_ifastcbo_warn_invalid_nric();
			break;
		case 1702185: /* WARN_INVALID_PCG_FOR_RESP_ACCOUNTHOLDER */
			conditionObj = new CIFast_IFast_ifastcbo_warn_invalid_pcg_for_resp_accountholder();
			break;
		case 1702186: /* WARN_INVALID_PHONE_FAX_NUMBER */
			conditionObj = new CIFast_IFast_ifastcbo_warn_invalid_phone_fax_number();
			break;
		case 1702187: /* WARN_INVALID_PROVINCE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_invalid_province();
			break;
		case 1702188: /* WARN_INVALID_WKN_NUMBER */
			conditionObj = new CIFast_IFast_ifastcbo_warn_invalid_wkn_number();
			break;
		case 1702189: /* WARN_INVALID_YEAR_RESP_OC_WITHDRAWAL */
			conditionObj = new CIFast_IFast_ifastcbo_warn_invalid_year_resp_oc_withdrawal();
			break;
		case 1702190: /* WARN_INVESTOR_AUTHORIZATION_INFO_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_warn_investor_authorization_info_missing();
			break;
		case 1702191: /* WARN_JURISDICTION_NOT_SAME_AS_SHRHLDR_JURISDICTION */
			conditionObj = new CIFast_IFast_ifastcbo_warn_jurisdiction_not_same_as_shrhldr_jurisdiction();
			break;
		case 1702192: /* WARN_KIID_ATTESTATION */
			conditionObj = new CIFast_IFast_ifastcbo_warn_kiid_attestation();
			break;
		case 1702193: /* WARN_LIFETIME_CONTRIB_LIMITS_NOT_SETUP */
			conditionObj = new CIFast_IFast_ifastcbo_warn_lifetime_contrib_limits_not_setup();
			break;
		case 1702194: /* WARN_LOAN_NUM_FOR_ACCTHOLDER */
			conditionObj = new CIFast_IFast_ifastcbo_warn_loan_num_for_acctholder();
			break;
		case 1702195: /* WARN_LOAN_NUM_MANDATORY */
			conditionObj = new CIFast_IFast_ifastcbo_warn_loan_num_mandatory();
			break;
		case 1702196: /* WARN_LOAN_NUMBER_FOR_ESCROW_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_loan_number_for_escrow_account();
			break;
		case 1702197: /* WARN_LOAN_TYPE_FOR_ESCROW */
			conditionObj = new CIFast_IFast_ifastcbo_warn_loan_type_for_escrow();
			break;
		case 1702198: /* WARN_LOAN_TYPE_MANDATORY */
			conditionObj = new CIFast_IFast_ifastcbo_warn_loan_type_mandatory();
			break;
		case 1702199: /* WARN_LOCKEDIN_TO_NON_LOCKEDIN_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_lockedin_to_non_lockedin_allowed();
			break;
		case 1702200: /* WARN_LOCKEDIN_TO_NON_REGISTED_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_lockedin_to_non_registed_allowed();
			break;
		case 1702201: /* WARN_LOSS_SITUATION */
			conditionObj = new CIFast_IFast_ifastcbo_warn_loss_situation();
			break;
		case 1702202: /* WARN_LSIF_REDEMPTION_NOT_ENOUGH_UNITS_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_lsif_redemption_not_enough_units_available();
			break;
		case 1702203: /* WARN_LWA_AGE_RATE_IS_NOT_APPLICABLE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_lwa_age_rate_is_not_applicable();
			break;
		case 1702204: /* WARN_LWA_ELECTION_DATE_LATER_THAN_TRANSFER_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_lwa_election_date_later_than_transfer_date();
			break;
		case 1702205: /* WARN_LWA_OPTION_NOT_MATCH */
			conditionObj = new CIFast_IFast_ifastcbo_warn_lwa_option_not_match();
			break;
		case 1702206: /* WARN_MAIL_CANNOT_BE_NO_FOR_NO_WAIVE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_mail_cannot_be_no_for_no_waive();
			break;
		case 1702207: /* WARN_MAIL_OPTION_CANNOT_BE_ALL_NO */
			conditionObj = new CIFast_IFast_ifastcbo_warn_mail_option_cannot_be_all_no();
			break;
		case 1702208: /* WARN_MARGIN_ACCT_LETTER_REQ */
			conditionObj = new CIFast_IFast_ifastcbo_warn_margin_acct_letter_req();
			break;
		case 1702209: /* WARN_MAX_PAYMENT_EXCEED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_max_payment_exceed();
			break;
		case 1702210: /* WARN_MAY_NEED_TO_ADD_NEW_GRANT_REQUEST_FOR_TAX_YEAR */
			conditionObj = new CIFast_IFast_ifastcbo_warn_may_need_to_add_new_grant_request_for_tax_year();
			break;
		case 1702211: /* WARN_MAY_NEED_TO_STOP_GRANT_REQUEST_FOR_TAX_YEAR */
			conditionObj = new CIFast_IFast_ifastcbo_warn_may_need_to_stop_grant_request_for_tax_year();
			break;
		case 1702212: /* WARN_MGMT_FEE_MODEL_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_warn_mgmt_fee_model_missing();
			break;
		case 1702213: /* WARN_MIN_TWO_FUNDS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_min_two_funds();
			break;
		case 1702214: /* WARN_MISSING_FUTURE_DEFAULT_SETTL_INSTR */
			conditionObj = new CIFast_IFast_ifastcbo_warn_missing_future_default_settl_instr();
			break;
		case 1702215: /* WARN_MISSING_NEQ */
			conditionObj = new CIFast_IFast_ifastcbo_warn_missing_neq();
			break;
		case 1702216: /* WARN_MULTIPLE_GIIN_NOT_ALLOWED_FOR_AN_ENTITY */
			conditionObj = new CIFast_IFast_ifastcbo_warn_multiple_giin_not_allowed_for_an_entity();
			break;
		case 1702217: /* WARN_MULTIPLE_NATIONAL_ID_NOT_ALLOWED_FOR_AN_ENTITY */
			conditionObj = new CIFast_IFast_ifastcbo_warn_multiple_national_id_not_allowed_for_an_entity();
			break;
		case 1702218: /* WARN_NEG_MM_CAN_BE_REINVESTED_ONLY_SAME_FUNDCLASS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_neg_mm_can_be_reinvested_only_same_fundclass();
			break;
		case 1702219: /* WARN_NEG_MONEY_MARKET_INTEREST_NOT_APPLICABLE_FOR_THIS_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_warn_neg_money_market_interest_not_applicable_for_this_fund();
			break;
		case 1702220: /* WARN_NET_ANNUAL_CONTRIBUTION_IS_ZERO */
			conditionObj = new CIFast_IFast_ifastcbo_warn_net_annual_contribution_is_zero();
			break;
		case 1702221: /* WARN_NET_REDEMPTION_OVER_MINIMUM */
			conditionObj = new CIFast_IFast_ifastcbo_warn_net_redemption_over_minimum();
			break;
		case 1702222: /* WARN_Net_SETTLEMENT_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_net_settlement_not_allowed();
			break;
		case 1702223: /* WARN_NET_TRANS_AMT_EXCEED_NET_CESG_OWNING */
			conditionObj = new CIFast_IFast_ifastcbo_warn_net_trans_amt_exceed_net_cesg_owning();
			break;
		case 1702224: /* WARN_NO_CHECK_ON_TAXRATE_FOR_NON_DOLLAR_AMTTYPE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_no_check_on_taxrate_for_non_dollar_amttype();
			break;
		case 1702225: /* WARN_NO_DIVTYPE_UNIT_RATE_EXISTS_FOR_THIS_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_no_divtype_unit_rate_exists_for_this_date();
			break;
		case 1702226: /* WARN_NO_LIFETIME_CONTRIB_LIMIT_SET_UP */
			conditionObj = new CIFast_IFast_ifastcbo_warn_no_lifetime_contrib_limit_set_up();
			break;
		case 1702227: /* WARN_NO_MAIL_TO_SUPPRESS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_no_mail_to_suppress();
			break;
		case 1702228: /* WARN_NO_MATCHING_BIC_CODE_FOUND */
			conditionObj = new CIFast_IFast_ifastcbo_warn_no_matching_bic_code_found();
			break;
		case 1702229: /* WARN_NO_ORIGINATING_CONTRIBUTION_SELECTED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_no_originating_contribution_selected();
			break;
		case 1702230: /* WARN_NO_RESP_BENEFICIARY_SELECTED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_no_resp_beneficiary_selected();
			break;
		case 1702231: /* WARN_NO_TRADING_SETTLEMENT_LOCATION */
			conditionObj = new CIFast_IFast_ifastcbo_warn_no_trading_settlement_location();
			break;
		case 1702232: /* WARN_NO_VALID_CONTRACT_FOR_ORIGINAL_TRADE_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_no_valid_contract_for_original_trade_date();
			break;
		case 1702233: /* WARN_NON_ASSOCIATED_BENEF_IS_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_non_associated_benef_is_not_allowed();
			break;
		case 1702234: /* WARN_NON_RECEIPT_FLAG_ACTIVE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_non_receipt_flag_active();
			break;
		case 1702235: /* WARN_NON_RESIDENT_TAX_JURID */
			conditionObj = new CIFast_IFast_ifastcbo_warn_non_resident_tax_jurid();
			break;
		case 1702236: /* WARN_NON_RESIDENT_TAX_JURISD_STOP_PAC */
			conditionObj = new CIFast_IFast_ifastcbo_warn_non_resident_tax_jurisd_stop_pac();
			break;
		case 1702237: /* WARN_NON_TRUSTEE_UPDATE_HIST_INFO_REQ */
			conditionObj = new CIFast_IFast_ifastcbo_warn_non_trustee_update_hist_info_req();
			break;
		case 1702238: /* WARN_NOT_ENOUGH_GRANT_AMOUNT_FOR_RETURN */
			conditionObj = new CIFast_IFast_ifastcbo_warn_not_enough_grant_amount_for_return();
			break;
		case 1702239: /* WARN_NS_DUPLICATE_BICCODE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_ns_duplicate_biccode();
			break;
		case 1702240: /* WARN_NSCC_PAYMENT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_nscc_payment();
			break;
		case 1702241: /* WARN_NSM_SETTLE_VALUE_IS_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_nsm_settle_value_is_not_allowed();
			break;
		case 1702242: /* WARN_OCCUPATION_EMPTY */
			conditionObj = new CIFast_IFast_ifastcbo_warn_occupation_empty();
			break;
		case 1702243: /* WARN_OFFSET_CUTOFFTIME_LATER_THAN_MARKET_CUTOFFTIME */
			conditionObj = new CIFast_IFast_ifastcbo_warn_offset_cutofftime_later_than_market_cutofftime();
			break;
		case 1702244: /* WARN_ONE_COMPENSATION_AGENT_IS_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_one_compensation_agent_is_allowed();
			break;
		case 1702245: /* WARN_ONHOLD_FLAG_FOR_APPLICABLE_ADDR_MUST_BE_RELEASED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_onhold_flag_for_applicable_addr_must_be_released();
			break;
		case 1702246: /* WARN_ONLY_10_CHARATERS_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_only_10_charaters_allowed();
			break;
		case 1702247: /* WARN_ONLY_RD_ALLOW_RESP_TRANSFER */
			conditionObj = new CIFast_IFast_ifastcbo_warn_only_rd_allow_resp_transfer();
			break;
		case 1702248: /* WARN_ORDERTYPE_DIRECT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_ordertype_direct();
			break;
		case 1702249: /* WARN_ORDERTYPE_WIRE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_ordertype_wire();
			break;
		case 1702250: /* WARN_ORIG_PLAN_DEFF_WILL_BE_CHANGED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_orig_plan_deff_will_be_changed();
			break;
		case 1702251: /* WARN_OVERRIDE_FED_TAX_RATE_LESS_THEN_DEFAULT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_override_fed_tax_rate_less_then_default();
			break;
		case 1702252: /* WARN_OVERRIDE_PROV_TAX_RATE_LESS_THEN_DEFAULT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_override_prov_tax_rate_less_then_default();
			break;
		case 1702253: /* WARN_PAC_LESS_THAN_MINIMUM_ALLOW */
			conditionObj = new CIFast_IFast_ifastcbo_warn_pac_less_than_minimum_allow();
			break;
		case 1702254: /* WARN_PAC_STOP_DATE_RESTRICTION */
			conditionObj = new CIFast_IFast_ifastcbo_warn_pac_stop_date_restriction();
			break;
		case 1702255: /* WARN_PARENT_FUND_CLASS_CANNOT_BE_A_PART_OF_ASSET_ALLOCATION_MIX */
			conditionObj = new CIFast_IFast_ifastcbo_warn_parent_fund_class_cannot_be_a_part_of_asset_allocation_mix();
			break;
		case 1702256: /* WARN_PAYINS_SHOULD_BE_EFT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_payins_should_be_eft();
			break;
		case 1702257: /* WARN_PAYMENT_STATUS_EMPTY */
			conditionObj = new CIFast_IFast_ifastcbo_warn_payment_status_empty();
			break;
		case 1702258: /* WARN_PAYMENT_STATUS_IS_OUTSTANDING */
			conditionObj = new CIFast_IFast_ifastcbo_warn_payment_status_is_outstanding();
			break;
		case 1702259: /* WARN_PAYOUT_AMOUNT_MAYBE_CHANGED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_payout_amount_maybe_changed();
			break;
		case 1702260: /* WARN_PCG_INST_BUSINESS_NUMBER_INVALID */
			conditionObj = new CIFast_IFast_ifastcbo_warn_pcg_inst_business_number_invalid();
			break;
		case 1702261: /* WARN_PCG_INST_BUSINESS_NUMBER_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_warn_pcg_inst_business_number_missing();
			break;
		case 1702262: /* WARN_PCG_MISSING_FOR_RESP_ACCOUNTHOLDER */
			conditionObj = new CIFast_IFast_ifastcbo_warn_pcg_missing_for_resp_accountholder();
			break;
		case 1702263: /* WARN_PENDING_OR_UNSETTLED_TRADE_EXISTS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_pending_or_unsettled_trade_exists();
			break;
		case 1702264: /* WARN_PENDING_TRADES_WITH_AMS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_pending_trades_with_ams();
			break;
		case 1702265: /* WARN_PENSION_AGE_LESS_THAN_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_pension_age_less_than_required();
			break;
		case 1702266: /* WARN_PLEASE_CANCEL_MONEY_OUT_TRANSACTION */
			conditionObj = new CIFast_IFast_ifastcbo_warn_please_cancel_money_out_transaction();
			break;
		case 1702267: /* WARN_PRIVATE_ACCOUNT_ACTEGORY_ONLY_FOR_CLIENT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_private_account_actegory_only_for_client();
			break;
		case 1702268: /* WARN_PROD_PORTFOLIO_RELATED_FIELDS_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_prod_portfolio_related_fields_required();
			break;
		case 1702269: /* WARN_PURC_RESP_NOT_SUPPORTED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_purc_resp_not_supported();
			break;
		case 1702270: /* WARN_PURCHASE_ANNUITANT_OLDER_THAN_LATEST_AGE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_purchase_annuitant_older_than_latest_age();
			break;
		case 1702271: /* WARN_PURCHASE_NON_BELL_FOR_DEPOSIT_27 */
			conditionObj = new CIFast_IFast_ifastcbo_warn_purchase_non_bell_for_deposit_27();
			break;
		case 1702272: /* WARN_PURCHASE_NOT_ALLOWED_FOR_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_warn_purchase_not_allowed_for_fund();
			break;
		case 1702273: /* WARN_QESI_AMOUNT_GREATER_THAN_10_PRCNT_OF_EXISTING_QESI_UNASSISTED_AMOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_qesi_amount_greater_than_10_prcnt_of_existing_qesi_unassisted_amount();
			break;
		case 1702274: /* WARN_QESI_BASIC_LIMIT_EXCEEDED_FOR_YEAR */
			conditionObj = new CIFast_IFast_ifastcbo_warn_qesi_basic_limit_exceeded_for_year();
			break;
		case 1702275: /* WARN_QESI_DP_RD_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_qesi_dp_rd_not_allowed();
			break;
		case 1702276: /* WARN_QESI_GRANT_REQUEST_NOT_AVAILABLE_FOR_BENEFICIARY */
			conditionObj = new CIFast_IFast_ifastcbo_warn_qesi_grant_request_not_available_for_beneficiary();
			break;
		case 1702277: /* WARN_QESI_INCREASE_LIMIT_EXCEEDED_FOR_YEAR */
			conditionObj = new CIFast_IFast_ifastcbo_warn_qesi_increase_limit_exceeded_for_year();
			break;
		case 1702278: /* WARN_QESI_LIFE_TIME_GRANT_LIMIT_EXCEEDED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_qesi_life_time_grant_limit_exceeded();
			break;
		case 1702279: /* WARN_QESI_LIMIT_EXCEEDED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_qesi_limit_exceeded();
			break;
		case 1702280: /* WARN_QESI_TOTAL_TRANSFER_FILED_IS_BLANK */
			conditionObj = new CIFast_IFast_ifastcbo_warn_qesi_total_transfer_filed_is_blank();
			break;
		case 1702281: /* WARN_RDR_ADVICE_UPDATED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_rdr_advice_updated();
			break;
		case 1702282: /* WARN_REBALANCING_STATUS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_rebalancing_status();
			break;
		case 1702283: /* WARN_RED_CODE_40_CANNOT_BE_PLACED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_red_code_40_cannot_be_placed();
			break;
		case 1702284: /* WARN_REDCODE_APPLICABLE_TO_STTRADING */
			conditionObj = new CIFast_IFast_ifastcbo_warn_redcode_applicable_to_sttrading();
			break;
		case 1702285: /* WARN_REDCODE_EMPTY */
			conditionObj = new CIFast_IFast_ifastcbo_warn_redcode_empty();
			break;
		case 1702286: /* WARN_REDEMP_CONTRARY_CLIENT_GUAGUARD_PROTECTION */
			conditionObj = new CIFast_IFast_ifastcbo_warn_redemp_contrary_client_guaguard_protection();
			break;
		case 1702287: /* WARN_REDEMPT_AMT_EXCEEDED_QESI_AMT_RECEIVED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_redempt_amt_exceeded_qesi_amt_received();
			break;
		case 1702288: /* WARN_REDEMPTION_AMOUNT_FOR_ADJUSTMENT_OF_QESI_BASIC_HAS_EXCEEDED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_redemption_amount_for_adjustment_of_qesi_basic_has_exceeded();
			break;
		case 1702289: /* WARN_REDEMPTION_AMOUNT_FOR_ADJUSTMENT_OF_QESI_INCREASE_HAS_EXCEEDED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_redemption_amount_for_adjustment_of_qesi_increase_has_exceeded();
			break;
		case 1702290: /* WARN_REDEMPTION_CODE_APPLICABLE_ONLY_FOR_NON_RESIDENT_BENEFICIARIES */
			conditionObj = new CIFast_IFast_ifastcbo_warn_redemption_code_applicable_only_for_non_resident_beneficiaries();
			break;
		case 1702291: /* WARN_REDEMPTION_CODE_IS_INVALID_BENEFICIARY_IS_NON_RESIDENT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_redemption_code_is_invalid_beneficiary_is_non_resident();
			break;
		case 1702292: /* WARN_REDEMPTION_CODE_IS_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_redemption_code_is_not_allowed();
			break;
		case 1702293: /* WARN_REDEMPTION_CODE_RULES_NOT_SETUP */
			conditionObj = new CIFast_IFast_ifastcbo_warn_redemption_code_rules_not_setup();
			break;
		case 1702294: /* WARN_REDEMPTION_EXCEED_REMAINING_CONTRIB */
			conditionObj = new CIFast_IFast_ifastcbo_warn_redemption_exceed_remaining_contrib();
			break;
		case 1702295: /* WARN_REDEMPTION_EXCEEDS_GRANT_PLUS_EARNINGS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_redemption_exceeds_grant_plus_earnings();
			break;
		case 1702296: /* WARN_REFERENCE_NO_IS_MANDATORY_FOR_SOURCE_OF_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_warn_reference_no_is_mandatory_for_source_of_fund();
			break;
		case 1702297: /* WARN_REFUND_OF_SPECIAL_TAXES_EXCEED_REDEMPTION */
			conditionObj = new CIFast_IFast_ifastcbo_warn_refund_of_special_taxes_exceed_redemption();
			break;
		case 1702298: /* WARN_REG_DOC_DEL_TAX_STAT_NEED_UPDATE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_reg_doc_del_tax_stat_need_update();
			break;
		case 1702299: /* WARN_REG_STANDARD_CHANGED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_reg_standard_changed();
			break;
		case 1702300: /* WARN_REGAGENT_BANKING_UNVERIFIED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_regagent_banking_unverified();
			break;
		case 1702301: /* WARN_REGULATORY_DOC_STATUS_NEEDS_TO_BE_MANUALLY_UPDATED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_regulatory_doc_status_needs_to_be_manually_updated();
			break;
		case 1702302: /* WARN_REMAIN_ACCT_BALANCE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_remain_acct_balance();
			break;
		case 1702303: /* WARN_REMAIN_AMOUNT_MUSTBE_PAID */
			conditionObj = new CIFast_IFast_ifastcbo_warn_remain_amount_mustbe_paid();
			break;
		case 1702304: /* WARN_REPORTING_FFI_IS_REQURIED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_reporting_ffi_is_requried();
			break;
		case 1702305: /* WARN_RESET_HAS_OCCURED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_reset_has_occured();
			break;
		case 1702306: /* WARN_RESP_BENEF_OVER21 */
			conditionObj = new CIFast_IFast_ifastcbo_warn_resp_benef_over21();
			break;
		case 1702307: /* WARN_RESP_BENEF_OVER31 */
			conditionObj = new CIFast_IFast_ifastcbo_warn_resp_benef_over31();
			break;
		case 1702308: /* WARN_RESP_BENEFICIARY_SIN_INVALID */
			conditionObj = new CIFast_IFast_ifastcbo_warn_resp_beneficiary_sin_invalid();
			break;
		case 1702309: /* WARN_RESP_BENEFICIARY_SIN_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_warn_resp_beneficiary_sin_missing();
			break;
		case 1702310: /* WARN_RESP_NASU_NOT_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_resp_nasu_not_available();
			break;
		case 1702311: /* WARN_RESP_PCG_INDIV_SIN_INVALID */
			conditionObj = new CIFast_IFast_ifastcbo_warn_resp_pcg_indiv_sin_invalid();
			break;
		case 1702312: /* WARN_RESP_PCG_INDIV_SIN_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_warn_resp_pcg_indiv_sin_missing();
			break;
		case 1702313: /* WARN_RESP_PLAN_LIMIT_EXCEEDED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_resp_plan_limit_exceeded();
			break;
		case 1702314: /* WARN_RESP_REDEMPTION_EXCEED_CONTRIBUTION */
			conditionObj = new CIFast_IFast_ifastcbo_warn_resp_redemption_exceed_contribution();
			break;
		case 1702315: /* WARN_RESP_REDEMPTION_EXCEED_EARNINGS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_resp_redemption_exceed_earnings();
			break;
		case 1702316: /* WARN_RESP_SPECIFIC_EDIT_CHECK_NOT_PERFORMED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_resp_specific_edit_check_not_performed();
			break;
		case 1702317: /* WARN_RESP_TRADE_NOT_ALLOW */
			conditionObj = new CIFast_IFast_ifastcbo_warn_resp_trade_not_allow();
			break;
		case 1702318: /* WARN_RESP_TRANSACTION_MIGHT_TRIGGER_GRANT_REPAYMENT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_resp_transaction_might_trigger_grant_repayment();
			break;
		case 1702319: /* WARN_RESP_TRANSFER_OUT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_resp_transfer_out();
			break;
		case 1702320: /* WARN_RESP_YEAR_LIMIT_EXCEEDED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_resp_year_limit_exceeded();
			break;
		case 1702321: /* WARN_RET_MAIL_CHANGED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_ret_mail_changed();
			break;
		case 1702322: /* WARN_RET_MAIL_CHANGED_CHANGE_HOLD_FLAG */
			conditionObj = new CIFast_IFast_ifastcbo_warn_ret_mail_changed_change_hold_flag();
			break;
		case 1702323: /* WARN_RETMAIL_REASON_IS_BLANK */
			conditionObj = new CIFast_IFast_ifastcbo_warn_retmail_reason_is_blank();
			break;
		case 1702324: /* WARN_RETMAIL_RELATED_FIELDS_WILL_BE_RESET */
			conditionObj = new CIFast_IFast_ifastcbo_warn_retmail_related_fields_will_be_reset();
			break;
		case 1702325: /* WARN_RIF_AMTTYPE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_rif_amttype();
			break;
		case 1702326: /* WARN_RIF_FED_RATE_LESS_THAN_DEFAULT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_rif_fed_rate_less_than_default();
			break;
		case 1702327: /* WARN_RIF_PROV_RATE_LESS_THAN_DEFAULT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_rif_prov_rate_less_than_default();
			break;
		case 1702328: /* WARN_RIF_SPOUSE_OLDER_THAN_SHAREHOLDER */
			conditionObj = new CIFast_IFast_ifastcbo_warn_rif_spouse_older_than_shareholder();
			break;
		case 1702329: /* WARN_RO_EFF_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_ro_eff_date();
			break;
		case 1702330: /* WARN_SAGES_ASSISTED_CONTRIBUTION_AMOUNT_IS_ZERO */
			conditionObj = new CIFast_IFast_ifastcbo_warn_sages_assisted_contribution_amount_is_zero();
			break;
		case 1702331: /* WARN_SALESREP_MIN_BALANCE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_salesrep_min_balance();
			break;
		case 1702332: /* WARN_SCHEDULED_PAYMENT_NOT_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_scheduled_payment_not_available();
			break;
		case 1702333: /* WARN_SEG_MANUAL_EVENTS_SINCE_ORIGINAL_TRADE_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_seg_manual_events_since_original_trade_date();
			break;
		case 1702334: /* WARN_SELAMOUNT_LESSTHAN_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_selamount_lessthan_required();
			break;
		case 1702335: /* WARN_SENDER_REF_NUM_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_sender_ref_num_required();
			break;
		case 1702336: /* WARN_SERVICE_AGENT_CHANGED_BY_COMPENSATION_AGENT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_service_agent_changed_by_compensation_agent();
			break;
		case 1702337: /* WARN_SERVICE_AGENT_MUST_BE_CHANGED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_service_agent_must_be_changed();
			break;
		case 1702338: /* WARN_SETTL_LOC_IS_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_warn_settl_loc_is_missing();
			break;
		case 1702339: /* WARN_SETTLE_ALL */
			conditionObj = new CIFast_IFast_ifastcbo_warn_settle_all();
			break;
		case 1702340: /* WARN_SETTLE_NETWORK_APPLIED_TO_CANCELLATION_AND_REBOOK */
			conditionObj = new CIFast_IFast_ifastcbo_warn_settle_network_applied_to_cancellation_and_rebook();
			break;
		case 1702341: /* WARN_SETTLE_TYPE_INDIVIDUAL_NOT_ALLOW_THROUGH_FUNDSERV */
			conditionObj = new CIFast_IFast_ifastcbo_warn_settle_type_individual_not_allow_through_fundserv();
			break;
		case 1702342: /* WARN_SETTLEMENT_NOT_ALL_TRADES_SETTLED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_settlement_not_all_trades_settled();
			break;
		case 1702343: /* WARN_SETTLEMENT_SOURCE_NOT_UPDATABLE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_settlement_source_not_updatable();
			break;
		case 1702344: /* WARN_SETTLING_GRANT_REPAYMENT_BY_UNIT_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_settling_grant_repayment_by_unit_not_allowed();
			break;
		case 1702345: /* WARN_SHAREHOLDER_HAS_MULTIPLE_ACTIVE_BANK_ACCOUNTS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_shareholder_has_multiple_active_bank_accounts();
			break;
		case 1702346: /* WARN_SHAREHOLDER_TAXJUR_RESPROV_UNASSIGNED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_shareholder_taxjur_resprov_unassigned();
			break;
		case 1702347: /* WARN_ShareholerFeeModelCodeIsNeeded */
			conditionObj = new CIFast_IFast_ifastcbo_warn_shareholerfeemodelcodeisneeded();
			break;
		case 1702348: /* WARN_SIBLING_ONLY_BLANK_OR_NO */
			conditionObj = new CIFast_IFast_ifastcbo_warn_sibling_only_blank_or_no();
			break;
		case 1702349: /* WARN_SIGNATURE_DATE_LATER */
			conditionObj = new CIFast_IFast_ifastcbo_warn_signature_date_later();
			break;
		case 1702350: /* WARN_SIGNATURE_DATE_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_signature_date_required();
			break;
		case 1702351: /* WARN_SIN_EFFECTIVE_DATE_CANNOT_BE_EARLIER_THAN_DOFB */
			conditionObj = new CIFast_IFast_ifastcbo_warn_sin_effective_date_cannot_be_earlier_than_dofb();
			break;
		case 1702352: /* WARN_SIN_EFFECTIVE_DATE_CANNOT_BE_FUTURE_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_sin_effective_date_cannot_be_future_date();
			break;
		case 1702353: /* WARN_SIN_EFFECTIVE_DATE_CANNOT_BE_UNKNOWN */
			conditionObj = new CIFast_IFast_ifastcbo_warn_sin_effective_date_cannot_be_unknown();
			break;
		case 1702354: /* WARN_SIN_EFFECTIVE_DATE_IS_MANDATORY */
			conditionObj = new CIFast_IFast_ifastcbo_warn_sin_effective_date_is_mandatory();
			break;
		case 1702355: /* WARN_SIN_NUMBER_SAME_ENTITY_1_ENTITY_2 */
			conditionObj = new CIFast_IFast_ifastcbo_warn_sin_number_same_entity_1_entity_2();
			break;
		case 1702356: /* WARN_SLSREP_FROM_TRANSFER_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_slsrep_from_transfer_not_allowed();
			break;
		case 1702357: /* WARN_SLSREP_MIN_ALLOWABLE_PURCHASE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_slsrep_min_allowable_purchase();
			break;
		case 1702358: /* WARN_SLSREP_MIN_INIT_PURCHASE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_slsrep_min_init_purchase();
			break;
		case 1702359: /* WARN_SLSREP_PURCHASE_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_slsrep_purchase_not_allowed();
			break;
		case 1702360: /* WARN_SLSREP_REDEMPTION_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_slsrep_redemption_not_allowed();
			break;
		case 1702361: /* WARN_SLSREP_TO_TRANSFER_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_slsrep_to_transfer_not_allowed();
			break;
		case 1702362: /* WARN_SOCIAL_CODE_NOT_APPLICABLE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_social_code_not_applicable();
			break;
		case 1702363: /* WARN_SRVCE_AGENT_BELONGS_TO_FUNDSERV_BROKER */
			conditionObj = new CIFast_IFast_ifastcbo_warn_srvce_agent_belongs_to_fundserv_broker();
			break;
		case 1702364: /* WARN_START_STOP_DATE_MUST_BE_WITHIN_REGPORTING_FFI */
			conditionObj = new CIFast_IFast_ifastcbo_warn_start_stop_date_must_be_within_regporting_ffi();
			break;
		case 1702365: /* WARN_STATUS_NEED_TO_FLIP_OR_NEW_REQUEST_REQUIRED_FOR_TAX_YEAR */
			conditionObj = new CIFast_IFast_ifastcbo_warn_status_need_to_flip_or_new_request_required_for_tax_year();
			break;
		case 1702366: /* WARN_STOP_DATE_MUST_BE_WITHIN_FFI_STOP_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_stop_date_must_be_within_ffi_stop_date();
			break;
		case 1702367: /* WARN_STOP_FLAG_SET_FOR_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_warn_stop_flag_set_for_fund();
			break;
		case 1702368: /* WARN_STOP_SETTLE_REDEMPTION */
			conditionObj = new CIFast_IFast_ifastcbo_warn_stop_settle_redemption();
			break;
		case 1702369: /* WARN_SUBSEQUENT_EVENTS_TAKEN_PLACE_AT_BACKDATING */
			conditionObj = new CIFast_IFast_ifastcbo_warn_subsequent_events_taken_place_at_backdating();
			break;
		case 1702370: /* WARN_SUM_OF_DISTRIBUTION_RATES_NOT_RECENT_DISTRIBUTION */
			conditionObj = new CIFast_IFast_ifastcbo_warn_sum_of_distribution_rates_not_recent_distribution();
			break;
		case 1702371: /* WARN_SUPPRESS_PAYTYPE_REQUIRED_FOR_FUND_SOURCE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_suppress_paytype_required_for_fund_source();
			break;
		case 1702372: /* WARN_SWITCH_EFT_PUR_TO_ALTERNATIVE_EFT_PUR */
			conditionObj = new CIFast_IFast_ifastcbo_warn_switch_eft_pur_to_alternative_eft_pur();
			break;
		case 1702373: /* WARN_SWITCH_EFT_TO_ALTERNATIVEEFT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_switch_eft_to_alternativeeft();
			break;
		case 1702374: /* WARN_SWP_NON_GMWB_FUNDS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_swp_non_gmwb_funds();
			break;
		case 1702375: /* WARN_SWP_PAYOPTION */
			conditionObj = new CIFast_IFast_ifastcbo_warn_swp_payoption();
			break;
		case 1702376: /* WARN_SYS_TRIG_AMEND_AND_RECAL_QESI_NOTIONAL_BALANCE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_sys_trig_amend_and_recal_qesi_notional_balance();
			break;
		case 1702377: /* WARN_SYSTEM_ADMIN_FEE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_system_admin_fee();
			break;
		case 1702378: /* WARN_TAINTED_ONLY_APPLICABLE_IF_PRE98CONTRIB_IS_YES */
			conditionObj = new CIFast_IFast_ifastcbo_warn_tainted_only_applicable_if_pre98contrib_is_yes();
			break;
		case 1702379: /* WARN_TAX_EXEMPT_AUTH_SHOULD_BE_UPDATED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_tax_exempt_auth_should_be_updated();
			break;
		case 1702380: /* WARN_TAX_ID_NUMBER_NOT_PROVIDED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_tax_id_number_not_provided();
			break;
		case 1702381: /* WARN_TAX_JURIS_CHANGED_EFFECTIVE_DATE_SAME */
			conditionObj = new CIFast_IFast_ifastcbo_warn_tax_juris_changed_effective_date_same();
			break;
		case 1702382: /* WARN_TAX_JURIS_CHANGED_ENSURE_RRIF_IS_FOLLOWED_NEW_TAX */
			conditionObj = new CIFast_IFast_ifastcbo_warn_tax_juris_changed_ensure_rrif_is_followed_new_tax();
			break;
		case 1702383: /* WARN_TAX_JURIS_INVALID */
			conditionObj = new CIFast_IFast_ifastcbo_warn_tax_juris_invalid();
			break;
		case 1702384: /* WARN_TAX_JURIS_NOT_FOUND_FOR_OWNER */
			conditionObj = new CIFast_IFast_ifastcbo_warn_tax_juris_not_found_for_owner();
			break;
		case 1702385: /* WARN_TFSA_ACCT_STATUS_CHANGED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_tfsa_acct_status_changed();
			break;
		case 1702386: /* WARN_TFSA_DECEASED_ANNUITANT_DOD_UPDATED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_tfsa_deceased_annuitant_dod_updated();
			break;
		case 1702387: /* WARN_TFSA_UPDATE_EFFECTIVE_DATE_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_tfsa_update_effective_date_required();
			break;
		case 1702388: /* WARN_THE_AMS_MODEL_ASSOCIATED_WITH_ANOTHER_ACCT_SAME_SHRHLDR */
			conditionObj = new CIFast_IFast_ifastcbo_warn_the_ams_model_associated_with_another_acct_same_shrhldr();
			break;
		case 1702389: /* WARN_TRADE_BACKDATED_SUBSEQUENT_OUT_EXISTS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_trade_backdated_subsequent_out_exists();
			break;
		case 1702390: /* WARN_TRADE_DATE_MUST_BE_EQUAL_OR_GREATER_THAN_SAGESDEFF */
			conditionObj = new CIFast_IFast_ifastcbo_warn_trade_date_must_be_equal_or_greater_than_sagesdeff();
			break;
		case 1702391: /* WARN_TRADE_DATE_PAST_CUTOFF_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_trade_date_past_cutoff_date();
			break;
		case 1702392: /* WARN_TRADE_EXIST_FOR_TAX_YEAR */
			conditionObj = new CIFast_IFast_ifastcbo_warn_trade_exist_for_tax_year();
			break;
		case 1702393: /* WARN_TRADE_EXITS_IN_ACCT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_trade_exits_in_acct();
			break;
		case 1702394: /* WARN_TRADE_GUAR_ADJ */
			conditionObj = new CIFast_IFast_ifastcbo_warn_trade_guar_adj();
			break;
		case 1702395: /* WARN_TRADE_GUAR_ADJ_EXISTS_AFTER_TRADE_DATE_ACCT_FROM */
			conditionObj = new CIFast_IFast_ifastcbo_warn_trade_guar_adj_exists_after_trade_date_acct_from();
			break;
		case 1702396: /* WARN_TRADE_GUAR_ADJ_EXISTS_AFTER_TRADE_DATE_ACCT_TO */
			conditionObj = new CIFast_IFast_ifastcbo_warn_trade_guar_adj_exists_after_trade_date_acct_to();
			break;
		case 1702397: /* WARN_TRADE_IS_A_GRANT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_trade_is_a_grant();
			break;
		case 1702398: /* WARN_TRADE_IS_PART_OF_DM_EVENT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_trade_is_part_of_dm_event();
			break;
		case 1702399: /* WARN_TRADE_NOT_ALLOWED_TO_CANCEL */
			conditionObj = new CIFast_IFast_ifastcbo_warn_trade_not_allowed_to_cancel();
			break;
		case 1702400: /* WARN_TRADE_PASSED_FUND_CUTOFF_TIME */
			conditionObj = new CIFast_IFast_ifastcbo_warn_trade_passed_fund_cutoff_time();
			break;
		case 1702401: /* WARN_TRADE_SETTLEMENT_INSTRUCTIONS_MISSING_ACCT_LEVEL_DEFAULT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_trade_settlement_instructions_missing_acct_level_default();
			break;
		case 1702402: /* WARN_TRADE_SETTLEMENT_IS_RESTRICTED_DUE_TO */
			conditionObj = new CIFast_IFast_ifastcbo_warn_trade_settlement_is_restricted_due_to();
			break;
		case 1702403: /* WARN_TRADE_UNIT_ADJ_REQ_FOR_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_trade_unit_adj_req_for_account();
			break;
		case 1702404: /* WARN_TRADE_UNIT_ADJ_REQ_FOR_ACCOUNT_FROM */
			conditionObj = new CIFast_IFast_ifastcbo_warn_trade_unit_adj_req_for_account_from();
			break;
		case 1702405: /* WARN_TRADE_UNIT_ADJ_REQ_FOR_ACCOUNT_TO */
			conditionObj = new CIFast_IFast_ifastcbo_warn_trade_unit_adj_req_for_account_to();
			break;
		case 1702406: /* WARN_TRADED_UNIT_POSITION */
			conditionObj = new CIFast_IFast_ifastcbo_warn_traded_unit_position();
			break;
		case 1702407: /* WARN_TRADING_TIME_PASSED_AGGREGATED_ORDER_CUTOFF_TIME */
			conditionObj = new CIFast_IFast_ifastcbo_warn_trading_time_passed_aggregated_order_cutoff_time();
			break;
		case 1702408: /* WARN_TRADING_TIME_PASSED_CLIENT_AND_AGGREGATED_ORDER_CUTTOF_TIME */
			conditionObj = new CIFast_IFast_ifastcbo_warn_trading_time_passed_client_and_aggregated_order_cuttof_time();
			break;
		case 1702409: /* WARN_TRANFER_TANSACTION_RESUBMITTED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_tranfer_tansaction_resubmitted();
			break;
		case 1702410: /* WARN_TRANS_NOT_ALLOWED_DURING_SETTLMENTPHASE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_trans_not_allowed_during_settlmentphase();
			break;
		case 1702411: /* WARN_TRANSFER_CONTRARY_CLIENT_GUAGUARD_PROTECTION */
			conditionObj = new CIFast_IFast_ifastcbo_warn_transfer_contrary_client_guaguard_protection();
			break;
		case 1702412: /* WARN_TRANSFER_DIFFERENT_TO_FROM_FUND_CLASS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_transfer_different_to_from_fund_class();
			break;
		case 1702413: /* WARN_TRANSFER_NOT_ALLOWED_CONTRACT_TYPE_AND_OR_VERSION_NOT_THE_SAME */
			conditionObj = new CIFast_IFast_ifastcbo_warn_transfer_not_allowed_contract_type_and_or_version_not_the_same();
			break;
		case 1702414: /* WARN_TRANSFER_OUT_NOT_ALLOWED_FOR_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_warn_transfer_out_not_allowed_for_fund();
			break;
		case 1702415: /* WARN_TRANSFERIN_NOT_ALLOWED_FOR_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_warn_transferin_not_allowed_for_fund();
			break;
		case 1702416: /* WARN_TRFX_AGE_DIFF_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_trfx_age_diff_not_allowed();
			break;
		case 1702417: /* WARN_TRUST_ACCOUNT_NUMBER_FORMAT_IS_INVALID */
			conditionObj = new CIFast_IFast_ifastcbo_warn_trust_account_number_format_is_invalid();
			break;
		case 1702418: /* WARN_TRX_TIERED_AND_NON_TIERED_ACCOUNT_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_trx_tiered_and_non_tiered_account_not_allowed();
			break;
		case 1702419: /* WARN_TUP_CALCULATION_ERROR */
			conditionObj = new CIFast_IFast_ifastcbo_warn_tup_calculation_error();
			break;
		case 1702420: /* WARN_TUP_ESTIMATED_UNITS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_tup_estimated_units();
			break;
		case 1702421: /* WARN_TUP_FULLMONEYOUT_PENDING_TRADE_EXISTS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_tup_fullmoneyout_pending_trade_exists();
			break;
		case 1702422: /* WARN_TUP_SHARES */
			conditionObj = new CIFast_IFast_ifastcbo_warn_tup_shares();
			break;
		case 1702423: /* WARN_TUP_TOLERANCE_PERCENT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_tup_tolerance_percent();
			break;
		case 1702424: /* WARN_TUP_TOLERANCE_UNITS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_tup_tolerance_units();
			break;
		case 1702425: /* WARN_UC_AMT_LESS_THAN_RES_AMT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_uc_amt_less_than_res_amt();
			break;
		case 1702426: /* WARN_UNABLE_TO_ADD_ESTATE_OF_DECEASED_TO_NON_ESTATE_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_unable_to_add_estate_of_deceased_to_non_estate_account();
			break;
		case 1702427: /* WARN_UNCLAIM_RETMAIL_FIELD_CHANGED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_unclaim_retmail_field_changed();
			break;
		case 1702428: /* WARN_UNITS_CANNOT_BE_REDEEMED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_units_cannot_be_redeemed();
			break;
		case 1702429: /* WARN_UNSETTLED_TRADES_WITH_AMS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_unsettled_trades_with_ams();
			break;
		case 1702430: /* WARN_UNVERIFIED_BANK */
			conditionObj = new CIFast_IFast_ifastcbo_warn_unverified_bank();
			break;
		case 1702431: /* WARN_UNVERIFIED_BANK_INSTR */
			conditionObj = new CIFast_IFast_ifastcbo_warn_unverified_bank_instr();
			break;
		case 1702432: /* WARN_UPDATE_NOTIONAL_DATA */
			conditionObj = new CIFast_IFast_ifastcbo_warn_update_notional_data();
			break;
		case 1702433: /* WARN_USER_DEF_MAT_LESS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_user_def_mat_less();
			break;
		case 1702434: /* WARN_USER_DEFINED_MATURITY_DATE_CANNOT_BE_BLANK */
			conditionObj = new CIFast_IFast_ifastcbo_warn_user_defined_maturity_date_cannot_be_blank();
			break;
		case 1702435: /* WARN_USER_DEFINED_MATURITY_DATE_LESS_THAN_MATURITY_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_user_defined_maturity_date_less_than_maturity_date();
			break;
		case 1702436: /* WARN_USER_DEFINED_MATURITY_DATE_LESS_THAN_MIN_TERM */
			conditionObj = new CIFast_IFast_ifastcbo_warn_user_defined_maturity_date_less_than_min_term();
			break;
		case 1702437: /* WARN_USER_DEFINED_MATURITY_DATE_SHOULD_BE_BETWEEN_MIN_MAX_AGE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_user_defined_maturity_date_should_be_between_min_max_age();
			break;
		case 1702438: /* WARN_USER_DEFINED_MATURITY_DATE_SHOULD_BE_GREATER_THAN_MIN_TERM */
			conditionObj = new CIFast_IFast_ifastcbo_warn_user_defined_maturity_date_should_be_greater_than_min_term();
			break;
		case 1702439: /* WARN_VALUE_BETWEEN_TWO_REOCRDS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_value_between_two_reocrds();
			break;
		case 1702440: /* WARN_VALUE_ZERO */
			conditionObj = new CIFast_IFast_ifastcbo_warn_value_zero();
			break;
		case 1702441: /* WARN_VARIABLE_DSC_FEE_AMOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_variable_dsc_fee_amount();
			break;
		case 1702442: /* WARN_WAIVE_PAPER_CANNOT_BE_YES */
			conditionObj = new CIFast_IFast_ifastcbo_warn_waive_paper_cannot_be_yes();
			break;
		case 1702443: /* WARN_WIRE_ORDER_NUMBER_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_wire_order_number_required();
			break;
		case 1702444: /* WARN_YTD_CONTRIBUTION_WILL_BE_NEGATIVE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_ytd_contribution_will_be_negative();
			break;
		case 1702445: /* WARNING_DOCUMENT_TYPE_IS_ONHOLD */
			conditionObj = new CIFast_IFast_ifastcbo_warning_document_type_is_onhold();
			break;
		case 1702446: /* ERR_FEE_MODEL_CANNOT_BE_STOPPED_BEFORE_LAST_PROCESS_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_fee_model_cannot_be_stopped_before_last_process_date();
			break;
		case 1702447: /* WARN_FEE_MODEL_CANNOT_BE_STOPPED_BEFORE_LAST_PROCESS_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_fee_model_cannot_be_stopped_before_last_process_date();
			break;
		case 1702448: /* ERR_THE_MAXIMUM_FEE_RATE_IS_GREATER_THAN */
			conditionObj = new CIFast_IFast_ifastcbo_err_the_maximum_fee_rate_is_greater_than();
			break;
		case 1702449: /* WARN_THE_MAXIMUM_FEE_RATE_IS_GREATER_THAN */
			conditionObj = new CIFast_IFast_ifastcbo_warn_the_maximum_fee_rate_is_greater_than();
			break;
		case 1702450: /* WARN_SAGES_AMOUNT_TO_BE_RETURNED_BECAUSE_REDEMPTION */
			conditionObj = new CIFast_IFast_ifastcbo_warn_sages_amount_to_be_returned_because_redemption();
			break;
		case 1702451: /* ERR_SAGES_AMOUNT_TO_BE_RETURNED_BECAUSE_REDEMPTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_sages_amount_to_be_returned_because_redemption();
			break;
		case 1702452: /* WARN_REVIEW_SAGES_APPLICATION_DUE_TO_TAX_JURISDICTION_CHANGES */
			conditionObj = new CIFast_IFast_ifastcbo_warn_review_sages_application_due_to_tax_jurisdiction_changes();
			break;
		case 1702453: /* ERR_ACCOUNT_MUST_BE_SIBLING_ONLY_FOR_SAGES */
			conditionObj = new CIFast_IFast_ifastcbo_err_account_must_be_sibling_only_for_sages();
			break;
		case 1702454: /* WARN_ACCOUNT_MUST_BE_SIBLING_ONLY_FOR_SAGES */
			conditionObj = new CIFast_IFast_ifastcbo_warn_account_must_be_sibling_only_for_sages();
			break;
		case 1702455: /* ERR_TERMINATION_NOT_ALLOWED_SAGES_BALANCE_GREATER_THAN_ZERO */
			conditionObj = new CIFast_IFast_ifastcbo_err_termination_not_allowed_sages_balance_greater_than_zero();
			break;
		case 1702456: /* WARN_TERMINATION_NOT_ALLOWED_SAGES_BALANCE_GREATER_THAN_ZERO */
			conditionObj = new CIFast_IFast_ifastcbo_warn_termination_not_allowed_sages_balance_greater_than_zero();
			break;
		case 1702457: /* ERR_ALLOCATION_OPTION_NOT_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastcbo_err_allocation_option_not_available();
			break;
		case 1702458: /* WARN_ALLOCATION_OPTION_NOT_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_allocation_option_not_available();
			break;
		case 1702459: /* INFO_CESG_UC_REASON */
			conditionObj = new CIFast_IFast_ifastcbo_info_cesg_uc_reason();
			break;
		case 1702460: /* INFO_CESG_REJ_REASON */
			conditionObj = new CIFast_IFast_ifastcbo_info_cesg_rej_reason();
			break;
		case 1702461: /* INFO_SAGES_UC_REASON */
			conditionObj = new CIFast_IFast_ifastcbo_info_sages_uc_reason();
			break;
		case 1702462: /* INFO_SAGES_REJ_REASON */
			conditionObj = new CIFast_IFast_ifastcbo_info_sages_rej_reason();
			break;
		case 1702463: /* INFO_SAGES_REPORTED */
			conditionObj = new CIFast_IFast_ifastcbo_info_sages_reported();
			break;
		case 1702464: /* INFO_SAGES_TRANSORIGCODE */
			conditionObj = new CIFast_IFast_ifastcbo_info_sages_transorigcode();
			break;
		case 1702465: /* ERR_SETTLE_TYPE_BLOCK_NOT_ALLOW_NOT_THROUGH_FUNDSERV */
			conditionObj = new CIFast_IFast_ifastcbo_err_settle_type_block_not_allow_not_through_fundserv();
			break;
		case 1702466: /* WARN_SETTLE_TYPE_BLOCK_NOT_ALLOW_NOT_THROUGH_FUNDSERV */
			conditionObj = new CIFast_IFast_ifastcbo_warn_settle_type_block_not_allow_not_through_fundserv();
			break;
		case 1702467: /* WARN_TRADE_DOES_NOT_BELONG_TO_EXISTING_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_warn_trade_does_not_belong_to_existing_fund();
			break;
		case 1702468: /* WARN_ANNUITANT_AGE_BELOW_MINIMUM_REQUIREMENT_PER_CONTRACT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_annuitant_age_below_minimum_requirement_per_contract();
			break;
		case 1702469: /*  */
			conditionObj = new CIFast_IFast_ifastcbo_err_branch_different_than_account_branch();
			break;
		case 1702470: /*  */
			conditionObj = new CIFast_IFast_ifastcbo_warn_branch_different_than_account_branch();
			break;
		case 1702471: /*  */
			conditionObj = new CIFast_IFast_ifastcbo_err_slsrep_different_than_account_slsrep();
			break;
		case 1702472: /*  */
			conditionObj = new CIFast_IFast_ifastcbo_warn_slsrep_different_than_account_slsrep();
			break;
		case 1702473: /*  */
			conditionObj = new CIFast_IFast_ifastcbo_err_fundserv_settle_dilution_of_rebook_must_be_the_same_as_cancellation_trade();
			break;
		case 1702474: /* ERR_INVALID_AMOUNT_TYPE_BY_SEG_RULES */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_amount_type_by_seg_rules();
			break;
		case 1702475: /* WARN_INVALID_AMOUNT_TYPE_BY_SEG_RULES */
			conditionObj = new CIFast_IFast_ifastcbo_warn_invalid_amount_type_by_seg_rules();
			break;
		case 1702476: /* ERR_INVALID_OR_MISSING_ANNUITANT_SEX */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_or_missing_annuitant_sex();
			break;
		case 1702477: /* WARN_INVALID_OR_MISSING_ANNUITANT_SEX */
			conditionObj = new CIFast_IFast_ifastcbo_warn_invalid_or_missing_annuitant_sex();
			break;
		case 1702478: /* ERR_RELATED_PARTY_NOT_ALLOWED_FOR_CORPORATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_related_party_not_allowed_for_corporate();
			break;
		case 1702479: /* WARN_RELATED_PARTY_NOT_ALLOWED_FOR_CORPORATE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_related_party_not_allowed_for_corporate();
			break;
		case 1702480: /* ERR_TAX_PAYER_STATUS_REASON_IS_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_tax_payer_status_reason_is_missing();
			break;
		case 1702481: /* WARN_TAX_PAYER_STATUS_REASON_IS_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_warn_tax_payer_status_reason_is_missing();
			break;
		case 1702482: /* ERR_ERR_FUND_IN_FOREIGN_CURRENCY */
			conditionObj = new CIFast_IFast_ifastcbo_err_err_fund_in_foreign_currency();
			break;
		case 1702483: /* WARN_FUND_CLASS_NOT_APPLICABLE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_fund_class_not_applicable();
			break;	
		case 1702484: /* ERR_SERVICE_ONLY_SALES_REP */
			conditionObj = new CIFast_IFast_ifastcbo_err_slsrep_service_only();
			break;
		case 1702485: /* WARN_SERVICE_ONLY_SALES_REP */
			conditionObj = new CIFast_IFast_ifastcbo_warn_slsrep_service_only();
			break;
        case 1702486: /* ERR_RELATED_PARTY_CAN_BE_ONLY_INDIVIDUAL */
            conditionObj = new CIFast_IFast_ifastcbo_err_related_party_can_be_only_individual();
            break;
        case 1702487: /* WARN_RELATED_PARTY_CAN_BE_ONLY_INDIVIDUAL */
            conditionObj = new CIFast_IFast_ifastcbo_warn_related_party_can_be_only_individual();
            break;
        case 1702488: /* ERR_ANNUITANTS_FOR_FROM_TO_MUST_BE_THE_SAME */
            conditionObj = new CIFast_IFast_ifastcbo_err_annuitants_for_from_to_must_be_the_same();
            break;
        case 1702489: /* WARN_ANNUITANTS_FOR_FROM_TO_MUST_BE_THE_SAME */
            conditionObj = new CIFast_IFast_ifastcbo_warn_annuitants_for_from_to_must_be_the_same();
            break;
        case 1702490: /* ERR_ANNUITANT_FOR_TO_ACCT_MUST_BE_AT_LEAST_50_YEARS */
            conditionObj = new CIFast_IFast_ifastcbo_err_annuitant_for_to_acct_must_be_at_least_50_years();
            break;
        case 1702491: /* WARN_ANNUITANT_FOR_TO_ACCT_MUST_BE_AT_LEAST_50_YEARS */
            conditionObj = new CIFast_IFast_ifastcbo_warn_annuitant_for_to_acct_must_be_at_least_50_years();
            break;
        case 1702492: /* ERR_TRANSMITTER_NUMBER_FORMAT_INCORRECT */
            conditionObj = new CIFast_IFast_ifastcbo_err_transmitter_number_format_incorrect();
            break;
        case 1702493: /* WARN_TRANSMITTER_NUMBER_FORMAT_INCORRECT */
            conditionObj = new CIFast_IFast_ifastcbo_warn_transmitter_number_format_incorrect();
            break;
		case 1702494: /* WARN_STOPDATE_NOT_VALID */
			conditionObj = new CIFast_IFast_ifastcbo_warn_stopdate_not_valid();
			break;
        case 1702495: /* ERR_TR_OUT_MUSTBE_CANCELLED_PRIOR_TO_THIS_OPERATION */
            conditionObj = new CIFast_IFast_ifastcbo_err_tr_out_must_be_cancelled();
            break;
        case 1702496: /* WARN_TR_OUT_MUSTBE_CANCELLED_PRIOR_TO_THIS_OPERATION */
            conditionObj = new CIFast_IFast_ifastcbo_warn_tr_out_must_be_cancelled();
            break;
		case 1702497: /* WARN_ADDITIONAL_ACCTNUM_MUST_BE_SETUP_IN_IDENTIFICATION */
			conditionObj = new CIFast_IFast_ifastcbo_warn_additional_acctnum_must_be_setup_in_identification();
			break;
		case 1702498: /* ERR_FEECODE_NOT_VALID_FOR_NON_PF_FUNDS */
			conditionObj = new CIFast_IFast_ifastcbo_err_feecode_not_valid_for_non_pf_funds();
			break;
		case 1702499: /* ERR_RESP_TRANSACTION_DATE_MUST_BE_GREATER_THAN_PROGRAM_START_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_resp_transaction_date_must_be_greater_than_program_start_date();
			break;
		case 1702500: /* WARN_RESP_TRANSACTION_DATE_MUST_BE_GREATER_THAN_PROGRAM_START_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_resp_transaction_date_must_be_greater_than_program_start_date();
			break;
		case 1702501: /* ERR_RESP_RESIDUAL_GRANT_TRANSFER_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_resp_residual_grant_transfer_not_allowed();
			break;
		case 1702502: /* WARN_RESP_RESIDUAL_GRANT_TRANSFER_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_resp_residual_grant_transfer_not_allowed();
			break;
		case 1702503: /* ERR_CANCELLATION_NOT_ALLOWED_NOTIONAL_BALANCE_GOING_NEGATIVE */
			conditionObj = new CIFast_IFast_ifastcbo_err_cancellation_not_allowed_notional_balance_going_negative();
			break;
		case 1702504: /* WARN_CANCELLATION_NOT_ALLOWED_NOTIONAL_BALANCE_GOING_NEGATIVE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_cancellation_not_allowed_notional_balance_going_negative();
			break;
		case 1702505: /* ERR_ACCOUNT_MUST_BE_SIBLING_ONLY_FOR_BCTESG */
			conditionObj = new CIFast_IFast_ifastcbo_err_account_must_be_sibling_only_for_bctesg();
			break;
		case 1702506: /* WARN_ACCOUNT_MUST_BE_SIBLING_ONLY_FOR_BCTESG */
			conditionObj = new CIFast_IFast_ifastcbo_warn_account_must_be_sibling_only_for_bctesg();
			break;
		case 1702507: /* ERR_AMOUNT_EXCEEDS_BCTESG_BALANCE */
			conditionObj = new CIFast_IFast_ifastcbo_err_amount_exceeds_bctesg_balance();
			break;
		case 1702508: /* WARN_AMOUNT_EXCEEDS_BCTESG_BALANCE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_amount_exceeds_bctesg_balance();
			break;
		case 1702509: /* ERR_TRANSFER_IN_WITH_BCTESG_CANNOT_BE_PROCESSED_BEFORE_DEFF */
			conditionObj = new CIFast_IFast_ifastcbo_err_tranfer_in_with_bctesg_cannot_be_processed_before_deff();
			break;
		case 1702510: /* WARN_TRANSFER_IN_WITH_BCTESG_CANNOT_BE_PROCESSED_BEFORE_DEFF */
			conditionObj = new CIFast_IFast_ifastcbo_warn_tranfer_in_with_bctesg_cannot_be_processed_before_deff();
			break;
		case 1702511: /* ERR_COUNTRY_OF_EXPOSURE_IS_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_country_of_exposure_is_required();
			break;
		case 1702512: /* WARN_COUNTRY_OF_EXPOSURE_IS_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_country_of_exposure_is_required();
			break;
		case 1702513: /* ERR_TRANSACTION_AWAITING_HRSDC_RESPONSE_CANNOT_CHANGE_ALLOCATIONS */
			conditionObj = new CIFast_IFast_ifastcbo_err_transaction_awaiting_hrsdc_response_cannot_change_allocations();
			break;
		case 1702514: /* WARN_TRANSACTION_AWAITING_HRSDC_RESPONSE_CANNOT_CHANGE_ALLOCATIONS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_transaction_awaiting_hrsdc_response_cannot_change_allocations();
			break;
		case 1702515: /* ERR_BENEFICIARY_NOT_BC_RESIDENT */
			conditionObj = new CIFast_IFast_ifastcbo_err_beneficiary_not_bc_resident();
			break;
		case 1702516: /* WARN_BENEFICIARY_NOT_BC_RESIDENT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_beneficiary_not_bc_resident();
			break;
        case 1702517: /* ERR_RECEIVING_ACCT_AMS_MODEL_NOT_CONTAIN_THIS_FUND_CLASS_AS_CHILD */
            conditionObj = new CIFast_IFast_ifastcbo_err_receiving_acct_ams_model_not_contain_this_fund_class_as_child();
            break;
        case 1702518: /* WARN_RECEIVING_ACCT_AMS_MODEL_NOT_CONTAIN_THIS_FUND_CLASS_AS_CHILD */
            conditionObj = new CIFast_IFast_ifastcbo_warn_receiving_acct_ams_model_not_contain_this_fund_class_as_child();
            break;
        case 1702519: /* ERR_PENDING_TRADE_EXIST_ON_PARENT_FUND_CLASS */
            conditionObj = new CIFast_IFast_ifastcbo_err_pending_trade_exist_on_parent_fund_class();
            break;
        case 1702520: /* WARN_PENDING_TRADE_EXIST_ON_PARENT_FUND_CLASS */
            conditionObj = new CIFast_IFast_ifastcbo_warn_pending_trade_exist_on_parent_fund_class();
            break;
        case 1702521: /* ERR_PENDING_TRADE_EXIST_ON_ONE_OF_CHILD_FUND_CLASS */
            conditionObj = new CIFast_IFast_ifastcbo_err_pending_trade_exist_on_one_of_child_fund_class();
            break;
        case 1702522: /* WARN_PENDING_TRADE_EXIST_ON_ONE_OF_CHILD_FUND_CLASS */
            conditionObj = new CIFast_IFast_ifastcbo_warn_pending_trade_exist_on_one_of_child_fund_class();
            break;
        case 1702523: /* ERR_RECEIVING_ACCT_AND_RELINQUISHING_ACCT_LINKED_TO_DIFF_AMS_MODEL */
            conditionObj = new CIFast_IFast_ifastcbo_err_receiving_acct_and_relinquishing_acct_linked_to_diff_ams_model();
            break;
        case 1702524: /* WARN_RECEIVING_ACCT_AND_RELINQUISHING_ACCT_LINKED_TO_DIFF_AMS_MODEL */
            conditionObj = new CIFast_IFast_ifastcbo_warn_receiving_acct_and_relinquishing_acct_linked_to_diff_ams_model();
            break;
        case 1702525: /* ERR_UNSETTLED_TRADE_EXISTS_ON_ONE_OF_CHILD_FUND_CLASSES */
            conditionObj = new CIFast_IFast_ifastcbo_err_unsettled_trade_exists_on_one_of_child_fund_classes();
            break;
        case 1702526: /* WARN_UNSETTLED_TRADE_EXISTS_ON_ONE_OF_CHILD_FUND_CLASSES */
            conditionObj = new CIFast_IFast_ifastcbo_warn_unsettled_trade_exists_on_one_of_child_fund_classes();
            break;
        case 1702527: /* ERR_PENDING_PARENT_TO_PARENT_FULL_EXCHG_EXISTS */
            conditionObj = new CIFast_IFast_ifastcbo_err_pending_parent_to_parent_full_exchg_exists();
            break;
        case 1702528: /* WARN_PENDING_PARENT_TO_PARENT_FULL_EXCHG_EXISTS */
            conditionObj = new CIFast_IFast_ifastcbo_warn_pending_parent_to_parent_full_exchg_exists();
            break;
        case 1702529: /* ERR_RECEIVING_ACCT_LINKED_TO_DIFF_AMS_MODEL */
            conditionObj = new CIFast_IFast_ifastcbo_err_receiving_acct_linked_to_diff_ams_model();
            break;
        case 1702530: /* WARN_RECEIVING_ACCT_LINKED_TO_DIFF_AMS_MODEL */
            conditionObj = new CIFast_IFast_ifastcbo_warn_receiving_acct_linked_to_diff_ams_model();
            break;
        case 1702531: /* ERR_CURRENT_AMS_MODEL_NOT_CONTAIN_THIS_CHILD_FUND_CLASS */
            conditionObj = new CIFast_IFast_ifastcbo_err_current_ams_model_not_contain_this_child_fund_class();
            break;
        case 1702532: /* WARN_CURRENT_AMS_MODEL_NOT_CONTAIN_THIS_CHILD_FUND_CLASS */
            conditionObj = new CIFast_IFast_ifastcbo_warn_current_ams_model_not_contain_this_child_fund_class();
            break;
        case 1702533: /* ERR_PARENT_FUND_CLASS_DIFF_FROM_AMS_MODEL */
            conditionObj = new CIFast_IFast_ifastcbo_err_parent_fund_class_diff_from_ams_model();
            break;
        case 1702534: /* WARN_PARENT_FUND_CLASS_DIFF_FROM_AMS_MODEL */
            conditionObj = new CIFast_IFast_ifastcbo_warn_parent_fund_class_diff_from_ams_model();
            break;
        case 1702535: /* ERR_TRADING_ON_GLOBAL_AMS_PARENT_FND_CLS_NOT_ALLOWED_ACCT_NOT_LINKED_TO_ANY_AMS */
            conditionObj = new CIFast_IFast_ifastcbo_err_trading_on_global_ams_parent_fnd_cls_not_allowed_acct_not_linked_to_any_ams();
            break;
        case 1702536: /* WARN_TRADING_ON_GLOBAL_AMS_PARENT_FND_CLS_NOT_ALLOWED_ACCT_NOT_LINKED_TO_ANY_AMS */
            conditionObj = new CIFast_IFast_ifastcbo_warn_trading_on_global_ams_parent_fnd_cls_not_allowed_acct_not_linked_to_any_ams();
            break;
        case 1702537: /* ERR_ACCOUNT_AMS_MODEL_CANNOT_HOLD_GLOBAL_MODEL_FUNDS */
            conditionObj = new CIFast_IFast_ifastcbo_err_account_ams_model_cannot_hold_global_model_funds();
            break;
        case 1702538: /* WARN_ACCOUNT_AMS_MODEL_CANNOT_HOLD_GLOBAL_MODEL_FUNDS */
            conditionObj = new CIFast_IFast_ifastcbo_warn_account_ams_model_cannot_hold_global_model_funds();
            break;
        case 1702539: /* ERR_ONLY_CHILD_FUND_CAN_BE_ADDED_TO_ALLOCATION */
            conditionObj = new CIFast_IFast_ifastcbo_err_only_child_fund_can_be_added_to_allocation();
            break;
        case 1702540: /* WARN_ONLY_CHILD_FUND_CAN_BE_ADDED_TO_ALLOCATION */
            conditionObj = new CIFast_IFast_ifastcbo_warn_only_child_fund_can_be_added_to_allocation();
            break;
        case 1702541: /* ERR_STOPPING_AMS_MODEL_REQUIRE_FULL_MONEY_OUT_TRADE */
            conditionObj = new CIFast_IFast_ifastcbo_err_stopping_ams_model_require_full_money_out_trade();
            break;
        case 1702542: /* WARN_STOPPING_AMS_MODEL_REQUIRE_FULL_MONEY_OUT_TRADE */
            conditionObj = new CIFast_IFast_ifastcbo_warn_stopping_ams_model_require_full_money_out_trade();
            break;
        case 1702543: /* ERR_PARENT_FUND_IS_NOT_ALLOWED */
            conditionObj = new CIFast_IFast_ifastcbo_err_parent_fund_is_not_allowed();
            break;
        case 1702544: /* WARN_PARENT_FUND_IS_NOT_ALLOWED */
            conditionObj = new CIFast_IFast_ifastcbo_warn_parent_fund_is_not_allowed();
            break;
        case 1702545: /* ERR_UNIT_TRADING_NOT_ALLOWED */
            conditionObj = new CIFast_IFast_ifastcbo_err_unit_trading_not_allowed();
            break;
        case 1702546: /* WARN_UNIT_TRADING_NOT_ALLOWED */
            conditionObj = new CIFast_IFast_ifastcbo_warn_unit_trading_not_allowed();
            break;
        case 1702547: /* ERR_SOFT_CAPPED_FUND_LEVEL */
            conditionObj = new CIFast_IFast_ifastcbo_err_soft_capped_fund_level();
            break;
        case 1702548: /* WARN_SOFT_CAPPED_FUND_LEVEL */
            conditionObj = new CIFast_IFast_ifastcbo_warn_soft_capped_fund_level();
            break;
        case 1702549: /* ERR_SOFT_CAPPED_FUND_GROUP_LEVEL */
            conditionObj = new CIFast_IFast_ifastcbo_err_soft_capped_fund_group_level();
            break;
        case 1702550: /* WARN_SOFT_CAPPED_FUND_GROUP_LEVEL */
            conditionObj = new CIFast_IFast_ifastcbo_warn_soft_capped_fund_group_level();
            break;
        case 1702553: /* ERR_PSE_INFORMATION_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_pse_information_required();							 
			break;
        case 1702554: /* WARN_PSE_INFORMATION_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_pse_information_required();
			break;
		case 1702555: /* ERR_NOTIONAL_AMOUNTS_MUST_BE_NEGATIVE */
			conditionObj = new CIFast_IFast_ifastcbo_err_notional_amounts_must_be_negative();							 
			break;
		case 1702556: /* WARN_NOTIONAL_AMOUNTS_MUST_BE_NEGATIVE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_notional_amounts_must_be_negative();
			break;
		case 1702557: /* ERR_DIF_DOES_NOT_ALLOW_CASH_SWEEP */
			conditionObj = new CIFast_IFast_ifastcbo_err_dif_does_not_allow_cash_sweep();
			break;
        case 1702558: /* ERR_BROKER_IS_NOT_ELIGIBLE_FOR_FUND_CLASS */
            conditionObj = new CIFast_IFast_ifastcbo_err_broker_is_not_eligible_for_fund_class();
            break;
        case 1702559: /* WARN_BROKER_IS_NOT_ELIGIBLE_FOR_FUND_CLASS */
            conditionObj = new CIFast_IFast_ifastcbo_warn_broker_is_not_eligible_for_fund_class();
            break;
        case 1702560: /* ERR_SALE_REP_IS_NOT_ELIGIBLE_FOR_FUND_CLASS */
            conditionObj = new CIFast_IFast_ifastcbo_err_sale_rep_is_not_eligible_for_fund_class();
            break;
        case 1702561: /* WARN_SALE_REP_IS_NOT_ELIGIBLE_FOR_FUND_CLASS */
            conditionObj = new CIFast_IFast_ifastcbo_warn_sale_rep_is_not_eligible_for_fund_class();
            break;
        case 1702562: /* ERR_INVALID_INSTITUTION_CODE */
            conditionObj = new CIFast_IFast_ifastcbo_err_Invalid_institution_code();
            break;
        case 1702563: /* WARN_INVALID_INSTITUTION_CODE */
            conditionObj = new CIFast_IFast_ifastcbo_warn_Invalid_institution_code();
            break;
        case 1702564: /* ERR_EXTINSTITUTION_NAME_NOT_PROVIDED */
            conditionObj = new CIFast_IFast_ifastcbo_err_ExtInstitution_name_not_provided();
            break;
        case 1702565: /* WARN_EXTINSTITUTION_NAME_NOT_PROVIDED */
            conditionObj = new CIFast_IFast_ifastcbo_warn_ExtInstitution_name_not_provided();
            break; 
        case 1702566: /* ERR_TRADING_ON_CHILD_FND_CLS_NOT_ALLOWED_ACCT_NOT_LINKED_TO_ANY_AMS */
            conditionObj = new CIFast_IFast_ifastcbo_err_trading_on_child_fnd_cls_not_allowed();
            break;
        case 1702567: /* ERR_TRADING_ON_CHILD_FND_CLS_NOT_ALLOWED_ACCT_NOT_LINKED_TO_ANY_AMS */
            conditionObj = new CIFast_IFast_ifastcbo_warn_trading_on_child_fnd_cls_not_allowed();
            break;
		case 1702568: /* IFASTCBO_ERR_VERSION_MISMATCH */
			conditionObj = new CIFast_IFast_ifastcbo_err_version_mismatch();
			break;
		case 1702569: /* IFASTCBO_WARN_VERSION_MISMATCH */
			conditionObj = new CIFast_IFast_ifastcbo_warn_version_mismatch();
			break;
		case 1702570: /* ERR_LTD_CONTRIB_MUST_EQUAL_SUM_OF_PRE98_CESGAC_CESGUC */
			conditionObj = new CIFast_IFast_ifastcbo_err_ltd_contrib_must_equal_sum_of_pre98_cesgac_cesguc();
			break;
		case 1702571: /* WARN_LTD_CONTRIB_MUST_EQUAL_SUM_OF_PRE98_CESGAC_CESGUC */
			conditionObj = new CIFast_IFast_ifastcbo_warn_ltd_contrib_must_equal_sum_of_pre98_cesgac_cesguc();
			break;
		case 1702572: /* ERR_QESIPREFEB2007_NOT_EQUAL_LTD_MINUS_QESIAC_QESIUC_QESIYTD */
			conditionObj = new CIFast_IFast_ifastcbo_err_qesiprefeb2007_not_equal_ltd_minus_qesiac_qesiuc_qesiytd();
			break;
		case 1702573: /* WARN_QESIPREFEB2007_NOT_EQUAL_LTD_MINUS_QESIAC_QESIUC_QESIYTD */
			conditionObj = new CIFast_IFast_ifastcbo_warn_qesiprefeb2007_not_equal_ltd_minus_qesiac_qesiuc_qesiytd();
			break;
		case 1702580: /* ERR_INVALID_LFC_NUMBER */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_lfc_number();
			break;
		case 1702581: /* WARN_INVALID_LFC_NUMBER */
			conditionObj = new CIFast_IFast_ifastcbo_warn_invalid_lfc_number();
			break;
        case 1702582: /* ERR_ONLY_DOLLAR_AMOUNT_IS_ALLOWED_FOR_CUSTOM_PAYOUT */
            conditionObj = new CIFast_IFast_ifastcbo_err_only_dollar_amount_is_allowed_for_custom_payout();
            break;
        case 1702583: /* WARN_ONLY_DOLLAR_AMOUNT_IS_ALLOWED_FOR_CUSTOM_PAYOUT */
            conditionObj = new CIFast_IFast_ifastcbo_warn_only_dollar_amount_is_allowed_for_custom_payout();
            break;
        case 1702584: /* ERR_NET_AMOUNT_IS_NOT_ALLOWED_FOR_CUSTOM_PAYOUT_SWP */
            conditionObj = new CIFast_IFast_ifastcbo_err_net_amount_is_not_allowed_for_custom_payout_swp();
            break;
        case 1702585: /* WARN_NET_AMOUNT_IS_NOT_ALLOWED_FOR_CUSTOM_PAYOUT_SWP */
            conditionObj = new CIFast_IFast_ifastcbo_warn_net_amount_is_not_allowed_for_custom_payout_swp();
            break;
        case 1702586: /* ERR_ONLY_CUSTOM_PAYOUT_FUNDS_ARE_ALLOWED_FOR_THE_PLAN */
            conditionObj = new CIFast_IFast_ifastcbo_err_only_custom_payout_funds_are_allowed_for_the_plan();
            break;
        case 1702587: /* WARN_ONLY_CUSTOM_PAYOUT_FUNDS_ARE_ALLOWED_FOR_THE_PLAN */
            conditionObj = new CIFast_IFast_ifastcbo_warn_only_custom_payout_funds_are_allowed_for_the_plan();
            break;
        case 1702588: /* ERR_PLAN_CANNOT_BE_MANUALLY_CREATED */
            conditionObj = new CIFast_IFast_ifastcbo_err_plan_cannot_be_manually_created();
            break;
        case 1702589: /* WARN_PLAN_CANNOT_BE_MANUALLY_CREATED */
            conditionObj = new CIFast_IFast_ifastcbo_warn_plan_cannot_be_manually_created();
            break;
        case 1702590: /* ERR_AMT_TYPE_NOT_APPL_FOR_FND_LOAD_TYPE */
            conditionObj = new CIFast_IFast_ifastcbo_err_amt_type_not_appl_for_fnd_load_type();
            break;
        case 1702591: /* WARN_AMT_TYPE_NOT_APPL_FOR_FND_LOAD_TYPE */
            conditionObj = new CIFast_IFast_ifastcbo_warn_amt_type_not_appl_for_fnd_load_type();
            break;
        case 1702592: /* ERR_AMT_TYPE_NOT_APPL_FOR_CHARGEBACK_LOAD_TYPE_REDMP */
            conditionObj = new CIFast_IFast_ifastcbo_err_amt_type_not_appl_for_chargeback_load_type_redmp();
            break;
        case 1702593: /* WARN_AMT_TYPE_NOT_APPL_FOR_CHARGEBACK_LOAD_TYPE_REDMP */
            conditionObj = new CIFast_IFast_ifastcbo_warn_amt_type_not_appl_for_chargeback_load_type_redmp();
            break;
        case 1702594: /* ERR_AMT_TYPE_NOT_APPL_FOR_BACKEND_LOAD_TYPE_REDMP */
            conditionObj = new CIFast_IFast_ifastcbo_err_amt_type_not_appl_for_backend_load_type_redmp();
            break;
        case 1702595: /* WARN_AMT_TYPE_NOT_APPL_FOR_BACKEND_LOAD_TYPE_REDMP */
            conditionObj = new CIFast_IFast_ifastcbo_warn_amt_type_not_appl_for_backend_load_type_redmp();
            break;
        case 1702596: /* ERR_FROM_FND_CANNOT_BE_FND_LOAD_TYPE_FOR_AMT */
            conditionObj = new CIFast_IFast_ifastcbo_err_from_fnd_cannot_be_fnd_load_type_for_amt();
            break;
        case 1702597: /* WARN_FROM_FND_CANNOT_BE_FND_LOAD_TYPE_FOR_AMT */
            conditionObj = new CIFast_IFast_ifastcbo_warn_from_fnd_cannot_be_fnd_load_type_for_amt();
            break;
        case 1702598: /* ERR_FROM_FND_CANNOT_BE_BACKEND_LOAD_TYPE_FOR_AMT */
            conditionObj = new CIFast_IFast_ifastcbo_err_from_fnd_cannot_be_backend_load_type_for_amt();
            break;
        case 1702599: /* WARN_FROM_FND_CANNOT_BE_BACKEND_LOAD_TYPE_FOR_AMT */
            conditionObj = new CIFast_IFast_ifastcbo_warn_from_fnd_cannot_be_backend_load_type_for_amt();
            break;
        case 1702600: /* ERR_FROM_FND_CANNOT_BE_CHARGEBACK_LOAD_TYPE_FOR_AMT */
            conditionObj = new CIFast_IFast_ifastcbo_err_from_fnd_cannot_be_chargeback_load_type_for_amt();
            break;
        case 1702601: /* WARN_FROM_FND_CANNOT_BE_CHARGEBACK_LOAD_TYPE_FOR_AMT */
            conditionObj = new CIFast_IFast_ifastcbo_warn_from_fnd_cannot_be_chargeback_load_type_for_amt();
            break;
        case 1702602: /* ERR_ACCT_NOT_ELIGIBLE_MONEY_IN_AGE_LESS_THAN_MINIMUM */
            conditionObj = new CIFast_IFast_ifastcbo_err_acct_not_eligible_money_in_age_less_than_minimum();
            break;
        case 1702603: /* WARN_ACCT_NOT_ELIGIBLE_MONEY_IN_AGE_LESS_THAN_MINIMUM */
            conditionObj = new CIFast_IFast_ifastcbo_warn_acct_not_eligible_money_in_age_less_than_minimum();
            break;
        case 1702604: /* ERR_ACCT_NOT_TFSA_ELIGIBLE_BASED_ON_DOB_AND_TAXJURIS */
            conditionObj = new CIFast_IFast_ifastcbo_err_acct_not_tfsa_eligible_based_on_dob_and_taxjuris();
            break;
        case 1702605: /* WARN_ACCT_NOT_TFSA_ELIGIBLE_BASED_ON_DOB_AND_TAXJURIS */
            conditionObj = new CIFast_IFast_ifastcbo_warn_acct_not_tfsa_eligible_based_on_dob_and_taxjuris();
            break;
        case 1702606: /* ERR_REFUND_UNITS_EXCEED_THE_AVAILABLE_UNIT_BALANCE */
            conditionObj = new CIFast_IFast_ifastcbo_err_refund_units_exceed_the_available_unit_balance();
            break;
        case 1702607: /* WARN_REFUND_UNITS_EXCEED_THE_AVAILABLE_UNIT_BALANCE */
            conditionObj = new CIFast_IFast_ifastcbo_warn_refund_units_exceed_the_available_unit_balance();
            break;
		case 1702608: /* ERR_SETTLEMENT_RULE_PENDING_TRADE_EXISTS */
			conditionObj = new CIFast_IFast_ifastcbo_err_settlement_rule_pending_trade_exists();
			break;
		case 1702609: /* WARN_SETTLEMENT_RULE_PENDING_TRADE_EXISTS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_settlement_rule_pending_trade_exists();
			break;
		case 1702610: /* ERR_INVALID_CUSIP_NUMBER */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_cusip_number();
			break;
		case 1702611: /* WARN_INVALID_CUSIP_NUMBER */
			conditionObj = new CIFast_IFast_ifastcbo_warn_invalid_cusip_number();
			break;
		case 1702612: /* ERR_SETTLEMENT_RULE_STOP_DATE_MUST_BE_EARLIER_THAN_CURRENT_BUSINESS_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_settlement_rule_stop_date_must_be_earlier_than_current_business_date();
			break;
		case 1702613: /* WARN_SETTLEMENT_RULE_STOP_DATE_MUST_BE_EARLIER_THAN_CURRENT_BUSINESS_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_settlement_rule_stop_date_must_be_earlier_than_current_business_date();
			break;
		case 1702614: /* EMAIL is blank */
			conditionObj = new CIFast_IFast_ifastcbo_err_entity_email_blank();
			break;
		case 1702615: /* First name is blank */
			conditionObj = new CIFast_IFast_ifastcbo_err_entity_first_name_blank();
			break;
		case 1702616: /* Account manager ID is mandatory */
			conditionObj = new CIFast_IFast_ifastcbo_err_entity_account_manager_id_mandatory();
			break;
		case 1702617: /* WARN_ACCOUNT_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_acct_min_initial_purchase_units();
			break;
		case 1702618: /* ERR_ACCOUNT_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS */
			conditionObj = new CIFast_IFast_ifastcbo_err_acct_min_initial_purchase_units();
			break;
		case 1702619: /* WARN_BROKER_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_broker_min_initial_purchase_units();
			break;
		case 1702620: /* ERR_BROKER_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS */
			conditionObj = new CIFast_IFast_ifastcbo_err_broker_min_initial_purchase_units();
			break;
		case 1702621: /* WARN_BRANCH_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_branch_min_initial_purchase_units();
			break;
		case 1702622: /* ERR_BRANCH_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS*/
			conditionObj = new CIFast_IFast_ifastcbo_err_branch_min_initial_purchase_units();
			break;
		case 1702623: /* WARN_SALES_REP_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_sales_rep_min_initial_purchase_units();
			break;
		case 1702624: /* ERR_SALES_REP_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS */
			conditionObj = new CIFast_IFast_ifastcbo_err_sales_rep_min_initial_purchase_units();
			break;
		case 1702625: /* WARN_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_min_initial_purchase_units();
			break;
		case 1702626: /* ERR_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS */
			conditionObj = new CIFast_IFast_ifastcbo_err_min_initial_purchase_units();
			break;
	    case 1702627: /* seg_event_during_create_trade */
			conditionObj = new CIFast_IFast_ifastcbo_err_Settledate_less_than_fund_level_Settledate();
			break;
		case 1702628: /* WARN_SETTLEDATE_LESS_THAN_FUND_LEVEL_SETTLEDATE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_Settledate_less_than_fund_level_Settledate();
			break;
		case 1702629: /* ERR_SETTLEDAYS_LESS_THAN_FUND_LEVEL_SETTLEDAYS */
			conditionObj = new CIFast_IFast_ifastcbo_err_Settledays_less_than_fund_level_Settledays();
			break;
		case 1702630: /* WARN_SETTLEDAYS_LESS_THAN_FUND_LEVEL_SETTLEDAYS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_Settledays_less_than_fund_level_Settledays();
			break;
	    case 1702631: /* seg_event_during_create_trade */
	 	    conditionObj = new CIFast_IFast_ifastcbo_err_seg_event_during_create_trade();
			break;
		case 1702632: /* seg_event_during_create_trade */
			conditionObj = new CIFast_IFast_ifastcbo_warn_seg_event_during_create_trade();
			break;
        case 1702633: /* ERR_ACCT_LESS_THAN_MIN_INIT_RED */
            conditionObj = new CIFast_IFast_ifastcbo_err_acct_less_than_min_init_red();
            break;
        case 1702634: /* WARN_ACCT_LESS_THAN_MIN_INIT_RED */
            conditionObj = new CIFast_IFast_ifastcbo_warn_acct_less_than_min_init_red();
            break;
        case 1702635: /* ERR_BROKER_LESS_THAN_MIN_INIT_RED */
            conditionObj = new CIFast_IFast_ifastcbo_err_broker_less_than_min_init_red();
            break;
        case 1702636: /* WARN_BROKER_LESS_THAN_MIN_INIT_RED */
            conditionObj = new CIFast_IFast_ifastcbo_warn_broker_less_than_min_init_red();
            break;
        case 1702637: /* ERR_BRANCH_LESS_THAN_MIN_INIT_RED */
            conditionObj = new CIFast_IFast_ifastcbo_err_branch_less_than_min_init_red();
            break;
        case 1702638: /* WARN_BRANCH_LESS_THAN_MIN_INIT_RED */
            conditionObj = new CIFast_IFast_ifastcbo_warn_branch_less_than_min_init_red();
            break;
        case 1702639: /* ERR_SLSREP_LESS_THAN_MIN_INIT_RED */
            conditionObj = new CIFast_IFast_ifastcbo_err_slsrep_less_than_min_init_red();
            break;
        case 1702640: /* WARN_SLSREP_LESS_THAN_MIN_INIT_RED */
            conditionObj = new CIFast_IFast_ifastcbo_warn_slsrep_less_than_min_init_red();
            break;
        case 1702641: /* ERR_ACCT_LESS_THAN_MIN_SUBSEQ_RED */
            conditionObj = new CIFast_IFast_ifastcbo_err_acct_less_than_min_subseq_red();
            break;
        case 1702642: /* WARN_ACCT_LESS_THAN_MIN_SUBSEQ_RED */
            conditionObj = new CIFast_IFast_ifastcbo_warn_acct_less_than_min_subseq_red();
            break;
        case 1702643: /* ERR_BROKER_LESS_THAN_MIN_SUBSEQ_RED */
            conditionObj = new CIFast_IFast_ifastcbo_err_broker_less_than_min_subseq_red();
            break;
        case 1702644: /* WARN_BROKER_LESS_THAN_MIN_SUBSEQ_RED */
            conditionObj = new CIFast_IFast_ifastcbo_warn_broker_less_than_min_subseq_red();
            break;
        case 1702645: /* ERR_BRANCH_LESS_THAN_MIN_SUBSEQ_RED */
            conditionObj = new CIFast_IFast_ifastcbo_err_branch_less_than_min_subseq_red();
            break;
        case 1702646: /* WARN_BRANCH_LESS_THAN_MIN_SUBSEQ_RED */
            conditionObj = new CIFast_IFast_ifastcbo_warn_branch_less_than_min_subseq_red();
            break;
        case 1702647: /* ERR_SLSREP_LESS_THAN_MIN_SUBSEQ_RED */
            conditionObj = new CIFast_IFast_ifastcbo_err_slsrep_less_than_min_subseq_red();
            break;
        case 1702648: /* WARN_SLSREP_LESS_THAN_MIN_SUBSEQ_RED */
            conditionObj = new CIFast_IFast_ifastcbo_warn_slsrep_less_than_min_subseq_red();
            break;
		case 1702649: /* ERR_CESG_ADCESG_AMOUNT_BE_RETURNED_BECAUSE_REDEMPTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_cesg_adcesg_amount_be_returned_because_redemption();
			break;
		case 1702650: /* WARN_CESG_ADCESG_AMOUNT_BE_RETURNED_BECAUSE_REDEMPTION */
			conditionObj = new CIFast_IFast_ifastcbo_warn_cesg_adcesg_amount_be_returned_because_redemption();
			break;
		case 1702651: /* ERR_CASH_DATE_MANDATORY */
			conditionObj = new CIFast_IFast_ifastcbo_err_cash_date_mandatory();
			break;
		case 1702652: /* WARN_CASH_DATE_MANDATORY */
			conditionObj = new CIFast_IFast_ifastcbo_warn_cash_date_mandatory();
			break;
		case 1702653: /* ERR_TRADE_WILL_CREATE_NEGATIVE_NOTIONAL_BALANCE_UC_AC_YTD */
			conditionObj = new CIFast_IFast_ifastcbo_err_trade_will_create_negative_notional_balance_uc_ac_ytd();
			break;
		case 1702654: /* WARN_TRADE_WILL_CREATE_NEGATIVE_NOTIONAL_BALANCE_UC_AC_YTD */
			conditionObj = new CIFast_IFast_ifastcbo_warn_trade_will_create_negative_notional_balance_uc_ac_ytd();
			break;
		case 1702655: /*ERR_ABSOLUTE_VALUE_THRESHOLD_BREACHED*/
			conditionObj = new CIFast_IFast_ifastcbo_err_absolute_value_threshold_breached();
			break; 
		case 1702656: /* WARN_ABSOLUTE_VALUE_THRESHOLD_BREACHED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_absolute_value_threshold_breached();
			break;
		case 1702657: /*ERR_PERCENTAGE_OF_CLASS_HOLDINGS_BREACHED*/
			conditionObj = new CIFast_IFast_ifastcbo_err_percentage_of_class_holdings_breached();
			break;
		case 1702658: /* WARN_PERCENTAGE_OF_CLASS_HOLDINGS_BREACHED*/
			conditionObj = new CIFast_IFast_ifastcbo_warn_percentage_of_class_holdings_breached();
			break;
		case 1702659: /*ERR_INITIAL_MONEY_IN_TO_A_CLASS */
			conditionObj = new CIFast_IFast_ifastcbo_err_initial_money_in_to_class();
			break;
		case 1702660: /*WARN_INITIAL_MONEY_IN_TO_A_CLASS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_initial_money_in_to_class();
			break;
        case 1702661: /* ERR_COUNTRY_OF_EXPR_IS_REQUIRED */
            conditionObj = new CIFast_IFast_ifastcbo_err_country_of_expr_is_required();
            break;
        case 1702662: /* WARN_COUNTRY_OF_EXPR_IS_REQUIRED */
            conditionObj = new CIFast_IFast_ifastcbo_warn_country_of_expr_is_required();
            break;
		case 1702663: /* WARN_DUPLICATE_TRADE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_duplicate_trade();
			break;
		case 1702664: /* ERR_ACCOUNT_ROUNDING_RULE_MANDATORY */
			conditionObj = new CIFast_IFast_ifastcbo_err_account_rounding_rule_mandatory();
			break;
		case 1702665: /* WARN_ACCOUNT_ROUNDING_RULE_MANDATORY */
			conditionObj = new CIFast_IFast_ifastcbo_warn_account_rounding_rule_mandatory();
			break;
		case 1702666: /* ERR_ACCOUNT_ROUNDING_RULE_TRADE_EXISTS */
			conditionObj = new CIFast_IFast_ifastcbo_err_account_rounding_rule_trade_exists();
			break;
		case 1702667: /* WARN_ACCOUNT_ROUNDING_RULE_TRADE_EXISTS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_account_rounding_rule_trade_exists();
			break;	
		case 1702668 : /*ERR_PERCENTAGE_OF_TRADES_SETTLEMENT_CURRENCY_BREACHED*/
			conditionObj = new CIFast_IFast_ifastcbo_err_percentage_of_trades_settlement_currency_breached();
			break;
		case 1702669 : /*WARN_PERCENTAGE_OF_TRADES_SETTLEMENT_CURRENCY_BREACHED*/
			conditionObj = new CIFast_IFast_ifastcbo_warn_percentage_of_trades_settlement_currency_breached();
			break;
		case 1702670 : /*ERR_PERCENTAGE_OF_TRADES_AMOUNT_TYPE_BREACHED*/
			conditionObj = new CIFast_IFast_ifastcbo_err_percentage_of_trades_settlement_currency_breached();
			break;
		case 1702671 : /*WARN_PERCENTAGE_OF_TRADES_AMOUNT_TYPE_BREACHED*/
			conditionObj = new CIFast_IFast_ifastcbo_warn_percentage_of_trades_amount_type_breached();
			break;
        case 1702672: /* ERR_FIRSTNAME_IS_MANDATORY_FOR_ENTITY_TYPE */
            conditionObj = new CIFast_IFast_ifastcbo_err_firstname_is_mandatory_for_entity_type();
            break;
        case 1702673: /* WARN_FIRSTNAME_IS_MANDATORY_FOR_ENTITY_TYPE */
            conditionObj = new CIFast_IFast_ifastcbo_warn_firstname_is_mandatory_for_entity_type();
            break;
		case 1702674: /*ERR_FUND_COMPANY_APPROVAL_REQUIRED*/
			conditionObj = new CIFast_IFast_ifastcbo_err_fund_company_available_required();
			break;
		case 1702675: /*WARN_FUND_COMPANY_APPROVAL_REQUIRED*/
			conditionObj = new CIFast_IFast_ifastcbo_warn_fund_company_available_required();
			break;
		case 1702676: /*ERR_GENERAL_AGREEMENT_NOT_AVAILABLE*/
			conditionObj = new CIFast_IFast_ifastcbo_err_general_agreement_not_available();
			break;
		case 1702677: /*WARN_GENERAL_AGREEMENT_NOT_AVAILABLE*/
			conditionObj = new CIFast_IFast_ifastcbo_warn_general_agreement_not_available();
			break;
		case 1702678: /* ERR_LESS_THAN_MINIMUM_INITIAL_BUYBACK_AMOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_less_then_minimum_initial_buyback_amount();
			break;	
		case 1702679: /* WARN_LESS_THAN_MINIMUM_INITIAL_BUYBACK_AMOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_less_then_minimum_initial_buyback_amount();
			break;
        case 1702680: /* ERR_HIGHEST_RISK_LVL_IS_REQUIRED */
            conditionObj = new CIFast_IFast_ifastcbo_err_highest_risk_lvl_is_required();
            break;
        case 1702681: /* WARN_HIGHEST_RISK_LVL_IS_REQUIRED */
            conditionObj = new CIFast_IFast_ifastcbo_warn_highest_risk_lvl_is_required();
            break;
        case 1702682: /* ERR_INVALID_HIGHEST_RISK_LEVEL */
            conditionObj = new CIFast_IFast_ifastcbo_err_invalid_highest_risk_level();
            break;
        case 1702683: /* WARN_INVALID_HIGHEST_RISK_LEVEL */
            conditionObj = new CIFast_IFast_ifastcbo_warn_invalid_highest_risk_level();
            break;
		case 1702684: /* ERR_ACCOUNT_ROUNDING_RULE_EXISTS */
			conditionObj = new CIFast_IFast_ifastcbo_err_account_rounding_rule_exists();
			break;
		case 1702685: /* WARN_ACCOUNT_ROUNDING_RULE_EXISTS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_account_rounding_rule_exists();
			break;
		case 1702686: /*ERR_ACCOUNT_HOLDING_LESS_THAN_MINIMUM_HOLDING_AMOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_account_holding_less_than_minimum_holding_amount();
			break;
		case 1702687: /*WARN_ACCOUNT_HOLDING_LESS_THAN_MINIMUM_HOLDING_AMOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_account_holding_less_than_minimum_holding_amount();
			break;
		case 1702688: /* ERR_ANNUITANT_DOFBIRTH_IS_CHANGING */
			conditionObj = new CIFast_IFast_ifastcbo_err_annuitant_date_of_birth_is_changing();
			break;
		case 1702689: /* WARN_ANNUITANT_DOFBIRTH_IS_CHANGING */
			conditionObj = new CIFast_IFast_ifastcbo_warn_annuitant_date_of_birth_is_changing();
			break;
		case 1702690: /* ERR_NOTIONAL_AMOUNTS_UPDATE_FOR_CANCELLED_OR_REVERSED_TRADE_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_notional_amounts_update_for_cancelled_or_reversed_trade_not_allowed();
			break;
		case 1702691: /* WARN_NOTIONAL_AMOUNTS_UPDATE_FOR_CANCELLED_OR_REVERSED_TRADE_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_notional_amounts_update_for_cancelled_or_reversed_trade_not_allowed();
			break;
		case 1702692: /* ERR_NOTIONALS_MANUAL_OVERRIDE_RECOMMENDED_FOR_MULTIPLE_TRANSFERS */
			conditionObj = new CIFast_IFast_ifastcbo_err_notionals_manual_override_recommended_for_multiple_transfers();
			break;
		case 1702693: /* WARN_NOTIONALS_MANUAL_OVERRIDE_RECOMMENDED_FOR_MULTIPLE_TRANSFERS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_notionals_manual_override_recommended_for_multiple_transfers();
			break;
		case 1702694: /* ERR_NOTIONALS_MANUAL_OVERRIDE_MAY_BE_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_notionals_manual_override_may_be_required();
			break;
		case 1702695: /* WARN_NOTIONALS_MANUAL_OVERRIDE_MAY_BE_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_notionals_manual_override_may_be_required();
			break;
		case 1702696: /* ERR_PIM_INST_ACCT_MUST_BE_ADDED_TO_CUSTODIAN */
			conditionObj = new CIFast_IFast_ifastcbo_err_pim_inst_acct_must_be_added_to_custodian();
			break;
		case 1702697: /* WARN_PIM_INST_ACCT_MUST_BE_ADDED_TO_CUSTODIAN */
			conditionObj = new CIFast_IFast_ifastcbo_warn_pim_inst_acct_must_be_added_to_custodian();
			break;
		case 1702698: /* ERR_DIF_FUND_ONLY_ALLOW_DIRECT_ORDER */
			conditionObj = new CIFast_IFast_ifastcbo_err_dif_fund_only_allow_direct_order();
			break;
		case 1702699: /* WARN_DIF_FUND_ONLY_ALLOW_DIRECT_ORDER */
			conditionObj = new CIFast_IFast_ifastcbo_warn_dif_fund_only_allow_direct_order();
			break;
		case 1702700: /* ERR_BONUS_INTEREST_RATE_SETUP_ONLY_FOR_DIF_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_bonus_interrest_rate_setup_only_for_dif_fund();
			break;
		case 1702701: /* WARN_BONUS_INTEREST_RATE_SETUP_ONLY_FOR_DIF_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_warn_bonus_interrest_rate_setup_only_for_dif_fund();
			break;
		case 1702702: /* ERR_INVALID_TRADEINDATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_tradeindate();
			break;
		case 1702703: /* ERR_NOTIONAL_PAID_BY_OTHER_AMOUNTS_MUST_BE_POSITIVE */
			conditionObj = new CIFast_IFast_ifastcbo_err_notional_paid_by_other_amounts_must_be_positive();
			break;
		case 1702704: /* WARN_NOTIONAL_PAID_BY_OTHER_AMOUNTS_MUST_BE_POSITIVE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_notional_paid_by_other_amounts_must_be_positive();
			break;
		case 1702705: /* ERR_INVALID_TFN_VALUE */
			conditionObj = new  CIFast_IFast_ifastcbo_err_Invalid_tfn_value();
			break;
		case 1702706: /* WARN_INVALID_TFN_VALUE */
			conditionObj = new  CIFast_IFast_ifastcbo_warn_Invalid_tfn_value();
			break;
		case 1702707: /* ERR_INVALID_ABN_VALUE */
			conditionObj = new  IFast_IFast_ifastcbo_err_Invalid_australian_business_number_value();
			break;
		case 1702708: /* WARN_INVALID_ABN_VALUE */
			conditionObj = new  IFast_IFast_ifastcbo_warn_Invalid_australian_business_number_value();
			break;		
		case 1702709: /* ERR_DILUTION_LINK_ID_DOES_NOT_EXIST */
			conditionObj = new  CIFast_IFast_ifastcbo_err_dilution_link_id_does_not_exist();
			break;
		case 1702710: /* WARN_DILUTION_LINK_ID_DOES_NOT_EXIST */
			conditionObj = new  CIFast_IFast_ifastcbo_warn_dilution_link_id_does_not_exist();
			break;
		case 1702711: /* ERR_DILUTION_LINK_ID_AUTO_GENERATE */
			conditionObj = new  CIFast_IFast_ifastcbo_err_dilution_link_id_auto_generate();
			break;
		case 1702712: /* WARN_DILUTION_LINK_ID_AUTO_GENERATE */
			conditionObj = new  CIFast_IFast_ifastcbo_warn_dilution_link_id_auto_generate();
			break;
		case 1702713: /* ERR_SUM_OF_DELTA_MUST_BE_0 */
			conditionObj = new CIFast_IFast_ifastcbo_err_sum_of_delta_must_be_0();
			break;
		case 1702714: /* ERR_UNREVERSED_TERMINATION_ENTRIES_EXIST */
			conditionObj = new CIFast_IFast_ifastcbo_err_unreversed_termination_entries_exist();
			break;
		case 1702715: /* WARN_UNREVERSED_TERMINATION_ENTRIES_EXIST */
			conditionObj = new CIFast_IFast_ifastcbo_warn_unreversed_termination_entries_exist();
			break;
		case 1702716: /* ERR_DELTA_MUST_WITHIN_100 */
			conditionObj = new CIFast_IFast_ifastcbo_err_delta_must_within_100();
			break;
		case 1702717: /* ERR_BSB_FORMAT_IS_INCORRECT */
			conditionObj = new CIFast_IFast_ifastcbo_err_bsb_format_is_incorrect();
			break;
		case 1702718: /* ERR_BSB_BANK_ACCT_AUD_FORMAT_IS_INCORRECT */
			conditionObj = new CIFast_IFast_ifastcbo_err_bsb_bank_acct_aud_format_is_incorrect();
			break;
		case 1702719: /* ERR_BSB_BANK_ACCT_FOREIGN_FORMAT_IS_INCORRECT */
			conditionObj = new CIFast_IFast_ifastcbo_err_bsb_bank_acct_foreign_format_is_incorrect();
			break;
		case 1702720: /* ERR_ONLY_ONE_REC_WITH_100_PERCENT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_only_one_rec_with_100_percent_allowed();
			break;
		case 1702721: /* WARN_ONLY_ONE_REC_WITH_100_PERCENT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_only_one_rec_with_100_percent_allowed();
			break;
		case 1702722: /* ERR_DILUTION_LINK_ID_IS_ASSOCIATED_F50_TRADE */
			conditionObj = new CIFast_IFast_ifastcbo_err_dilution_link_id_is_associated_F50_trade();
			break;
		case 1702723: /* WARN_DILUTION_LINK_ID_IS_ASSOCIATED_F50_TRADE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_dilution_link_id_is_associated_F50_trade();
			break;
		case 1702724: /* ERR_DILUTION_NSM_EXTERNAL_NSM_ONLY_ONE_YES */
			conditionObj = new CIFast_IFast_ifastcbo_err_dilution_nsm_external_nsm_only_one_yes();
			break;
		case 1702725: /* WARN_DILUTION_NSM_EXTERNAL_NSM_ONLY_ONE_YES */
			conditionObj = new CIFast_IFast_ifastcbo_warn_dilution_nsm_external_nsm_only_one_yes();
			break;		
		case 1702726: /* ERR_DUPLICATE_BUSINESS_NUMBER */
			conditionObj = new CIFast_IFast_ifastcbo_err_duplicate_business_number();
			break;
		case 1702727: /* WARN_DUPLICATE_BUSINESS_NUMBER */
			conditionObj = new CIFast_IFast_ifastcbo_warn_duplicate_business_number();
			break;
		case 1702728: /* ERR_PENDING_ALLOCATION_TRADE */ //INC0039323
			conditionObj = new CIFast_IFast_ifastcbo_err_pending_allocation_trade();
			break;
		case 1702729: /* WAR_PENDING_ALLOCATION_TRADE *///INC0039323
			conditionObj = new CIFast_IFast_ifastcbo_warn_pending_allocation_trade();
			break;
		case 1702730: /* ERR_TRADING_SUSPENSION_ACTIVE_FOR_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_trading_suspension_active_for_fund();
			break;
		case 1702731: /* WARN_TRADING_SUSPENSION_ACTIVE_FOR_FUND */
			conditionObj = new CIFast_IFast_ifastcbo_warn_trading_suspension_active_for_fund();
			break;
		case 1702732: /* ERR_INVALID_PAYMENT_METHOD */
			conditionObj = new CIFast_IFast_ifastcbo_err_invalid_payment_method();
			break;
		case 1702733: /* ERR_FUND_SUBJECT_TO_LIQUIDITY_GATING_MEASURE */
			conditionObj = new CIFast_IFast_ifastcbo_err_attention_fund_subject_to_liquidity_gating();
			break;
		case 1702734: /* WARN_FUND_SUBJECT_TO_LIQUIDITY_GATING_MEASURE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_attention_fund_subject_to_liquidity_gating();
			break;
		case 1702735: /* ERR_DEATHDATE_UPDATION_DISABLED */
			conditionObj = new CIFast_IFast_ifastcbo_err_deathdate_updation_disabled_for_entity_type();
			break;
		case 1702736: /* ERR_DEATHDATE_NOTIFICATION_UPDATION_DISABLED */
			conditionObj = new CIFast_IFast_ifastcbo_err_deathdate_notification_updation_disabled_for_entity_type();
			break;
		case 1702737: /* ERR_RDSP_BENEFICIARY_NON_RESIDENT */
			conditionObj = new CIFast_IFast_ifastcbo_err_rdsp_beneficiary_non_resident();
			break;
		case 1702738: /* WARN_RDSP_BENEFICIARY_NON_RESIDENT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_rdsp_beneficiary_non_resident();
			break;
		case 1702739: /* ERR_RDSP_BENEFICIARY_OVER_AGE_LIMIT */
			conditionObj = new CIFast_IFast_ifastcbo_err_rdsp_beneficiary_over_age_limit();
			break;
		case 1702740: /* WARN_RDSP_BENEFICIARY_OVER_AGE_LIMIT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_rdsp_beneficiary_over_age_limit();
			break;		 
		case 1702741: /* ERR_RDSP_BENEFICIARY_MUST_BE_RESIDENT_OF_CANADA */
			conditionObj = new CIFast_IFast_ifastcbo_err_rdsp_beneficiary_must_be_resident_of_canada();
			break;
		case 1702742: /* WARN_RDSP_BENEFICIARY_MUST_BE_RESIDENT_OF_CANADA */
			conditionObj = new CIFast_IFast_ifastcbo_warn_rdsp_beneficiary_must_be_resident_of_canada();
			break;
		case 1702743: /* ERR_RDSP_BENEFICIARY_OVER_AGE_OF_CONTRIBUTION */
			conditionObj = new CIFast_IFast_ifastcbo_err_rdsp_beneficiary_over_age_of_contribution();
			break;
		case 1702744: /* WARN_RDSP_BENEFICIARY_OVER_AGE_OF_CONTRIBUTION */
			conditionObj = new CIFast_IFast_ifastcbo_warn_rdsp_beneficiary_over_age_of_contribution();
			break;
		case 1702745: /* ERR_RDSP_BENEFICIARY_ENTITY_MUST_BE_SETUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_rdsp_beneficiary_entity_must_be_setup();
			break;
		case 1702746: /* ERR_RDSP_BENEFICIARY_ENTITY_IS_NOT_ALLOWED_FOR_THIS_TAX_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rdsp_beneficiary_entity_is_not_allowed_for_this_tax_type();
			break;
		case 1702747: /* ERR_RDSP_ONLY_ONE_BENF_ALLOW */
			conditionObj = new CIFast_IFast_ifastcbo_err_rdsp_only_one_benf_allow();
			break;
		case 1702748: /* WARN_RDSP_ONLY_ONE_BENF_ALLOW */
			conditionObj = new CIFast_IFast_ifastcbo_warn_rdsp_only_one_benf_allow();
			break;
		case 1702749: /* ERR_RDSP_ONLY_TWO_PCG_ALLOW */
			conditionObj = new CIFast_IFast_ifastcbo_err_rdsp_only_two_pcg_allow();
			break;
		case 1702750: /* WARN_RDSP_ONLY_TWO_PCG_ALLOW */
			conditionObj = new CIFast_IFast_ifastcbo_warn_rdsp_only_two_pcg_allow();
			break;
		case 1702751: /* ERR_RDSP_TRADE_NOT_ALLOWED_ACCOUNT_DTC_ELECT */
			conditionObj = new CIFast_IFast_ifastcbo_err_rdsp_trade_not_allowed_account_sdsp_elect();
			break;
		case 1702752: /* WARN_RDSP_TRADE_NOT_ALLOWED_ACCOUNT_DTC_ELECT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_rdsp_trade_not_allowed_account_sdsp_elect();
			break;	
		case 1702753: /* ERR_RDSP_TRADE_NOT_ALLOWED_ACCOUNT_DTC_ELECT */
			conditionObj = new CIFast_IFast_ifastcbo_err_rdsp_trade_not_allowed_account_dtc_elect();
			break;
		case 1702754: /* WARN_RDSP_TRADE_NOT_ALLOWED_ACCOUNT_DTC_ELECT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_rdsp_trade_not_allowed_account_dtc_elect();
			break; 
		case 1702755: /* ERR_RDSP_STATUS_DOES_NOT_ALLOW_CONTRIBUTIONS */
			conditionObj = new CIFast_IFast_ifastcbo_err_rdsp_status_does_not_allow_contributions();
			break;
		case 1702756: /* WARN_RDSP_STATUS_DOES_NOT_ALLOW_CONTRIBUTIONS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_rdsp_status_does_not_allow_contributions();
			break;
		case 1702757: /* ERR_RDSP_TRADE_DATE_AFTER_BENEFICIARY_DATE_OF_DEATH */
			conditionObj = new CIFast_IFast_ifastcbo_err_rdsp_trade_date_after_beneficiary_date_of_death();
			break;
		case 1702758: /* WARN_RDSP_TRADE_DATE_AFTER_BENEFICIARY_DATE_OF_DEATH */
			conditionObj = new CIFast_IFast_ifastcbo_warn_rdsp_trade_date_after_beneficiary_date_of_death();
			break;
		case 1702759: /* ERR_RDSP_MAX_CONTRIBUTIONS_LTA_EXCEEDED */
			conditionObj = new CIFast_IFast_ifastcbo_err_rdsp_max_contributions_lta_exceeded();
			break;
		case 1702760: /* WARN_RDSP_MAX_CONTRIBUTIONS_LTA_EXCEEDED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_rdsp_max_contributions_lta_exceeded();
			break;
		case 1702761: /* ERR_RDSP_EXTERNAL_CONTRACT_MANDATORY */
			conditionObj = new CIFast_IFast_ifastcbo_err_rdsp_external_contract_mandatory();
			break;
		case 1702762: /* WARN_RDSP_EXTERNAL_CONTRACT_MANDATORY */
			conditionObj = new CIFast_IFast_ifastcbo_warn_rdsp_external_contract_mandatory();
			break;
		case 1702763: /* ERR_RDSP_EXTERNAL_PLAN_MANDATORY */
			conditionObj = new CIFast_IFast_ifastcbo_err_rdsp_external_plan_mandatory();
			break;
		case 1702764: /* WARN_RDSP_EXTERNAL_PLAN_MANDATORY */
			conditionObj = new CIFast_IFast_ifastcbo_warn_rdsp_external_plan_mandatory();
			break;
		case 1702765: /* ERR_RDSP_PCG_ENTITY_MUST_BE_SETUP */
			conditionObj = new CIFast_IFast_ifastcbo_err_rdsp_pcg_entity_must_be_setup();
			break;
		case 1702766: /* WARN_RDSP_PCG_ENTITY_MUST_BE_SETUP */
			conditionObj = new CIFast_IFast_ifastcbo_warn_rdsp_pcg_entity_must_be_setup();
			break;
		case 1702767: /* ERR_RDSP_CANNOT_BACKDATE_TRADE_BEFORE_MONEY_OUT_TRANS */
			conditionObj = new CIFast_IFast_ifastcbo_err_rdsp_cannot_backdate_trade_before_money_out_trans();
			break;
		case 1702768: /* WARN_RDSP_CANNOT_BACKDATE_TRADE_BEFORE_MONEY_OUT_TRANS */
			conditionObj = new CIFast_IFast_ifastcbo_warn_rdsp_cannot_backdate_trade_before_money_out_trans();
			break;
		case 1702769: /* ERR_RDSP_REPAYMENT_REASON_MANDATORY */
			conditionObj = new CIFast_IFast_ifastcbo_err_rdsp_repayment_reason_mandatory();
			break;
		case 1702770: /* WARN_RDSP_REPAYMENT_REASON_MANDATORY */
			conditionObj = new CIFast_IFast_ifastcbo_warn_rdsp_repayment_reason_mandatory();
			break;
		case 1702771: /* ERR_RDSP_INVALID_REPAYMENT_REASON */
			conditionObj = new CIFast_IFast_ifastcbo_err_rdsp_invalid_repayment_reason();
			break;
		case 1702772: /* WARN_RDSP_INVALID_REPAYMENT_REASON */
			conditionObj = new CIFast_IFast_ifastcbo_warn_rdsp_invalid_repayment_reason();
			break;
		case 1702773: /* ERR_RDSP_FMV_LESS_THAN_AHA_AMOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_err_rdsp_fmv_less_than_aha_amount();
			break;
		case 1702774: /* WARN_RDSP_FMV_LESS_THAN_AHA_AMOUNT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_rdsp_fmv_less_than_aha_amount();
			break;
		case 1702775: /* ERR_RDSP_DAP_INVALID_REPAYMENT_REASON */
			conditionObj = new CIFast_IFast_ifastcbo_err_rdsp_dap_invalid_repayment_reason();
			break;
		case 1702776: /* WARN_RDSP_DAP_INVALID_REPAYMENT_REASON */
			conditionObj = new CIFast_IFast_ifastcbo_warn_rdsp_dap_invalid_repayment_reason();
			break; 
		case 1702777: /* ERR_RDSP_LDAP_INVALID_REPAYMENT_REASON */
			conditionObj = new CIFast_IFast_ifastcbo_err_rdsp_ldap_invalid_repayment_reason();
			break;
		case 1702778: /* WARN_RDSP_LDAP_INVALID_REPAYMENT_REASON */
			conditionObj = new CIFast_IFast_ifastcbo_warn_rdsp_ldap_invalid_repayment_reason();
			break;
		case 1702779: /* ERR_RDSP_FULL_WITHDRAWAL_INVALID_REPAYMENT_REASON */
			conditionObj = new CIFast_IFast_ifastcbo_err_rdsp_full_withdrawal_invalid_repayment_reason();
			break;
		case 1702780: /* WARN_RDSP_FULL_WITHDRAWAL_INVALID_REPAYMENT_REASON */
			conditionObj = new CIFast_IFast_ifastcbo_warn_rdsp_full_withdrawal_invalid_repayment_reason();
			break;
		case 1702781: /* ERR_RDSP_AMOUNT_NOT_BETWEEN_MIN_MAX */
			conditionObj = new CIFast_IFast_ifastcbo_err_rdsp_amount_not_between_min_max();
			break;
		case 1702782: /* WARN_RDSP_AMOUNT_NOT_BETWEEN_MIN_MAX */
			conditionObj = new CIFast_IFast_ifastcbo_warn_rdsp_amount_not_between_min_max();
			break;
		case 1702783: /* ERR_RDSP_RELATIONSHIP_TO_BENEFICIARY_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_err_rdsp_relationship_to_beneficiary_required();
			break;
		case 1702784: /* WARN_RDSP_RELATIONSHIP_TO_BENEFICIARY_REQUIRED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_rdsp_relationship_to_beneficiary_required();
			break;
		case 1702785: /* ERR_RDSP_API_TIMEOUT */
			conditionObj = new CIFast_IFast_ifastcbo_err_rdsp_api_timeout();
			break;
		case 1702786: /* WARN_RDSP_API_TIMEOUT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_rdsp_api_timeout();
			break;
		case 1702787: /* ERR_RDSP_BACKDATED_TRANSFER_OUT_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_rdsp_backdated_transfer_out_not_allowed();
			break;
		case 1702788: /* WARN_RDSP_BACKDATED_TRANSFER_OUT_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_rdsp_backdated_transfer_out_not_allowed();
			break;
		case 1702789: /* ERR_RDSP_PARTIAL_TRANSFER_OUT_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_rdsp_partial_transfer_out_not_allowed();
			break;
		case 1702790: /* WARN_RDSP_PARTIAL_TRANSFER_OUT_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_rdsp_partial_transfer_out_not_allowed();
			break;
		case 1702791: /* ERR_SWP_PERCENT_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastcbo_err_swp_percent_not_allowed();
			break;
		case 1702792: /* ERR_RDSP_MONEY_OUT_TRANS_EXISTS_AFTER_DATE_OF_PAYMENT */
			conditionObj = new CIFast_IFast_ifastcbo_err_rdsp_money_out_trans_exists_after_date_of_payment();
			break;
		case 1702793: /* WARN_RDSP_MONEY_OUT_TRANS_EXISTS_AFTER_DATE_OF_PAYMENT */
			conditionObj = new CIFast_IFast_ifastcbo_warn_rdsp_money_out_trans_exists_after_date_of_payment();
			break;
		case 1702794: /* ERR_TRADE_DATE_MUST_BE_EQUAL_OR_GREATER_THAN_PURCHASE_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_trade_date_equal_or_greater_than_purchase_date();
			break;			
		case 1702795: /*WARN_EMAIL_PHONE_DETAILS_CANNOT_BE_BLANK*/
			conditionObj = new CIFast_IFast_ifastcbo_warn_email_phone_details_cannot_be_blank();
			break;
		case 1702796: /*ERR_EMAIL_PHONE_DETAILS_CANNOT_BE_BLANK*/
			conditionObj = new CIFast_IFast_ifastcbo_err_email_phone_details_cannot_be_blank();
			break;
		case 1702797: /* ERR_RDSP_PCG_ENTITY_IS_NOT_ALLOWED_FOR_THIS_TAX_TYPE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rdsp_pcg_entity_is_not_allowed_for_this_tax_type();
			break;		
		case 1702798: /*ERR_BIC_CODE_LINKED_MSG */
			conditionObj = new IFast_IFast_ifastcbo_err_attention_biccode_linked_msg();
			break;
		case 1702799: /* WARN_BIC_CODE_LINKED_MSG */
			conditionObj = new IFast_IFast_ifastcbo_warn_attention_biccode_linked_msg();
			break;			
		case 1702800: /* ERR_FUND_SUBJECT_TO_LIQUIDITY_FEE_MEASURE */
			conditionObj = new CIFast_IFast_ifastcbo_err_attention_fund_subject_to_liquidity_fee();
			break;
		case 1702801: /* WARN_FUND_SUBJECT_TO_LIQUIDITY_FEE_MEASURE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_attention_fund_subject_to_liquidity_fee();
			break;		
		case 1702806: /* ERR_MATCHING_KEY_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastcbo_err_matching_key_not_found();
			break;
		case 1702807: /* WARN_MATCHING_KEY_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastcbo_warn_matching_key_not_found();
			break;
		case 1702808: /* WARN_INVALID_CASH_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_invalid_cash_date();
			break;
		case 1702809: /* ERR_CASH_DATE_MUST_BE_GREATER_THAN_TRADE_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_err_cash_date_must_be_greater_than_trade_date();
			break;
		case 1702810: /* WARN_CASH_DATE_MUST_BE_GREATER_THAN_TRADE_DATE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_cash_date_must_be_greater_than_trade_date();
			break;
		case 1702811: /* ERR_CASH_DATE_WILL_REMAIN_AS_ASSIGNED */
			conditionObj = new CIFast_IFast_ifastcbo_err_cash_date_will_remain_as_assigned();
			break;
		case 1702812: /* WARN_CASH_DATE_WILL_REMAIN_AS_ASSIGNED */
			conditionObj = new CIFast_IFast_ifastcbo_warn_cash_date_will_remain_as_assigned();
			break;
		case 1702813: /* ERR_RDSP_INSUFFICIENT_GRANT_BOND_BALANCE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rdsp_insufficient_grant_bond_balance();
			break;
		case 1702814: /* WARN_RDSP_INSUFFICIENT_GRANT_BOND_BALANCE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_rdsp_insufficient_grant_bond_balance();
			break;	
		case 1702815: /* ERR_RDSP_GRANT_RETURN_CANNOT_BE_GREATER_THAN_GRANT_PURCHASE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rdsp_grant_return_cannot_be_greater_than_grant_purchase();
			break;
		case 1702816: /* WARN_RDSP_GRANT_RETURN_CANNOT_BE_GREATER_THAN_GRANT_PURCHASE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_rdsp_grant_return_cannot_be_greater_than_grant_purchase();
			break;
		case 1702817: /* ERR_RDSP_BOND_RETURN_CANNOT_BE_GREATER_THAN_BOND_PURCHASE */
			conditionObj = new CIFast_IFast_ifastcbo_err_rdsp_bond_return_cannot_be_greater_than_bond_purchase();
			break;
		case 1702818: /* WARN_RDSP_BOND_RETURN_CANNOT_BE_GREATER_THAN_BOND_PURCHASE */
			conditionObj = new CIFast_IFast_ifastcbo_warn_rdsp_bond_return_cannot_be_greater_than_bond_purchase();
			break;		
		case 1702822: /* ERR_ACCOUNT_HAS_UNVERIFIED_DATA */
			conditionObj = new CIFast_IFast_ifastcbo_err_account_has_unverified_data();
			break;
		case 1702823: /* WARN_ACCOUNT_HAS_UNVERIFIED_DATA */
			conditionObj = new CIFast_IFast_ifastcbo_warn_account_has_unverified_data();
			break;
		case 1702824: /* ERR_RDSP_BENEFICIARY_DOFBIRTH_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_err_rdsp_beneficiary_dofbirth_missing();
			break;
		case 1702825: /* WARN_RDSP_BENEFICIARY_DOFBIRTH_MISSING */
			conditionObj = new CIFast_IFast_ifastcbo_warn_rdsp_beneficiary_dofbirth_missing();
			break;
		case 1702820: /* ERR_NOT_ELIGIBLE_TARGET_FUND_CASHSWEEP */
			conditionObj = new CIFast_IFast_ifastcbo_err_not_eligible_target_fund_cashsweep();
			break;
		case 1702821: /* ERR_NOT_ELIGIBLE_TARGET_FUND_GIA_MATURITY */
			conditionObj = new CIFast_IFast_ifastcbo_err_not_eligible_target_fund_giamaturity();
			break;
		case 1702822: /* WARN_NOT_ELIGIBLE_TARGET_FUND_CASHSWEEP */
			conditionObj = new CIFast_IFast_ifastcbo_warn_not_eligible_target_fund_cashsweep();
			break;
		case 1702823: /* WARN_NOT_ELIGIBLE_TARGET_FUND_GIA_MATURITY */
			conditionObj = new CIFast_IFast_ifastcbo_warn_not_eligible_target_fund_giamaturity();
			break;
		case 1800001: /* ERR_511_RECORDS_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_511_records_not_allowed();
			break;
		case 1800002: /* ERR_ACC_LASTNAME_POSTALCODE_BLANK */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_acc_lastname_postalcode_blank();
			break;
		case 1800003: /* ERR_ACCESS_DENIED_NO_SESSION_RECORD */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_access_denied_no_session_record();
			break;
		case 1800004: /* ERR_ACCESS_DENIED_PASS_LOGOFF_TIME */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_access_denied_pass_logoff_time();
			break;
		case 1800005: /* ERR_ACCESS_DENIED_PASSWORD_MUST_BE_RESET */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_access_denied_password_must_be_reset();
			break;
		case 1800006: /* ERR_ACCESS_ID_OVERRIDE_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_access_id_override_not_allowed();
			break;
		case 1800007: /* ERR_ACCOUNT_AMS_RECORD_ALREADY_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_account_ams_record_already_exists();
			break;
		case 1800008: /* ERR_ACCOUNT_AMS_RECORD_DOES_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_account_ams_record_does_not_exist();
			break;
		case 1800009: /* ERR_ACCOUNT_ENTITY_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_account_entity_not_found();
			break;
		case 1800010: /* ERR_ACCOUNT_INACTIVE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_account_inactive();
			break;
		case 1800011: /* ERR_ACCOUNT_MAY_ONLY_HAVE_ONE_NOMINEE_OWNER */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_account_may_only_have_one_nominee_owner();
			break;
		case 1800012: /* ERR_ACCOUNT_NUMBER_IS_INVALID */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_account_number_is_invalid();
			break;
		case 1800013: /* ERR_ACCOUNT_NUMBER_MUSTBE_BLANK */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_account_number_mustbe_blank();
			break;
		case 1800014: /* ERR_ACCOUNT_OR_FUNDBROKER_SHOULD_BE_BLANK */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_account_or_fundbroker_should_be_blank();
			break;
		case 1800015: /* ERR_ACCOUNT_REVIEW_DETAIL_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_account_review_detail_not_found();
			break;
		case 1800016: /* ERR_ACCOUNT_REVIEW_RECORD_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_account_review_record_exists();
			break;
		case 1800017: /* ERR_ACCOUNT_SPLITCOMM_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_account_splitcomm_not_found();
			break;
		case 1800018: /* ERR_ACCOUNT_SPLITCOMM_RECORD_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_account_splitcomm_record_exists();
			break;
		case 1800019: /* ERR_ACCOUNTABLE_SHOULD_BLANK_WHEN_DILUTION_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_accountable_should_blank_when_dilution_exists();
			break;
		case 1800020: /* ERR_ACCOUNTENTITY_ALREADY_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_accountentity_already_exists();
			break;
		case 1800021: /* ERR_ACCOUNTENTITY_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_accountentity_not_found();
			break;
		case 1800022: /* ERR_ACCT_BAL_MAY_BE_LESS_MIN */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_acct_bal_may_be_less_min();
			break;
		case 1800023: /* ERR_ACCT_BAL_WILL_BE_LESS_MIN */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_acct_bal_will_be_less_min();
			break;
		case 1800024: /* ERR_ACCT_CAT_REC_DOES_NOT_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_acct_cat_rec_does_not_exists();
			break;
		case 1800025: /* ERR_ACCT_ENTITY_BENEF_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_acct_entity_benef_not_found();
			break;
		case 1800026: /* ERR_ACCT_ENTITY_JOINT_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_acct_entity_joint_not_found();
			break;
		case 1800027: /* ERR_ACCT_FOR_TRANSACTION_NOT_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_acct_for_transaction_not_available();
			break;
		case 1800028: /* ERR_ACCT_LEVEL_IA_RECORD_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_acct_level_ia_record_exists();
			break;
		case 1800029: /* ERR_ACCT_LEVEL_IA_RECORD_INVALID_PAYMENT_TYPE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_acct_level_ia_record_invalid_payment_type();
			break;
		case 1800030: /* ERR_ACCT_LEVEL_IA_RECORD_NOT_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_acct_level_ia_record_not_exists();
			break;
		case 1800031: /* ERR_ACCT_LEVEL_IA_RECORD_VERSION_DIFF */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_acct_level_ia_record_version_diff();
			break;
		case 1800032: /* ERR_ACCT_LVL_CUT_OFF_TIME_ALREADY_EXIT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_acct_lvl_cut_off_time_already_exit();
			break;
		case 1800033: /* ERR_ACCT_LVL_CUT_OFF_TIME_NOT_EXIT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_acct_lvl_cut_off_time_not_exit();
			break;
		case 1800034: /* ERR_ACCT_NOT_ACTIVE_AT_TRADE_DATE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_acct_not_active_at_trade_date();
			break;
		case 1800035: /* ERR_ACCT_NUM_BLANK_FOR_TRANSPENDING */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_acct_num_blank_for_transpending();
			break;
		case 1800036: /* ERR_ACCT_REG_DETAILS_DOES_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_acct_reg_details_does_not_exist();
			break;
		case 1800037: /* ERR_ACCT_UPDATE_FAILED_AS_ACCTENTITY_UPDATE_FAILED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_acct_update_failed_as_acctentity_update_failed();
			break;
		case 1800038: /* ERR_ACCTNBR_MUST_BE_ENTERED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_acctnbr_must_be_entered();
			break;
		case 1800039: /* ERR_ACCTREGDETAILS_NOT_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_acctregdetails_not_available();
			break;
		case 1800040: /* ERR_ACQ_FEE_CALC_DURING_RUN */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_acq_fee_calc_during_run();
			break;
		case 1800041: /* ERR_ACTIVE_CONTRACT_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_active_contract_exists();
			break;
		case 1800042: /* ERR_AD_AFTER_MANDATORY_LOGOFF_TIME */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_ad_after_mandatory_logoff_time();
			break;
		case 1800043: /* ERR_AD_BEFORE_ALLOWABLE_LOGON_TIME */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_ad_before_allowable_logon_time();
			break;
		case 1800044: /* ERR_AD_INVALID_PASSWORD */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_ad_invalid_password();
			break;
		case 1800045: /* ERR_AD_INVALID_PROFILE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_ad_invalid_profile();
			break;
		case 1800046: /* ERR_AD_MAXIMUM_SESSIONS_ALREADY_RUNNING */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_ad_maximum_sessions_already_running();
			break;
		case 1800047: /* ERR_AD_NO_COMPANY_ACCESS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_ad_no_company_access();
			break;
		case 1800048: /* ERR_AD_PAST_PASSWORD_GRACE_PERIOD */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_ad_past_password_grace_period();
			break;
		case 1800049: /* ERR_AD_PROFLE_HAS_NO_ACCESS_TODAY */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_ad_profle_has_no_access_today();
			break;
		case 1800050: /* ERR_AD_SHAREHOLDER_DOES_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_ad_shareholder_does_not_exist();
			break;
		case 1800051: /* ERR_AD_TOO_MANY_FAILED_LOGONS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_ad_too_many_failed_logons();
			break;
		case 1800052: /* ERR_AD_UNKNOWN_ACCESS_PROFILE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_ad_unknown_access_profile();
			break;
		case 1800053: /* ERR_AD_UNKNOWN_USER */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_ad_unknown_user();
			break;
		case 1800054: /* ERR_AD_USER_ACCOUNT_NOT_ACTIVE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_ad_user_account_not_active();
			break;
		case 1800055: /* ERR_AD_USER_HAS_NO_COMPANY_ACCESS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_ad_user_has_no_company_access();
			break;
		case 1800056: /* ERR_ADDR_CODE_EXISTS_FOR_ENTITY */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_addr_code_exists_for_entity();
			break;
		case 1800057: /* ERR_ADDRESS_CODE_AT_LEAST_TWO */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_address_code_at_least_two();
			break;
		case 1800058: /* ERR_ADDRESS_USED_FOR_MAILING */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_address_used_for_mailing();
			break;
		case 1800059: /* ERR_ADDRID_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_addrid_not_found();
			break;
		case 1800060: /* ERR_AGGREGATE_ORDER_DOES_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_aggregate_order_does_not_exist();
			break;
		case 1800061: /* ERR_AGGREGATE_ORDER_LOSS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_aggregate_order_loss();
			break;
		case 1800062: /* ERR_AGGREGATION_REF_NUMBER_BLANK */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_aggregation_ref_number_blank();
			break;
		case 1800063: /* ERR_ALL_REQUEST_FIELDS_BLANK */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_all_request_fields_blank();
			break;
		case 1800064: /* ERR_ALLFUNDS_OR_FUND_CLASSCODE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_allfunds_or_fund_classcode();
			break;
		case 1800065: /* ERR_ALLOCATION_EXISTS_FOR_FUND_CLASS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_allocation_exists_for_fund_class();
			break;
		case 1800066: /* ERR_AMOUNT_CANNOT_BE_GREATER_AMOUNT_TYPE_P */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_amount_cannot_be_greater_amount_type_p();
			break;
		case 1800067: /* ERR_AMOUNT_DONOT_CROSSFOOT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_amount_donot_crossfoot();
			break;
		case 1800068: /* ERR_AMOUNT_EXCEEDS_VARIANCE_LIMIT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_amount_exceeds_variance_limit();
			break;
		case 1800069: /* ERR_AMOUNT_GREATER */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_amount_greater();
			break;
		case 1800070: /* ERR_AMOUNT_MUST_BE_ZERO_FOR_AMOUNTTYPE_T */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_amount_must_be_zero_for_amounttype_t();
			break;
		case 1800071: /* ERR_AMOUNT_SHOULD_MANDATORY */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_amount_should_mandatory();
			break;
		case 1800072: /* ERR_AMS_ACTIVE_CERTS_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_ams_active_certs_exist();
			break;
		case 1800073: /* ERR_AMS_CODE_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_ams_code_not_found();
			break;
		case 1800074: /* ERR_AMS_CODE_NOT_VALID */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_ams_code_not_valid();
			break;
		case 1800075: /* ERR_AMS_RULES_REC_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_ams_rules_rec_exists();
			break;
		case 1800076: /* ERR_AMSCODE_ALREADY_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_amscode_already_exists();
			break;
		case 1800077: /* ERR_AMT_EXCEED_VARIANCE_AGGRORD */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_amt_exceed_variance_aggrord();
			break;
		case 1800078: /* ERR_AMT_EXCEEDS_THRESHOLD_TRADE_LIMIT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_amt_exceeds_threshold_trade_limit();
			break;
		case 1800079: /* ERR_AMT_IS_LESS_FUND_PURC_MIN */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_amt_is_less_fund_purc_min();
			break;
		case 1800080: /* ERR_AMT_IS_LESS_THAN_MIN_SUBSEQ_REDEMP */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_amt_is_less_than_min_subseq_redemp();
			break;
		case 1800081: /* ERR_AMT_LESS_THAN_MIN_INIT_REDEMP */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_amt_less_than_min_init_redemp();
			break;
		case 1800082: /* ERR_AMT_MAY_LESS_FUND_PURC_MIN */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_amt_may_less_fund_purc_min();
			break;
		case 1800083: /* ERR_AMT_MAY_LESS_THAN_MIN_INIT_REDEMP */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_amt_may_less_than_min_init_redemp();
			break;
		case 1800084: /* ERR_AMT_MAY_LESS_THAN_MIN_SUBSEQ_REDEMP */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_amt_may_less_than_min_subseq_redemp();
			break;
		case 1800085: /* ERR_ANNUIT_AGE_GREATER_THAN_MIN */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_annuit_age_greater_than_min();
			break;
		case 1800086: /* ERR_APARTMENT_NUM_MISSING */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_apartment_num_missing();
			break;
		case 1800087: /* ERR_AS_OF_DATE_WAS_NOT_ENTERED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_as_of_date_was_not_entered();
			break;
		case 1800088: /* ERR_ASSIGN_INFO_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_assign_info_not_found();
			break;
		case 1800089: /* ERR_ASSIGNED_FLAG_ENABLED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_assigned_flag_enabled();
			break;
		case 1800090: /* ERR_AUTH_CHPWD_REQD */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_auth_chpwd_reqd();
			break;
		case 1800091: /* ERR_AUTH_INACTIVE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_auth_inactive();
			break;
		case 1800092: /* ERR_AUTH_LOCKED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_auth_locked();
			break;
		case 1800093: /* ERR_AUTH_MAX_LOGONS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_auth_max_logons();
			break;
		case 1800094: /* ERR_AUTH_TOKEN_EXP */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_auth_token_exp();
			break;
		case 1800095: /* ERR_BANK_ACC_EXCEEDS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_bank_acc_exceeds();
			break;
		case 1800096: /* ERR_BANK_ACC_MUST_BE_ENTERED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_bank_acc_must_be_entered();
			break;
		case 1800097: /* ERR_BANK_ACC_NUMERIC */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_bank_acc_numeric();
			break;
		case 1800098: /* ERR_BANK_INFO_IS_MANDATORY_FOR_EFT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_bank_info_is_mandatory_for_eft();
			break;
		case 1800099: /* ERR_BANK_MASTER_DEL_ON_DATE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_bank_master_del_on_date();
			break;
		case 1800100: /* ERR_BANK_MASTER_REC_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_bank_master_rec_exists();
			break;
		case 1800101: /* ERR_BANK_RECORD_SHOULD */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_bank_record_should();
			break;
		case 1800102: /* ERR_BANKACCT_LOCKED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_bankacct_locked();
			break;
		case 1800103: /* ERR_BANKACCT_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_bankacct_not_found();
			break;
		case 1800104: /* ERR_BANKACCT_VERSION_DIFFERENT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_bankacct_version_different();
			break;
		case 1800105: /* ERR_BANKMST_UNAVAILABLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_bankmst_unavailable();
			break;
		case 1800106: /* ERR_BANKTYPE_IDNUM_NOT_ENTERED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_banktype_idnum_not_entered();
			break;
		case 1800107: /* ERR_BATCH_CANNOT_BE_BLANK */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_batch_cannot_be_blank();
			break;
		case 1800108: /* ERR_BATCH_DOES_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_batch_does_not_exist();
			break;
		case 1800109: /* ERR_BATCH_IS_ACTIVE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_batch_is_active();
			break;
		case 1800110: /* ERR_BATCH_IS_LOCKED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_batch_is_locked();
			break;
		case 1800111: /* ERR_BATCH_NOT_ACTIVE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_batch_not_active();
			break;
		case 1800112: /* ERR_BATCHES_NOT_MATCH */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_batches_not_match();
			break;
		case 1800113: /* ERR_BATCHNAME_CANNOT_BLANK */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_batchname_cannot_blank();
			break;
		case 1800114: /* ERR_BATCHNAME_SHOULD_BLANK */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_batchname_should_blank();
			break;
		case 1800115: /* ERR_BATCHTRACE_REC_NOTFOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_batchtrace_rec_notfound();
			break;
		case 1800116: /* ERR_BATCHTYPE_INVALID */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_batchtype_invalid();
			break;
		case 1800117: /* ERR_BONIMAX_VALUE_LESS_THAN_ZERO */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_bonimax_value_less_than_zero();
			break;
		case 1800118: /* ERR_BOX_NUM_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_box_num_not_found();
			break;
		case 1800119: /* ERR_BRK_EPA_STATUS_NOT_ACTIVE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_brk_epa_status_not_active();
			break;
		case 1800120: /* ERR_BROKER_AMS_ALREADY_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_broker_ams_already_exists();
			break;
		case 1800121: /* ERR_BROKER_AMS_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_broker_ams_not_exist();
			break;
		case 1800122: /* ERR_BROKER_AMS_USED_BY_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_broker_ams_used_by_account();
			break;
		case 1800123: /* ERR_BROKER_BRANCH_NOT_ENTERED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_broker_branch_not_entered();
			break;
		case 1800124: /* ERR_BROKER_BRANCH_SLSREP_NOT_ENTERED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_broker_branch_slsrep_not_entered();
			break;
		case 1800125: /* ERR_BROKER_CAN_NOT_BLANK */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_broker_can_not_blank();
			break;
		case 1800126: /* ERR_BROKER_IS_NOT_PERMIT_MONEY_MKT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_broker_is_not_permit_money_mkt();
			break;
		case 1800127: /* ERR_BROKER_NOT_ELIGIBLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_broker_not_eligible();
			break;
		case 1800128: /* ERR_BROKER_NOT_ELIGIBLE_WRAP */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_broker_not_eligible_wrap();
			break;
		case 1800129: /* ERR_BROKER_NOT_ENTERED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_broker_not_entered();
			break;
		case 1800130: /* ERR_BROKER_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_broker_not_found();
			break;
		case 1800131: /* ERR_BROKER_SLSREP_NOT_ENTERED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_broker_slsrep_not_entered();
			break;
		case 1800132: /* ERR_BROKERCODE_AND_SRCHALTACCOUNT_MUST_BE_PROVIDED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_brokercode_and_srchaltaccount_must_be_provided();
			break;
		case 1800133: /* ERR_BULK_CANC_NO_TXN_TO_CANCEL */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_bulk_canc_no_txn_to_cancel();
			break;
		case 1800134: /* ERR_BULK_CANC_NO_TXN_TO_REBOOK */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_bulk_canc_no_txn_to_rebook();
			break;
		case 1800135: /* ERR_CALCULATING_DIVIDENTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_calculating_dividents();
			break;
		case 1800136: /* ERR_CALCULATING_MANAGEMENT_FEE_ACCRUALS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_calculating_management_fee_accruals();
			break;
		case 1800137: /* ERR_CAN_ONLY_DELETE_ON_THE_DATE_RECORD_IS_CREATED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_can_only_delete_on_the_date_record_is_created();
			break;
		case 1800138: /* ERR_CANC_NOT_ALLOWED_ACTIVE_CYCLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_canc_not_allowed_active_cycle();
			break;
		case 1800139: /* ERR_CANCEL_DOES_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_cancel_does_not_exist();
			break;
		case 1800140: /* ERR_CANCEL_FAILED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_cancel_failed();
			break;
		case 1800141: /* ERR_CANCEL_GUAR_ADJ_EXIST_FOR_ACCT_CONTRACT_AFTR_TRADE_DATE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_cancel_guar_adj_exist_for_acct_contract_aftr_trade_date();
			break;
		case 1800142: /* ERR_CANCEL_INSTR_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_cancel_instr_exists();
			break;
		case 1800143: /* ERR_CANCEL_MONEY_OUT_TXNS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_cancel_money_out_txns();
			break;
		case 1800144: /* ERR_CANCELLATION_CALC_EUSD_FAILED_ACCTIVE_OWNER_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_cancellation_calc_eusd_failed_acctive_owner_not_found();
			break;
		case 1800145: /* ERR_CANCELLATION_CALC_EUSD_FAILED_CURRENCY_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_cancellation_calc_eusd_failed_currency_not_found();
			break;
		case 1800146: /* ERR_CANCELLATION_CALC_EUSD_FAILED_ENTITY_IDENTITY_PAYING_AGENT_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_cancellation_calc_eusd_failed_entity_identity_paying_agent_not_found();
			break;
		case 1800147: /* ERR_CANCELLATION_CALC_EUSD_FAILED_FUND_INFO_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_cancellation_calc_eusd_failed_fund_info_not_found();
			break;
		case 1800148: /* ERR_CANCELLATION_CALC_EUSD_FAILED_PAYING_AGENT_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_cancellation_calc_eusd_failed_paying_agent_not_found();
			break;
		case 1800149: /* ERR_CANCELLATION_CALC_EUSD_FAILED_PRICE_DISTRIB_RATE_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_cancellation_calc_eusd_failed_price_distrib_rate_not_found();
			break;
		case 1800150: /* ERR_CANCELLATION_CALC_EUSD_FAILED_TAX_HIST_OWNER_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_cancellation_calc_eusd_failed_tax_hist_owner_not_found();
			break;
		case 1800151: /* ERR_CANCELLATION_CALC_EUSD_FAILED_TAX_HIST_PAYING_AGENT_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_cancellation_calc_eusd_failed_tax_hist_paying_agent_not_found();
			break;
		case 1800152: /* ERR_CANCELLATION_DEPOSIT_DTE_BLNK_FOR_LSIF_FND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_cancellation_deposit_dte_blnk_for_lsif_fnd();
			break;
		case 1800153: /* ERR_CANCELLATION_FAILED_TO_CANCEL_ASSOC_UNSTTL_CASH_ID */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_cancellation_failed_to_cancel_assoc_unsttl_cash_id();
			break;
		case 1800154: /* ERR_CANCELLATION_LOCK_ACCT_VAL_TO_RESET_ACB_SUPPRESS_FLAG_FAILED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_cancellation_lock_acct_val_to_reset_acb_suppress_flag_failed();
			break;
		case 1800155: /* ERR_CANCELLATION_UNDONE_BY_ERROR_OR_ENDKEY */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_cancellation_undone_by_error_or_endkey();
			break;
		case 1800156: /* ERR_CANNOT_CALCULATE_EUSD */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_cannot_calculate_eusd();
			break;
		case 1800157: /* ERR_CANNOT_DELETE_ACCOWNER */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_cannot_delete_accowner();
			break;
		case 1800158: /* ERR_CANNOT_DELETE_AMS_CODE_IN_USE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_cannot_delete_ams_code_in_use();
			break;
		case 1800159: /* ERR_CANNOT_DELETE_AMSCODE_IN_MSTR */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_cannot_delete_amscode_in_mstr();
			break;
		case 1800160: /* ERR_CANNOT_DELETE_CONTRACT_ACCOUNT_ACTIVITY */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_cannot_delete_contract_account_activity();
			break;
		case 1800161: /* ERR_CANNOT_DELETE_FEEMODEL_CODE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_cannot_delete_feemodel_code();
			break;
		case 1800162: /* ERR_CANNOT_FIND_TIME_ZONE_INFORMATION */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_cannot_find_time_zone_information();
			break;
		case 1800163: /* ERR_CANNOT_LOCATE_PAC_INDEX_REC */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_cannot_locate_pac_index_rec();
			break;
		case 1800164: /* ERR_CANNOT_LOCATE_SCHED_JOB */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_cannot_locate_sched_job();
			break;
		case 1800165: /* ERR_CANNOT_MODIFY_A_BAD_REC */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_cannot_modify_a_bad_rec();
			break;
		case 1800166: /* ERR_CANNOT_PRINT_DUPLICATE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_cannot_print_duplicate();
			break;
		case 1800167: /* ERR_CANNOT_RESOLVE_FTP_FROM_NAME */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_cannot_resolve_ftp_from_name();
			break;
		case 1800168: /* ERR_CANNOT_RESOLVE_HOST_FROM_NAME */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_cannot_resolve_host_from_name();
			break;
		case 1800169: /* ERR_CAT_TYPE_EXISTS_FOR_ACCT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_cat_type_exists_for_acct();
			break;
		case 1800170: /* ERR_CD_POLICY_IMPACT_DOB */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_cd_policy_impact_dob();
			break;
		case 1800171: /* ERR_CHEQUE_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_cheque_not_found();
			break;
		case 1800172: /* ERR_CHQ_DETL_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_chq_detl_not_found();
			break;
		case 1800173: /* ERR_CLAN_PLAN_NOT_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_clan_plan_not_available();
			break;
		case 1800174: /* ERR_CLEARINGSETTLEINSTR_ALREADY_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_clearingsettleinstr_already_exists();
			break;
		case 1800175: /* ERR_CLEARINGSETTLEINSTR_DATA_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_clearingsettleinstr_data_not_found();
			break;
		case 1800176: /* ERR_CLIENT_ACCOUNT_CANNOT_HAVE_A_NOMINEE_OWNER */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_client_account_cannot_have_a_nominee_owner();
			break;
		case 1800177: /* ERR_CLINET_RECORD_ALREADY_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_clinet_record_already_exists();
			break;
		case 1800178: /* ERR_CLOSEACCTCODE_NOT_FUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_closeacctcode_not_fund();
			break;
		case 1800179: /* ERR_CODE_USED_BY_FUNDSPONSOR_CANNOT_DELETE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_code_used_by_fundsponsor_cannot_delete();
			break;
		case 1800180: /* ERR_COMM_ENTITY_DOES_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_comm_entity_does_not_exist();
			break;
		case 1800181: /* ERR_COMMISION_EXCEED_FUND_DEFAULT_RATE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_commision_exceed_fund_default_rate();
			break;
		case 1800182: /* ERR_CONFLICT_ADDRESS_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_conflict_address_exist();
			break;
		case 1800183: /* ERR_CONNECTING_TO_FTP */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_connecting_to_ftp();
			break;
		case 1800184: /* ERR_CONTRACT_ACCT_NOT_ACTIVE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_contract_acct_not_active();
			break;
		case 1800185: /* ERR_CONTRACT_ACCT_STATUS_ACTIVE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_contract_acct_status_active();
			break;
		case 1800186: /* ERR_CONTRACT_ACCT_STATUS_DEATH */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_contract_acct_status_death();
			break;
		case 1800187: /* ERR_CONTRACT_CLOSED_FOR_NEW_BUSINESS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_contract_closed_for_new_business();
			break;
		case 1800188: /* ERR_CONTRACT_EXIST_BUT_NOT_EFFECTIVE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_contract_exist_but_not_effective();
			break;
		case 1800189: /* ERR_CONTRACT_MATURITY_DATE_GREATER_THAN_LEGAL */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_contract_maturity_date_greater_than_legal();
			break;
		case 1800190: /* ERR_CONTRACT_RECORD_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_contract_record_not_found();
			break;
		case 1800191: /* ERR_CONTRACT_TYPE_MUST_BE_ENTERED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_contract_type_must_be_entered();
			break;
		case 1800192: /* ERR_CONTROLS_NAME_RECORD_ENTITYID_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_controls_name_record_entityid_not_found();
			break;
		case 1800193: /* ERR_COULD_NOT_CREATE_THE_SHAREHOLDER_REMARKS_RECORD */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_could_not_create_the_shareholder_remarks_record();
			break;
		case 1800194: /* ERR_COUNTRY_REQUIRED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_country_required();
			break;
		case 1800195: /* ERR_CURRENCY_NOT_ALLOWED_TAX_TYPE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_currency_not_allowed_tax_type();
			break;
		case 1800196: /* ERR_CURRENCY_NOT_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_currency_not_available();
			break;
		case 1800197: /* ERR_CYCLE_RUN_UNAVAILABLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_cycle_run_unavailable();
			break;
		case 1800198: /* ERR_CYCLE_RUNNING */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_cycle_running();
			break;
		case 1800199: /* ERR_DAILY_FEE_RECORD_ALREADY_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_daily_fee_record_already_exists();
			break;
		case 1800200: /* ERR_DAILY_FEE_RECORD_DOES_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_daily_fee_record_does_not_exist();
			break;
		case 1800201: /* ERR_DATA_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_data_not_found();
			break;
		case 1800202: /* ERR_DATA_PROBLEM_MISSING_PRICE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_data_problem_missing_price();
			break;
		case 1800203: /* ERR_DATABASE_NOT_CONNECTED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_database_not_connected();
			break;
		case 1800204: /* ERR_DATABASE_UNAVAILABLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_database_unavailable();
			break;
		case 1800205: /* ERR_DATE_OF_BIRTH_MANDATORY */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_date_of_birth_mandatory();
			break;
		case 1800206: /* ERR_DBKR_BATCH_BELONGS_TO_OTHERUSER */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_dbkr_batch_belongs_to_otheruser();
			break;
		case 1800207: /* ERR_DEALER_CANNOT_SETTLE_INTERM */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_dealer_cannot_settle_interm();
			break;
		case 1800208: /* ERR_DEALER_FUNDS_NA */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_dealer_funds_na();
			break;
		case 1800209: /* ERR_DEALER_NOT_AUTH_TO_DEAL_FUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_dealer_not_auth_to_deal_fund();
			break;
		case 1800210: /* ERR_DEFAULT_FUNDBROKER_ALREADY_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_default_fundbroker_already_exists();
			break;
		case 1800211: /* ERR_DELIVERY_METHOD_EXISTS_FOR_DOC_TYPE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_delivery_method_exists_for_doc_type();
			break;
		case 1800212: /* ERR_DILUTION_DOES_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_dilution_does_not_exist();
			break;
		case 1800213: /* ERR_DILUTION_RECORD_IS_NOT_AVAIL */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_dilution_record_is_not_avail();
			break;
		case 1800214: /* ERR_DILUTION_RECORDS_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_dilution_records_exists();
			break;
		case 1800215: /* ERR_DILUTION_RECORDS_LOCKED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_dilution_records_locked();
			break;
		case 1800216: /* ERR_DISTRIB_NA */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_distrib_na();
			break;
		case 1800217: /* ERR_DISTRIB_TO_CASH_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_distrib_to_cash_not_allowed();
			break;
		case 1800218: /* ERR_DISTRIBANK_IS_LOCKED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_distribank_is_locked();
			break;
		case 1800219: /* ERR_DISTRIBANK_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_distribank_not_found();
			break;
		case 1800220: /* ERR_DISTRIBUTION_IS_LOCKED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_distribution_is_locked();
			break;
		case 1800221: /* ERR_DISTRIBUTION_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_distribution_not_found();
			break;
		case 1800222: /* ERR_DM_EVENT_SINCE_ORGI_TRADEDATE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_dm_event_since_orgi_tradedate();
			break;
		case 1800223: /* ERR_DOB_IMPACT_MATUR_POLICY */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_dob_impact_matur_policy();
			break;
		case 1800224: /* ERR_DP_RD_NOT_ALLOW_TRANSER */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_dp_rd_not_allow_transer();
			break;
		case 1800225: /* ERR_DSC_REC_EXISTS_THIS_FAMILY_NO_DELETE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_dsc_rec_exists_this_family_no_delete();
			break;
		case 1800226: /* ERR_DTA_REC_DOES_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_dta_rec_does_not_exist();
			break;
		case 1800227: /* ERR_DTA_REC_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_dta_rec_exists();
			break;
		case 1800228: /* ERR_DUPLICATE_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_duplicate_account();
			break;
		case 1800229: /* ERR_DUPLICATE_AUTO_TRANSFER */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_duplicate_auto_transfer();
			break;
		case 1800230: /* ERR_DUPLICATE_CONTRACT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_duplicate_contract();
			break;
		case 1800231: /* ERR_DUPLICATE_DISTRIBUTION */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_duplicate_distribution();
			break;
		case 1800232: /* ERR_DUPLICATE_PARENT_FUND_CLASS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_duplicate_parent_fund_class();
			break;
		case 1800233: /* ERR_EFFECTIVE_DATE_PRIOR_TO_LAST_RUN */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_effective_date_prior_to_last_run();
			break;
		case 1800234: /* ERR_EFFECTIVEDATE_MUST_BE_ENTERED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_effectivedate_must_be_entered();
			break;
		case 1800235: /* ERR_EFT_PAYMENT_DETAILS_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_eft_payment_details_not_found();
			break;
		case 1800236: /* ERR_EMPTY_REG_AGENT_CODE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_empty_reg_agent_code();
			break;
		case 1800237: /* ERR_ENT_REG_DUP_ID_REG */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_ent_reg_dup_id_reg();
			break;
		case 1800238: /* ERR_ENT_REG_JUR_DUP_TAX */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_ent_reg_jur_dup_tax();
			break;
		case 1800239: /* ERR_ENT_REG_JUR_LOCKED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_ent_reg_jur_locked();
			break;
		case 1800240: /* ERR_ENT_REG_JUR_NOT_AVAIL */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_ent_reg_jur_not_avail();
			break;
		case 1800241: /* ERR_ENT_REG_JUR_VER_DIFF */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_ent_reg_jur_ver_diff();
			break;
		case 1800242: /* ERR_ENT_REG_LOCKED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_ent_reg_locked();
			break;
		case 1800243: /* ERR_ENT_REG_NOT_AVAIL */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_ent_reg_not_avail();
			break;
		case 1800244: /* ERR_ENT_REG_VER_DIFF */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_ent_reg_ver_diff();
			break;
		case 1800245: /* ERR_ENTER_A_VALID_SUPPRESS_CODE_FOR_PAYTYPE_X_OR_BLANK_FOR_S */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_enter_a_valid_suppress_code_for_paytype_x_or_blank_for_s();
			break;
		case 1800246: /* ERR_ENTITY_ADDR_NA */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_entity_addr_na();
			break;
		case 1800247: /* ERR_ENTITY_ADDR_XREF_NA */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_entity_addr_xref_na();
			break;
		case 1800248: /* ERR_ENTITY_NOT_ASSOCIATED_WITH_AN_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_entity_not_associated_with_an_account();
			break;
		case 1800249: /* ERR_ENTITY_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_entity_not_found();
			break;
		case 1800250: /* ERR_ENTITY_WHEREUSE_ALREADY_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_entity_whereuse_already_exist();
			break;
		case 1800251: /* ERR_ENTITYTYPE_MUST_POPULATED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_entitytype_must_populated();
			break;
		case 1800252: /* ERR_ENTITYWHEREUSE_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_entitywhereuse_exists();
			break;
		case 1800253: /* ERR_ENTITYWHEREUSE_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_entitywhereuse_not_found();
			break;
		case 1800254: /* ERR_EQ_TRADE_CANCEL */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_eq_trade_cancel();
			break;
		case 1800255: /* ERR_ERROR_UPD_BANK_TABLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_error_upd_bank_table();
			break;
		case 1800256: /* ERR_ESOP_MUST_CLOSE_ACCT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_esop_must_close_acct();
			break;
		case 1800257: /* ERR_ESTATE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_estate();
			break;
		case 1800258: /* ERR_EUSD_OVERRIDE_DOES_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_eusd_override_does_not_exist();
			break;
		case 1800259: /* ERR_EXCEED_USER_SETUP_AMT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_exceed_user_setup_amt();
			break;
		case 1800260: /* ERR_EXCH_RATE_DOES_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_exch_rate_does_not_exist();
			break;
		case 1800261: /* ERR_EXCH_RATE_NOT_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_exch_rate_not_available();
			break;
		case 1800262: /* ERR_EXCHANGE_RATE_NOT_AVAIL */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_exchange_rate_not_avail();
			break;
		case 1800263: /* ERR_EXCHANGE_RATE_TAX_CALC_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_exchange_rate_tax_calc_not_found();
			break;
		case 1800264: /* ERR_EXIST_AS_BAD */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_exist_as_bad();
			break;
		case 1800265: /* ERR_EXT_TRANSFER_ACCT_DETL_NON_EXISTANT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_ext_transfer_acct_detl_non_existant();
			break;
		case 1800266: /* ERR_EXT_TRANSFER_ACCT_REC_NON_EXISTANT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_ext_transfer_acct_rec_non_existant();
			break;
		case 1800267: /* ERR_FAMILY_RECORD_NOT_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_family_record_not_exists();
			break;
		case 1800268: /* ERR_FEE_ENTERED_WITHOUT_OVERRIDE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_fee_entered_without_override();
			break;
		case 1800269: /* ERR_FEE_MODEL_CODE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_fee_model_code();
			break;
		case 1800270: /* ERR_FEE_MODEL_RECORD_WITH_SAME_FEE_MODEL_CODE_IS_ALREADY_DELETED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_fee_model_record_with_same_fee_model_code_is_already_deleted();
			break;
		case 1800271: /* ERR_FEE_OVERRIDE_NO_FEE_DEFINED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_fee_override_no_fee_defined();
			break;
		case 1800272: /* ERR_FEE_PARAMETER_ALREADY_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_fee_parameter_already_exists();
			break;
		case 1800273: /* ERR_FEE_PARAMS_NOT_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_fee_params_not_available();
			break;
		case 1800274: /* ERR_FEE_RECORD_NA */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_fee_record_na();
			break;
		case 1800275: /* ERR_FEEMODEL_ALREADY_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_feemodel_already_exists();
			break;
		case 1800276: /* ERR_FEEMODEL_DOES_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_feemodel_does_not_exist();
			break;
		case 1800277: /* ERR_FEEMODEL_LOCKED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_feemodel_locked();
			break;
		case 1800278: /* ERR_FEEMODELCODE_INUSE_CANNOT_DELETE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_feemodelcode_inuse_cannot_delete();
			break;
		case 1800279: /* ERR_FEES_WAIVED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_fees_waived();
			break;
		case 1800280: /* ERR_FIFO_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_fifo_not_exist();
			break;
		case 1800281: /* ERR_FINANCIAL_TIMEZONE_INVALID */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_financial_timezone_invalid();
			break;
		case 1800282: /* ERR_FNDSPONSOR_FEEMODEL_ALREADY_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_fndsponsor_feemodel_already_exists();
			break;
		case 1800283: /* ERR_FNDSPONSOR_FEEMODEL_DOES_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_fndsponsor_feemodel_does_not_exist();
			break;
		case 1800284: /* ERR_FNDSPONSOR_FEEMODEL_LOCKED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_fndsponsor_feemodel_locked();
			break;
		case 1800285: /* ERR_FNDSPONSOR_FEEMODEL_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_fndsponsor_feemodel_not_found();
			break;
		case 1800286: /* ERR_FROM_CLEARING_METHOD_CCY_ONLY_FOR_SAME_SETTLE_CURR_FUND_CURR */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_from_clearing_method_ccy_only_for_same_settle_curr_fund_curr();
			break;
		case 1800287: /* ERR_FROM_TO_DATE_MUST_ENTERED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_from_to_date_must_entered();
			break;
		case 1800288: /* ERR_FTP_FILE_READ_FAILED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_ftp_file_read_failed();
			break;
		case 1800289: /* ERR_FULL_REDEMP_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_full_redemp_not_allowed();
			break;
		case 1800290: /* ERR_FULL_REDEMPTION_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_full_redemption_not_allowed();
			break;
		case 1800291: /* ERR_FUND_BROKER_ALREADY_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_fund_broker_already_exist();
			break;
		case 1800292: /* ERR_FUND_BROKER_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_fund_broker_not_exist();
			break;
		case 1800293: /* ERR_FUND_BROKER_WHERE_USE_RECORD_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_fund_broker_where_use_record_not_exist();
			break;
		case 1800294: /* ERR_FUND_CLASS_NOT_AVAILABLE_FOR_PURCHASE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_fund_class_not_available_for_purchase();
			break;
		case 1800295: /* ERR_FUND_CLASS_USED_IN_ACTIVE_CONTRACT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_fund_class_used_in_active_contract();
			break;
		case 1800296: /* ERR_FUND_DEALER_ELIG_DATA_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_fund_dealer_elig_data_not_found();
			break;
		case 1800297: /* ERR_FUND_DETL_DATA_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_fund_detl_data_not_found();
			break;
		case 1800298: /* ERR_FUND_DETL_REC_IS_LOCKED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_fund_detl_rec_is_locked();
			break;
		case 1800299: /* ERR_FUND_INFO_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_fund_info_not_found();
			break;
		case 1800300: /* ERR_FUND_IS_NOT_ESOP_ELIGIBLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_fund_is_not_esop_eligible();
			break;
		case 1800301: /* ERR_FUND_NON_EXISTANT_UNDER_TYPEVAL */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_fund_non_existant_under_typeval();
			break;
		case 1800302: /* ERR_FUND_NOT_ELIGIBLE_FOR_COMMISSION */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_fund_not_eligible_for_commission();
			break;
		case 1800303: /* ERR_FUND_RECORD_NA */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_fund_record_na();
			break;
		case 1800304: /* ERR_FUND_RUNMODE_NOT_VALID */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_fund_runmode_not_valid();
			break;
		case 1800305: /* ERR_FUND_SPONSOR_REQUIRED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_fund_sponsor_required();
			break;
		case 1800306: /* ERR_FUNDCLASS_BAL_LESS_THAN_MIN */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_fundclass_bal_less_than_min();
			break;
		case 1800307: /* ERR_FUNDCLASS_BAL_MAY_LESS_THAN_MIN */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_fundclass_bal_may_less_than_min();
			break;
		case 1800308: /* ERR_FUNDCODE_CANNOT_BE_BLANK_BANK_ENTITY */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_fundcode_cannot_be_blank_bank_entity();
			break;
		case 1800309: /* ERR_FUNDIDTYPE_FUNDIDVALUE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_fundidtype_fundidvalue();
			break;
		case 1800310: /* ERR_FUNDTO_CLASSTO_CANNOT_BLANK_FOR_TRANSFERS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_fundto_classto_cannot_blank_for_transfers();
			break;
		case 1800311: /* ERR_GEN_CTRL_TRADE_DEFLT_DOES_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_gen_ctrl_trade_deflt_does_not_exist();
			break;
		case 1800312: /* ERR_GRNTE_MATURED_PER_CNTRCT_TERM */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_grnte_matured_per_cntrct_term();
			break;
		case 1800313: /* ERR_GROUP_REDEMP_STOP_FLAG_ENABLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_group_redemp_stop_flag_enable();
			break;
		case 1800314: /* ERR_GUARANTEE_ADJUST_NEED_CANCELLATION */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_guarantee_adjust_need_cancellation();
			break;
		case 1800315: /* ERR_GUARANTEE_ADJUSTMENT_MADE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_guarantee_adjustment_made();
			break;
		case 1800316: /* ERR_HOLDING_COMPANY_CODE_IS_ALREADY_DELETED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_holding_company_code_is_already_deleted();
			break;
		case 1800317: /* ERR_HOLDING_ENTITY_CODE_ALREADY_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_holding_entity_code_already_exists();
			break;
		case 1800318: /* ERR_HOLDING_ENTITY_CODE_BAD_RECORD_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_holding_entity_code_bad_record_exists();
			break;
		case 1800319: /* ERR_HOLDING_ENTITY_RECORD_DOES_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_holding_entity_record_does_not_exist();
			break;
		case 1800320: /* ERR_IDENTIFICATION_RECORD_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_identification_record_not_exist();
			break;
		case 1800321: /* ERR_IDENTIFYING */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_identifying();
			break;
		case 1800322: /* ERR_INCREASE_NOT_ALLOWED_MISSED_PACS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_increase_not_allowed_missed_pacs();
			break;
		case 1800323: /* ERR_INDEX_CODE_CANNOT_BE_BLANK */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_index_code_cannot_be_blank();
			break;
		case 1800324: /* ERR_INDEX_CODE_MUST_BE_ENTERED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_index_code_must_be_entered();
			break;
		case 1800325: /* ERR_INPUT_ACCOUNT_IS_NOT_RESP */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_input_account_is_not_resp();
			break;
		case 1800326: /* ERR_INPUT_ACCOUNT_IS_NOT_RIF */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_input_account_is_not_rif();
			break;
		case 1800327: /* ERR_INST_CODE_EXCEEDS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_inst_code_exceeds();
			break;
		case 1800328: /* ERR_INSTRUCTION_ALREADY_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_instruction_already_exists();
			break;
		case 1800329: /* ERR_INSUF_FUND_AT_TRADE_DATE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_insuf_fund_at_trade_date();
			break;
		case 1800330: /* ERR_INSUFFICIENT_INFO */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_insufficient_info();
			break;
		case 1800331: /* ERR_INSUFFICIENT_NOTIONAL_BALANCE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_insufficient_notional_balance();
			break;
		case 1800332: /* ERR_INTERDETL_RECORD_LOCKED_TRY_AGAIN_LATER */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_interdetl_record_locked_try_again_later();
			break;
		case 1800333: /* ERR_INTERM_IS_NOT_PERMIT_WIRE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_interm_is_not_permit_wire();
			break;
		case 1800334: /* ERR_INTERMEDIARY_ENTITY_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_intermediary_entity_not_found();
			break;
		case 1800335: /* ERR_INTERMEDIARY_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_intermediary_not_found();
			break;
		case 1800336: /* ERR_INTINVEST_LOCKED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_intinvest_locked();
			break;
		case 1800337: /* ERR_INTINVEST_NOT_AVAIL */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_intinvest_not_avail();
			break;
		case 1800338: /* ERR_INTINVEST_VERSION_DIFFERENT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_intinvest_version_different();
			break;
		case 1800339: /* ERR_INVALID_ACCESS_ID */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_access_id();
			break;
		case 1800340: /* ERR_INVALID_ACCRUAL_TYPE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_accrual_type();
			break;
		case 1800341: /* ERR_INVALID_ACTIVITY_ID */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_activity_id();
			break;
		case 1800342: /* ERR_INVALID_ADDRESS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_address();
			break;
		case 1800343: /* ERR_INVALID_ADJUST_TYPE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_adjust_type();
			break;
		case 1800344: /* ERR_INVALID_AMOUNT_TYPE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_amount_type();
			break;
		case 1800345: /* ERR_INVALID_ASSOCIATED_ACCNUM */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_associated_accnum();
			break;
		case 1800346: /* ERR_INVALID_BANKTYPE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_banktype();
			break;
		case 1800347: /* ERR_INVALID_BAYCOM */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_baycom();
			break;
		case 1800348: /* ERR_INVALID_BILL_TO_ENTITY */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_bill_to_entity();
			break;
		case 1800349: /* ERR_INVALID_BILL_TO_ENTITY_TYPE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_bill_to_entity_type();
			break;
		case 1800350: /* ERR_INVALID_BROKER_CODE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_broker_code();
			break;
		case 1800351: /* ERR_INVALID_CALL_TYPE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_call_type();
			break;
		case 1800352: /* ERR_INVALID_CALLNUM */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_callnum();
			break;
		case 1800353: /* ERR_INVALID_CALLTYPE_TRADETYPE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_calltype_tradetype();
			break;
		case 1800354: /* ERR_INVALID_CHUIR */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_chuir();
			break;
		case 1800355: /* ERR_INVALID_CLASS_CODE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_class_code();
			break;
		case 1800356: /* ERR_INVALID_CODE_TYPE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_code_type();
			break;
		case 1800357: /* ERR_INVALID_COMPANY_CODE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_company_code();
			break;
		case 1800358: /* ERR_INVALID_CUSTOM_TRADING_SCHD */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_custom_trading_schd();
			break;
		case 1800359: /* ERR_INVALID_DATE_RANGE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_date_range();
			break;
		case 1800360: /* ERR_INVALID_DEPOSIT_ID */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_deposit_id();
			break;
		case 1800361: /* ERR_INVALID_DEPOSIT_TYPE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_deposit_type();
			break;
		case 1800362: /* ERR_INVALID_ENTITY_TYPE_SPLIT_COMM */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_entity_type_split_comm();
			break;
		case 1800363: /* ERR_INVALID_ENVELOPE_ID */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_envelope_id();
			break;
		case 1800364: /* ERR_INVALID_FEEMODEL_CODE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_feemodel_code();
			break;
		case 1800365: /* ERR_INVALID_FROM_CURRENCY */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_from_currency();
			break;
		case 1800366: /* ERR_INVALID_FUND_AND_CLASS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_fund_and_class();
			break;
		case 1800367: /* ERR_INVALID_FUND_CODE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_fund_code();
			break;
		case 1800368: /* ERR_INVALID_FUND_GROUP_TYPE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_fund_group_type();
			break;
		case 1800369: /* ERR_INVALID_FUND_SPONSOR */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_fund_sponsor();
			break;
		case 1800370: /* ERR_INVALID_GROUP */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_group();
			break;
		case 1800371: /* ERR_INVALID_GROUP_CODE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_group_code();
			break;
		case 1800372: /* ERR_INVALID_ID_TYPE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_id_type();
			break;
		case 1800373: /* ERR_INVALID_LANG */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_lang();
			break;
		case 1800374: /* ERR_INVALID_MFR_PAYMENT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_mfr_payment();
			break;
		case 1800375: /* ERR_INVALID_MODE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_mode();
			break;
		case 1800376: /* ERR_INVALID_MRS_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_mrs_account();
			break;
		case 1800377: /* ERR_INVALID_ORDER_SOURCE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_order_source();
			break;
		case 1800378: /* ERR_INVALID_ORDER_SOURCE_ACCT_DESGIN */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_order_source_acct_desgin();
			break;
		case 1800379: /* ERR_INVALID_PARAMETER_NEED_BROKERCODE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_parameter_need_brokercode();
			break;
		case 1800380: /* ERR_INVALID_PERSIST_REQUEST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_persist_request();
			break;
		case 1800381: /* ERR_INVALID_PROCESS_CATEGORY */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_process_category();
			break;
		case 1800382: /* ERR_INVALID_PROCESS_ID */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_process_id();
			break;
		case 1800383: /* ERR_INVALID_PROCESS_TYPE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_process_type();
			break;
		case 1800384: /* ERR_INVALID_PROFILE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_profile();
			break;
		case 1800385: /* ERR_INVALID_REDEMP_CODE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_redemp_code();
			break;
		case 1800386: /* ERR_INVALID_REG_AGENT_CODE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_reg_agent_code();
			break;
		case 1800387: /* ERR_INVALID_REPEAT_RECORD_TYPE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_repeat_record_type();
			break;
		case 1800388: /* ERR_INVALID_REQUEST_TYPE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_request_type();
			break;
		case 1800389: /* ERR_INVALID_RESON_CODE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_reson_code();
			break;
		case 1800390: /* ERR_INVALID_RUNMODE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_runmode();
			break;
		case 1800391: /* ERR_INVALID_SEARCH_TYPE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_search_type();
			break;
		case 1800392: /* ERR_INVALID_SETTLE_SOURCE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_settle_source();
			break;
		case 1800393: /* ERR_INVALID_SETTLE_SOURCE_ACCT_DESIGN */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_settle_source_acct_design();
			break;
		case 1800394: /* ERR_INVALID_SETTLE_TYPE_DEALER_INTERM */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_settle_type_dealer_interm();
			break;
		case 1800395: /* ERR_INVALID_SETTLEMENT_INSTRUCTION_CODE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_settlement_instruction_code();
			break;
		case 1800396: /* ERR_INVALID_SETTLEMENT_TYPE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_settlement_type();
			break;
		case 1800397: /* ERR_INVALID_SHAREHOLDER */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_shareholder();
			break;
		case 1800398: /* ERR_INVALID_SORT_BY */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_sort_by();
			break;
		case 1800399: /* ERR_INVALID_TAX_TYPE_ACCT_TYPE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_tax_type_acct_type();
			break;
		case 1800400: /* ERR_INVALID_TRADE_TYPE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_trade_type();
			break;
		case 1800401: /* ERR_INVALID_TRANSACTION_STATUS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_transaction_status();
			break;
		case 1800402: /* ERR_INVALID_TRANSFER */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_transfer();
			break;
		case 1800403: /* ERR_INVALID_TRANSID_CURRENCY_FOR_TRANBANKING */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_transid_currency_for_tranbanking();
			break;
		case 1800404: /* ERR_INVALID_TRANSLATIONTYPE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_translationtype();
			break;
		case 1800405: /* ERR_INVALID_USER_ID */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_user_id();
			break;
		case 1800406: /* ERR_INVALID_VALID_TYPE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_valid_type();
			break;
		case 1800407: /* ERR_INVALID_VALIDATION_TYPE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_invalid_validation_type();
			break;
		case 1800408: /* ERR_INVENTORY_TRACKING_ERROR */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_inventory_tracking_error();
			break;
		case 1800409: /* ERR_JOBID_NOT_GEN_CHECK_PROCESS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_jobid_not_gen_check_process();
			break;
		case 1800410: /* ERR_JOINT_INFORMATION_ONLY_FOR_JOINT_ACCOUNTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_joint_information_only_for_joint_accounts();
			break;
		case 1800411: /* ERR_KV_NUM_DOES_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_kv_num_does_not_exist();
			break;
		case 1800412: /* ERR_KV_NUM_MUST_BE_ENTERED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_kv_num_must_be_entered();
			break;
		case 1800413: /* ERR_KYC_RECORD_ALREADY_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_kyc_record_already_exist();
			break;
		case 1800414: /* ERR_KYC_RECORD_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_kyc_record_not_found();
			break;
		case 1800415: /* ERR_LAST_BANK_TYPE_MUST_BE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_last_bank_type_must_be();
			break;
		case 1800416: /* ERR_LINK_CANNOT_BE_DEL */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_link_cannot_be_del();
			break;
		case 1800417: /* ERR_LLP_ERROR */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_llp_error();
			break;
		case 1800418: /* ERR_MALFORMED_DSTC_RESPONSE_BUFFER */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_malformed_dstc_response_buffer();
			break;
		case 1800419: /* ERR_MALFORMED_STUB_FILE_RESPONSE_BUFFER */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_malformed_stub_file_response_buffer();
			break;
		case 1800420: /* ERR_MANAGEMENT_COMPANY_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_management_company_not_found();
			break;
		case 1800421: /* ERR_MANAGEMENT_FEE_MODEL_MISSING */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_management_fee_model_missing();
			break;
		case 1800422: /* ERR_MATURITY_DATE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_maturity_date();
			break;
		case 1800423: /* ERR_MATURITYBANK_IS_MISSING */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_maturitybank_is_missing();
			break;
		case 1800424: /* ERR_MFCS_COMPLIANT_553 */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_mfcs_compliant_553();
			break;
		case 1800425: /* ERR_MIN_INITIAL_PURCH */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_min_initial_purch();
			break;
		case 1800426: /* ERR_MIRROR_CHILD_AMS_REBALANCE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_mirror_child_ams_rebalance();
			break;
		case 1800427: /* ERR_MISMATCHED_UNIT_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_mismatched_unit_available();
			break;
		case 1800428: /* ERR_MISMATCHED_UNITS_AVAIL */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_mismatched_units_avail();
			break;
		case 1800429: /* ERR_MISSING_ALLOCATION_INFO */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_missing_allocation_info();
			break;
		case 1800430: /* ERR_MISSING_CUSTOM_TRADING_SCHD */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_missing_custom_trading_schd();
			break;
		case 1800431: /* ERR_MKT_INDEX_DETAIL_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_mkt_index_detail_exists();
			break;
		case 1800432: /* ERR_MKT_INDEX_DETAIL_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_mkt_index_detail_not_found();
			break;
		case 1800433: /* ERR_MKT_INDEX_EXISTS_WITH_INDEX_CODE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_mkt_index_exists_with_index_code();
			break;
		case 1800434: /* ERR_MKT_INDEX_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_mkt_index_not_found();
			break;
		case 1800435: /* ERR_MKT_INDEX_REC_LOCKED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_mkt_index_rec_locked();
			break;
		case 1800436: /* ERR_MKT_INDEX_RECORD_LOCKED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_mkt_index_record_locked();
			break;
		case 1800437: /* ERR_MORE_THAN_ONE_MATCH_THE_SEARCH_CRITERIA */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_more_than_one_match_the_search_criteria();
			break;
		case 1800438: /* ERR_MULITIPLE_ADDRESS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_mulitiple_address();
			break;
		case 1800439: /* ERR_MULTIPLE_ALLOC_SAME_EFF_DATE_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_multiple_alloc_same_eff_date_not_allowed();
			break;
		case 1800440: /* ERR_MULTIPLE_ENTITIES_MATCH */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_multiple_entities_match();
			break;
		case 1800441: /* ERR_MUST_HAVE_ONE_ACTIVE_REC */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_must_have_one_active_rec();
			break;
		case 1800442: /* ERR_NEGATIVE_GUARANTEE_CANNOT_EXIT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_negative_guarantee_cannot_exit();
			break;
		case 1800443: /* ERR_NEGATIVE_GUARANTEE_ORIG_TRADEDATE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_negative_guarantee_orig_tradedate();
			break;
		case 1800444: /* ERR_NEGATIVE_GUARANTEES_FOLLOWING_MUST_BE_CANCELLED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_negative_guarantees_following_must_be_cancelled();
			break;
		case 1800445: /* ERR_NETWORKORDER_ALREADY_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_networkorder_already_exists();
			break;
		case 1800446: /* ERR_NEW_DATE_BIRTH_CANNOTBE_BLANK */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_new_date_birth_cannotbe_blank();
			break;
		case 1800447: /* ERR_NEW_LEGAL_CONTRACT_MAT_DATE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_new_legal_contract_mat_date();
			break;
		case 1800448: /* ERR_NEW_PASSWORD_TOO_LONG */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_new_password_too_long();
			break;
		case 1800449: /* ERR_NEXT_KEY_DID_NOT_MATCH_EXPECTED_FORMAT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_next_key_did_not_match_expected_format();
			break;
		case 1800450: /* ERR_NO_ACCESS_TO_SLSREP */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_access_to_slsrep();
			break;
		case 1800451: /* ERR_NO_ACCOUNT_SHR_NUMBER */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_account_shr_number();
			break;
		case 1800452: /* ERR_NO_ACCOUNTHOLDING */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_accountholding();
			break;
		case 1800453: /* ERR_NO_ACCT_CONTRACT_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_acct_contract_available();
			break;
		case 1800454: /* ERR_NO_ACCT_VALUE_REC_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_acct_value_rec_exists();
			break;
		case 1800455: /* ERR_NO_ACTENTDELOPTN_REC_AVAIL */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_actentdeloptn_rec_avail();
			break;
		case 1800457: /* ERR_NO_ACTIVE_OWNER_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_active_owner_found();
			break;
		case 1800458: /* ERR_NO_ADDITIONAL_TRADE_DATE_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_additional_trade_date_exist();
			break;
		case 1800459: /* ERR_NO_ADDRESS_RECORD_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_address_record_available();
			break;
		case 1800460: /* ERR_NO_AMOUNT_AVAIL_IN_CASH_FUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_amount_avail_in_cash_fund();
			break;
		case 1800461: /* ERR_NO_AMS_RECORD */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_ams_record();
			break;
		case 1800462: /* ERR_NO_AVAIL_UNITS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_avail_units();
			break;
		case 1800463: /* ERR_NO_BENEFICIARY_RECORD_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_beneficiary_record_available();
			break;
		case 1800464: /* ERR_NO_BRANCH_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_branch_found();
			break;
		case 1800465: /* ERR_NO_BUSSINESS_DAY_RECORD_AVAIL */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_bussiness_day_record_avail();
			break;
		case 1800466: /* ERR_NO_CLAN_PLAN_UPDATE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_clan_plan_update();
			break;
		case 1800467: /* ERR_NO_COMM_SCALE_RECORD_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_comm_scale_record_available();
			break;
		case 1800468: /* ERR_NO_COMPANY_RECORD */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_company_record();
			break;
		case 1800469: /* ERR_NO_CONTRACTMSTR */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_contractmstr();
			break;
		case 1800470: /* ERR_NO_COT_CONTRACT_SHGROUP */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_cot_contract_shgroup();
			break;
		case 1800471: /* ERR_NO_DATA_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_data_available();
			break;
		case 1800472: /* ERR_NO_DATA_IN_REPEAT_SECTION */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_data_in_repeat_section();
			break;
		case 1800473: /* ERR_NO_DEP_ID_RECORDS_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_dep_id_records_available();
			break;
		case 1800474: /* ERR_NO_EARNING_IN_THE_ACCT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_earning_in_the_acct();
			break;
		case 1800475: /* ERR_NO_ENOUGH_INPUT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_enough_input();
			break;
		case 1800476: /* ERR_NO_ENTITY_TAX_HIST_FOUND_FOR_PA */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_entity_tax_hist_found_for_pa();
			break;
		case 1800477: /* ERR_NO_ESCROW_REP_RECORD_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_escrow_rep_record_available();
			break;
		case 1800478: /* ERR_NO_ESOP_INFO_REC_AVAIL */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_esop_info_rec_avail();
			break;
		case 1800479: /* ERR_NO_ESOP_INFO_RECORD_AVAILIABLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_esop_info_record_availiable();
			break;
		case 1800480: /* ERR_NO_FEE_ACCRUAL_INFORMATION_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_fee_accrual_information_available();
			break;
		case 1800481: /* ERR_NO_FEE_DEFINED_FOR_FEE_OVERRIDE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_fee_defined_for_fee_override();
			break;
		case 1800482: /* ERR_NO_FUTURE_DATE_MIN_MAX */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_future_date_min_max();
			break;
		case 1800483: /* ERR_NO_INTEREST_ACCRUAL_INFORMATION_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_interest_accrual_information_available();
			break;
		case 1800484: /* ERR_NO_JOBS_AVAIL */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_jobs_avail();
			break;
		case 1800485: /* ERR_NO_JOINT_ENTITY_RECORD_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_joint_entity_record_available();
			break;
		case 1800486: /* ERR_NO_MAILING_INFO_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_mailing_info_available();
			break;
		case 1800487: /* ERR_NO_MATCHES_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_matches_found();
			break;
		case 1800488: /* ERR_NO_PARAM_REC_AVAIL */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_param_rec_avail();
			break;
		case 1800489: /* ERR_NO_PENDING_RESP_TRADES */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_pending_resp_trades();
			break;
		case 1800490: /* ERR_NO_PENDING_TRADES_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_pending_trades_found();
			break;
		case 1800491: /* ERR_NO_PENSION_INFO_REC_AVAIL */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_pension_info_rec_avail();
			break;
		case 1800492: /* ERR_NO_PRINTER_RECORDS_AVAIL */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_printer_records_avail();
			break;
		case 1800493: /* ERR_NO_PROCESSED_RESP_TRADES */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_processed_resp_trades();
			break;
		case 1800494: /* ERR_NO_PROCESSED_TRADES_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_processed_trades_found();
			break;
		case 1800495: /* ERR_NO_PRODUCT_GROUP_CODE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_product_group_code();
			break;
		case 1800496: /* ERR_NO_PURCHASE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_purchase();
			break;
		case 1800497: /* ERR_NO_RELATED_CHUI_FUNCTIONS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_related_chui_functions();
			break;
		case 1800498: /* ERR_NO_RESP_ACCOUNT_INFORMATION */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_resp_account_information();
			break;
		case 1800499: /* ERR_NO_RESPCONTRDETL_REC_AVAIL */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_respcontrdetl_rec_avail();
			break;
		case 1800500: /* ERR_NO_RIF_ALLOCATION_INFO */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_rif_allocation_info();
			break;
		case 1800501: /* ERR_NO_RIF_SETUP_INFO */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_rif_setup_info();
			break;
		case 1800502: /* ERR_NO_SETUP_RECORD */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_setup_record();
			break;
		case 1800503: /* ERR_NO_SHAARELOT_RECORD_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_shaarelot_record_available();
			break;
		case 1800504: /* ERR_NO_SLSREP_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_slsrep_found();
			break;
		case 1800505: /* ERR_NO_TAXTYPE_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_taxtype_available();
			break;
		case 1800506: /* ERR_NO_TITLE_RESTRICT_REC_AVAIL */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_title_restrict_rec_avail();
			break;
		case 1800507: /* ERR_NO_TRANSACTION_NUMBER */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_transaction_number();
			break;
		case 1800508: /* ERR_NO_UNIQE_NAME_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_uniqe_name_found();
			break;
		case 1800509: /* ERR_NO_USER */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_user();
			break;
		case 1800510: /* ERR_NO_USERID */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_userid();
			break;
		case 1800511: /* ERR_No_Valid_Acct_Level_CONTRACT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_valid_acct_level_contract();
			break;
		case 1800512: /* ERR_NO_VALID_CONTRACT_ORIG_TRADEDATE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_valid_contract_orig_tradedate();
			break;
		case 1800513: /* ERR_NO_VALUATION_SCHEDULE_FOR_FUNDGROUP */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_valuation_schedule_for_fundgroup();
			break;
		case 1800514: /* ERR_NO_VALUATION_SCHEDULE_GROUP_FUND_SETUP */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_no_valuation_schedule_group_fund_setup();
			break;
		case 1800515: /* ERR_NOMINEE_ENTITY_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_nominee_entity_not_found();
			break;
		case 1800516: /* ERR_NON_INT_AMT_ZERO_PRECISION */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_non_int_amt_zero_precision();
			break;
		case 1800517: /* ERR_NON_JOINT_ACCOUNT_ONE_ACCOUNTHOLDER */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_non_joint_account_one_accountholder();
			break;
		case 1800518: /* ERR_NOT_AN_EFT_TRANSACTION */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_not_an_eft_transaction();
			break;
		case 1800519: /* ERR_NOT_APPLICABLE_FOR_THIS_FUNDCLASS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_not_applicable_for_this_fundclass();
			break;
		case 1800520: /* ERR_NOT_AUTHENTIC */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_not_authentic();
			break;
		case 1800521: /* ERR_NOT_CONFIGURED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_not_configured();
			break;
		case 1800522: /* ERR_NOT_ENOUGH_GRANT_AMT_RETURN */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_not_enough_grant_amt_return();
			break;
		case 1800523: /* ERR_NOT_ENOUGH_INPUT_INFO_FOR_RECORD_SELECTION */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_not_enough_input_info_for_record_selection();
			break;
		case 1800524: /* ERR_NOT_ENOUGH_SETTLED_UNITS_TO_SETTLE_REDEMPTION */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_not_enough_settled_units_to_settle_redemption();
			break;
		case 1800525: /* ERR_NOT_FOUND_RESP_EARNING_GRANT_REDCODES_CONTROLS_RECORD */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_not_found_resp_earning_grant_redcodes_controls_record();
			break;
		case 1800526: /* ERR_NOT_VALID_FUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_not_valid_fund();
			break;
		case 1800527: /* ERR_NOT_WIRE_ORDER_TRADE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_not_wire_order_trade();
			break;
		case 1800528: /* ERR_NUM_UNITS_REQUIRED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_num_units_required();
			break;
		case 1800529: /* ERR_ONLINE_ACCESS_FOR_CLIENT_HELD_ACC */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_online_access_for_client_held_acc();
			break;
		case 1800530: /* ERR_ONLY_RD_ALLOW_RESP_TRANSFER */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_only_rd_allow_resp_transfer();
			break;
		case 1800531: /* ERR_ORDER_DETAIL_ALREADY_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_order_detail_already_exists();
			break;
		case 1800532: /* ERR_ORDER_DETAIL_DOES_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_order_detail_does_not_exist();
			break;
		case 1800533: /* ERR_ORDER_HEADER_ALREADY_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_order_header_already_exists();
			break;
		case 1800534: /* ERR_ORDER_STATUS_BLANK */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_order_status_blank();
			break;
		case 1800535: /* ERR_ORIGTRANSLD_MUST_BLANK */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_origtransld_must_blank();
			break;
		case 1800536: /* ERR_OVERLAPPING_OR_SAME_DAY_COMMISSION */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_overlapping_or_same_day_commission();
			break;
		case 1800537: /* ERR_PA_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_pa_not_found();
			break;
		case 1800538: /* ERR_PAC_INDEX_LOCKED_BY_ANOTHER_USER */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_pac_index_locked_by_another_user();
			break;
		case 1800539: /* ERR_PASSWORD_DENIED_CHANGE_NO_ALLOWED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_password_denied_change_no_allowed();
			break;
		case 1800540: /* ERR_PASSWORD_DENIED_TOO_LONG */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_password_denied_too_long();
			break;
		case 1800541: /* ERR_PASSWORD_DENIED_TOO_SHORT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_password_denied_too_short();
			break;
		case 1800542: /* ERR_PAST_CUT_OFF_TIME */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_past_cut_off_time();
			break;
		case 1800543: /* ERR_PAY_ENTITY_EXISTS_FOR_DATE_RANGE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_pay_entity_exists_for_date_range();
			break;
		case 1800544: /* ERR_PAY_INSTRUCT_EXISTS_FOR_DATE_RANGE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_pay_instruct_exists_for_date_range();
			break;
		case 1800545: /* ERR_PAYENTITY_ALREADY_EXIST_FOR_BROKER */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_payentity_already_exist_for_broker();
			break;
		case 1800546: /* ERR_PAYENTITY_DOES_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_payentity_does_not_exist();
			break;
		case 1800547: /* ERR_PAYENTITY_DOES_NOT_EXIST_FOR_DATE_RANGE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_payentity_does_not_exist_for_date_range();
			break;
		case 1800548: /* ERR_PAYINSTRUCT_ALREADY_EXISTS_FOR_BROKER */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_payinstruct_already_exists_for_broker();
			break;
		case 1800549: /* ERR_PAYINSTRUCT_DOES_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_payinstruct_does_not_exist();
			break;
		case 1800550: /* ERR_PD_CANNOT_CHANGE_PASSORD_FOR */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_pd_cannot_change_passord_for();
			break;
		case 1800551: /* ERR_PD_HAS_BEEN_USED_RECENTLY_CHOOSE_ANOTHER */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_pd_has_been_used_recently_choose_another();
			break;
		case 1800552: /* ERR_PD_NEED_TWO_OR_MORE_ALPHABETIC_CHARS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_pd_need_two_or_more_alphabetic_chars();
			break;
		case 1800553: /* ERR_PD_NEED_TWO_OR_MORE_NON_ALPHA_CHARS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_pd_need_two_or_more_non_alpha_chars();
			break;
		case 1800554: /* ERR_PD_NO_BLANKS_ALLOWED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_pd_no_blanks_allowed();
			break;
		case 1800555: /* ERR_PD_OLD_PASSWORD_INCORRECT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_pd_old_password_incorrect();
			break;
		case 1800556: /* ERR_PD_ONLY_ONE_REPETITION_OF_CHARS_ALLOWED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_pd_only_one_repetition_of_chars_allowed();
			break;
		case 1800557: /* ERR_PD_ONLY_SEVEN_CHARS_IN_A_ROW */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_pd_only_seven_chars_in_a_row();
			break;
		case 1800558: /* ERR_PD_PASSWORD_CAN_ONLY_BE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_pd_password_can_only_be();
			break;
		case 1800559: /* ERR_PD_PASSWORD_MUST_BE_AT_LEAST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_pd_password_must_be_at_least();
			break;
		case 1800560: /* ERR_PD_THREE_OF_SAME_CHARS_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_pd_three_of_same_chars_not_allowed();
			break;
		case 1800561: /* ERR_PD_UNKNOWN_ACCESS_PROFILE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_pd_unknown_access_profile();
			break;
		case 1800562: /* ERR_PD_UNKNOWN_USER */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_pd_unknown_user();
			break;
		case 1800563: /* ERR_PENDING_EXIST_WITH_TRANSNUM */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_pending_exist_with_transnum();
			break;
		case 1800564: /* ERR_PENDING_TRADE_BANK_INVALID */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_pending_trade_bank_invalid();
			break;
		case 1800565: /* ERR_PENDING_TRADE_CANNOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_pending_trade_cannot_exist();
			break;
		case 1800566: /* ERR_PENDING_TRADE_NOT_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_pending_trade_not_exists();
			break;
		case 1800567: /* ERR_PENDING_TRADE_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_pending_trade_not_found();
			break;
		case 1800568: /* ERR_PENSION_INFORMATION_NA */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_pension_information_na();
			break;
		case 1800569: /* ERR_PERSISTENCE_START_REQUEST_FAILED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_persistence_start_request_failed();
			break;
		case 1800570: /* ERR_PERSISTENT_FREERESP_FAILED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_persistent_freeresp_failed();
			break;
		case 1800571: /* ERR_PERSISTENT_NEEDED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_persistent_needed();
			break;
		case 1800572: /* ERR_PF_CRYSTALISATION_IS_NOT_YET_COMPLETED_FOR_FUNDCLASS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_pf_crystalisation_is_not_yet_completed_for_fundclass();
			break;
		case 1800573: /* ERR_PLAN_CODE_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_plan_code_not_found();
			break;
		case 1800574: /* ERR_PLEASE_CANCLE_MONEY_OUT_TEANS_FOR_BACKDATED_PRIOR */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_please_cancle_money_out_teans_for_backdated_prior();
			break;
		case 1800575: /* ERR_PLEASE_SEND_AGAIN_AS_LAST_RECORD_WAS_DELETED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_please_send_again_as_last_record_was_deleted();
			break;
		case 1800576: /* ERR_POSTAL_CODE_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_postal_code_not_found();
			break;
		case 1800577: /* ERR_PRI_CONTACT_WHERE_USE_RECORD_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_pri_contact_where_use_record_not_exist();
			break;
		case 1800578: /* ERR_PROCESS_REDEMP_ESOP_INVEST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_process_redemp_esop_invest();
			break;
		case 1800579: /* ERR_PROCESS_REDEMP_ESOP_PARTICIP */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_process_redemp_esop_particip();
			break;
		case 1800580: /* ERR_PROCESS_TYPE_MUST_BE_11 */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_process_type_must_be_11();
			break;
		case 1800581: /* ERR_PRODUCT_GROUP_CODE_INVALID */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_product_group_code_invalid();
			break;
		case 1800582: /* ERR_PROGRESS_ERROR */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_progress_error();
			break;
		case 1800583: /* ERR_PROTECTED_FUND_DOES_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_protected_fund_does_not_exist();
			break;
		case 1800584: /* ERR_PROTECTED_FUND_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_protected_fund_exists();
			break;
		case 1800585: /* ERR_PROVINCE_FILE_NA */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_province_file_na();
			break;
		case 1800586: /* ERR_PROVINCE_MUST_BE_ENTERED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_province_must_be_entered();
			break;
		case 1800587: /* ERR_PURCHASE_ANNUITANT_OLDER_THAN_LATEST_AGE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_purchase_annuitant_older_than_latest_age();
			break;
		case 1800588: /* ERR_PWD_NOT_CHANGE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_pwd_not_change();
			break;
		case 1800589: /* ERR_PWD_NOT_CONTAIN_USER */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_pwd_not_contain_user();
			break;
		case 1800590: /* ERR_PWD_USER_NOT_BE_SAME */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_pwd_user_not_be_same();
			break;
		case 1800591: /* ERR_RB_DEFAULT_ALLOCATION_NOT_SET_UP */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_rb_default_allocation_not_set_up();
			break;
		case 1800592: /* ERR_REASON_ACCOUNTABLE_CAN_NOT_BLANK */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_reason_accountable_can_not_blank();
			break;
		case 1800593: /* ERR_RECIPIENT_INFO_NOT_SET_UP */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_recipient_info_not_set_up();
			break;
		case 1800594: /* ERR_RECORD_LOCKED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_record_locked();
			break;
		case 1800595: /* ERR_RECREATING_POLICY_PERIOD */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_recreating_policy_period();
			break;
		case 1800596: /* ERR_REDEMP_CODE_RULE_NOT_SETUP */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_redemp_code_rule_not_setup();
			break;
		case 1800597: /* ERR_REDEMP_NOT_ALLOW_ESOP */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_redemp_not_allow_esop();
			break;
		case 1800598: /* ERR_REDEMP_NOT_ALLOWED_FUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_redemp_not_allowed_fund();
			break;
		case 1800599: /* ERR_REDEMP_STOP_FLAG_ENABLED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_redemp_stop_flag_enabled();
			break;
		case 1800600: /* ERR_REDEMPTIONCODE_NOT_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_redemptioncode_not_available();
			break;
		case 1800601: /* ERR_REGISTER_ADDRESS_NOT_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_register_address_not_available();
			break;
		case 1800602: /* ERR_REGISTERED_ADDRESS_DEFAULT_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_registered_address_default_not_found();
			break;
		case 1800603: /* ERR_REMAIN_MIN_AMT_REDEPM_NOT_PROCESSED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_remain_min_amt_redepm_not_processed();
			break;
		case 1800604: /* ERR_REMAINING_ACCT_BAL_INSUFFICIENT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_remaining_acct_bal_insufficient();
			break;
		case 1800605: /* ERR_REMARKS_NO_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_remarks_no_found();
			break;
		case 1800606: /* ERR_REPRINT_RECORD_ALREADY_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_reprint_record_already_exists();
			break;
		case 1800607: /* ERR_REPRINT_RECORD_DOES_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_reprint_record_does_not_exist();
			break;
		case 1800608: /* ERR_REQUEST_FIELDS_INVALID */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_request_fields_invalid();
			break;
		case 1800609: /* ERR_RESET_OCCURED_SINCE_ORIG_TRADEDATE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_reset_occured_since_orig_tradedate();
			break;
		case 1800610: /* ERR_RESP_ACCT_INFO_NOT_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_resp_acct_info_not_available();
			break;
		case 1800611: /* ERR_RESP_BENEF_RECORD_LOCKED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_resp_benef_record_locked();
			break;
		case 1800612: /* ERR_RESP_BENEF_RECORD_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_resp_benef_record_not_found();
			break;
		case 1800613: /* ERR_RESP_BENEF_RECORD_VERSION_NOT_MATCH */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_resp_benef_record_version_not_match();
			break;
		case 1800614: /* ERR_RESP_PLAN_LIMIT_EXCEEDED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_resp_plan_limit_exceeded();
			break;
		case 1800615: /* ERR_RESP_RECORD_LOCKED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_resp_record_locked();
			break;
		case 1800616: /* ERR_RESP_RECORD_UNAVAILABLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_resp_record_unavailable();
			break;
		case 1800617: /* ERR_RESP_REDEMP_EXCEED_CONTRIB */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_resp_redemp_exceed_contrib();
			break;
		case 1800618: /* ERR_RESP_REDEMP_EXCEED_EARNINGS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_resp_redemp_exceed_earnings();
			break;
		case 1800619: /* ERR_RESP_TRANSFER_AMT_TOO_HIGH */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_resp_transfer_amt_too_high();
			break;
		case 1800620: /* ERR_RESP_TRINFO_NOT_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_resp_trinfo_not_available();
			break;
		case 1800621: /* ERR_RESP_YEAR_LIMIT_EXCEEDED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_resp_year_limit_exceeded();
			break;
		case 1800622: /* ERR_REVERSAL_CODE_TOP_UP_INCORRECT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_reversal_code_top_up_incorrect();
			break;
		case 1800623: /* ERR_ROUTING_REF_NUMBER_BLANK */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_routing_ref_number_blank();
			break;
		case 1800624: /* ERR_RRIF_ALREADY_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_rrif_already_exists();
			break;
		case 1800625: /* ERR_RRIF_DETAIL_RECID_INVALID */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_rrif_detail_recid_invalid();
			break;
		case 1800626: /* ERR_RRIFINFO_ALREADY_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_rrifinfo_already_exists();
			break;
		case 1800627: /* ERR_RTS_CONFIG_ISSUE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_rts_config_issue();
			break;
		case 1800628: /* ERR_RTS_DATABASE_CONNECTION */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_rts_database_connection();
			break;
		case 1800629: /* ERR_RTS_IFAST_NOT_RESPONDING */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_rts_ifast_not_responding();
			break;
		case 1800630: /* ERR_RTS_OUT_OF_DISK_SPACE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_rts_out_of_disk_space();
			break;
		case 1800631: /* ERR_RTS_OUT_OF_MEMERY */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_rts_out_of_memery();
			break;
		case 1800632: /* ERR_RTS_SYSTEM_ISSUE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_rts_system_issue();
			break;
		case 1800633: /* ERR_RUN_MODE_INVALID */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_run_mode_invalid();
			break;
		case 1800634: /* ERR_SALES_REP_ALREADY_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_sales_rep_already_exists();
			break;
		case 1800635: /* ERR_SALES_REP_DOES_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_sales_rep_does_not_exist();
			break;
		case 1800636: /* ERR_SALES_REP_NO_LONGER_ACTIVE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_sales_rep_no_longer_active();
			break;
		case 1800637: /* ERR_SALESREP_CANNOT_ACCESS_THIS_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_salesrep_cannot_access_this_account();
			break;
		case 1800638: /* ERR_SCALE_DETL_RECORD_NOT_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_scale_detl_record_not_available();
			break;
		case 1800639: /* ERR_SCALE_REC_REQUIRED_FEE_2_3 */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_scale_rec_required_fee_2_3();
			break;
		case 1800640: /* ERR_SCHEDULED_PAYMENT_NOT_AVAIL */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_scheduled_payment_not_avail();
			break;
		case 1800641: /* ERR_SEARCH_FOR_SLSREP_BY_BROKER_CODE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_search_for_slsrep_by_broker_code();
			break;
		case 1800642: /* ERR_SEC_CONTACT_WHERE_USE_RECORD_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_sec_contact_where_use_record_not_exist();
			break;
		case 1800643: /* ERR_SECURITY_PROFILE_DOES_NOT_HAVE_ACCESS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_security_profile_does_not_have_access();
			break;
		case 1800644: /* ERR_SECURITY_SETUP_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_security_setup_not_found();
			break;
		case 1800645: /* ERR_SEE_ERROR_LOG_REDEMLOGD */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_see_error_log_redemlogd();
			break;
		case 1800646: /* ERR_SEG_CALC_REQUEST_DURING_CANCEL */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_seg_calc_request_during_cancel();
			break;
		case 1800647: /* ERR_SEG_GUAR_DETL_RECORD_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_seg_guar_detl_record_not_found();
			break;
		case 1800648: /* ERR_SEG_GUAR_MAT_RECORD_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_seg_guar_mat_record_not_found();
			break;
		case 1800649: /* ERR_SEG_MANUAL_EVENTS_SINCE_ORIGINAL_TRADE_DATE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_seg_manual_events_since_original_trade_date();
			break;
		case 1800650: /* ERR_SEQNUM_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_seqnum_not_exist();
			break;
		case 1800651: /* ERR_SETTLE_BANK_NOT_VERFIED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_settle_bank_not_verfied();
			break;
		case 1800652: /* ERR_SETTLE_LOC_ACCT_ALREADY_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_settle_loc_acct_already_exists();
			break;
		case 1800653: /* ERR_SETTLE_LOC_ACCT_DATA_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_settle_loc_acct_data_not_found();
			break;
		case 1800654: /* ERR_SETTLE_LOC_ACCT_DOES_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_settle_loc_acct_does_not_exist();
			break;
		case 1800655: /* ERR_SETTLE_LOC_ALREADY_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_settle_loc_already_exists();
			break;
		case 1800656: /* ERR_SETTLE_LOC_DATA_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_settle_loc_data_not_found();
			break;
		case 1800657: /* ERR_SETTLE_LOC_DOES_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_settle_loc_does_not_exist();
			break;
		case 1800658: /* ERR_SETTLEMENT_NOT_ALLOWED_551 */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_settlement_not_allowed_551();
			break;
		case 1800659: /* ERR_SETTLEMENT_NOT_ALLOWED_DURING_CYCLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_settlement_not_allowed_during_cycle();
			break;
		case 1800660: /* ERR_SHAREHOLDER_FAMILY_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_shareholder_family_exists();
			break;
		case 1800661: /* ERR_SHAREHOLDER_FAMILY_RECORD_NOT_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_shareholder_family_record_not_exists();
			break;
		case 1800662: /* ERR_SHAREHOLDER_NUMBER_GREATER_THEN_ZERO */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_shareholder_number_greater_then_zero();
			break;
		case 1800663: /* ERR_SHAREHOLDER_NUMBER_NOT_GREATER_THEN_SIX_DIGITS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_shareholder_number_not_greater_then_six_digits();
			break;
		case 1800664: /* ERR_SHAREHOLDER_RESIDENCY_NOT_VALID */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_shareholder_residency_not_valid();
			break;
		case 1800665: /* ERR_SHARELOT_UNITS_DO_NOT_MATCH_TRANSACTION_UNITS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_sharelot_units_do_not_match_transaction_units();
			break;
		case 1800666: /* ERR_SHR_FUND_BROKER_ALREADY_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_shr_fund_broker_already_exists();
			break;
		case 1800667: /* ERR_SHR_FUND_SPONSOR_AGRMNT_ALREADY_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_shr_fund_sponsor_agrmnt_already_exists();
			break;
		case 1800668: /* ERR_SHR_FUND_SPONSOR_AGRMNT_DOES_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_shr_fund_sponsor_agrmnt_does_not_exist();
			break;
		case 1800669: /* ERR_SHRHLDR_ADDR_NOT_VERIFIED_FOR_SETTLEMENT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_shrhldr_addr_not_verified_for_settlement();
			break;
		case 1800670: /* ERR_SLS_REP_NOT_ELIGIBLE_FOR_WRAP */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_sls_rep_not_eligible_for_wrap();
			break;
		case 1800671: /* ERR_SMQ_APPSERVER_ERROR */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_smq_appserver_error();
			break;
		case 1800672: /* ERR_SMQ_AUTHORIZATION_DENIED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_smq_authorization_denied();
			break;
		case 1800673: /* ERR_SMQ_AUTHORIZATION_ERROR */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_smq_authorization_error();
			break;
		case 1800674: /* ERR_SMQ_BROKEN_APPSERVER_CONNECTION */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_smq_broken_appserver_connection();
			break;
		case 1800675: /* ERR_SMQ_CONNECT_FAILED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_smq_connect_failed();
			break;
		case 1800676: /* ERR_SMQ_FRAMEWORK_ERROR */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_smq_framework_error();
			break;
		case 1800677: /* ERR_SMQ_MESSAGE_RECEIVE_FAILED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_smq_message_receive_failed();
			break;
		case 1800678: /* ERR_SMQ_MESSAGE_SEND_FAILED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_smq_message_send_failed();
			break;
		case 1800679: /* ERR_SMQ_NO_APPSERVER */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_smq_no_appserver();
			break;
		case 1800680: /* ERR_SMQ_SESSION_EXPIRED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_smq_session_expired();
			break;
		case 1800681: /* ERR_SMQ_SONICMQ_ERROR */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_smq_sonicmq_error();
			break;
		case 1800682: /* ERR_SMQ_UNKNOWN_MESSAGE_TYPE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_smq_unknown_message_type();
			break;
		case 1800683: /* ERR_SOCKET_CONNECT_FAILED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_socket_connect_failed();
			break;
		case 1800684: /* ERR_SOCKET_INITIALIZATION_FAILED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_socket_initialization_failed();
			break;
		case 1800685: /* ERR_SOCKET_RECEIVE_FAILED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_socket_receive_failed();
			break;
		case 1800686: /* ERR_SOCKET_SEND_FAILED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_socket_send_failed();
			break;
		case 1800687: /* ERR_SPLIT_COMMISSION_RECORD_ALREADY_EXISTS_FOR_THIS_ENTITY */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_split_commission_record_already_exists_for_this_entity();
			break;
		case 1800688: /* ERR_SPLIT_COMMISSION_RECORD_DOES_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_split_commission_record_does_not_exist();
			break;
		case 1800689: /* ERR_SPLIT_DILUTION_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_split_dilution_not_allowed();
			break;
		case 1800690: /* ERR_SPLITCOM_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_splitcom_exists();
			break;
		case 1800691: /* ERR_SPLITCOM_FEE_DEF_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_splitcom_fee_def_not_found();
			break;
		case 1800692: /* ERR_SPLITCOMM_FEEDEFN_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_splitcomm_feedefn_not_found();
			break;
		case 1800693: /* ERR_STOP_BEFORE_START */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_stop_before_start();
			break;
		case 1800694: /* ERR_STOP_DATE_FUND_SAME_TRADE_DATE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_stop_date_fund_same_trade_date();
			break;
		case 1800695: /* ERR_STOP_PW_FLAG_ACTIVE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_stop_pw_flag_active();
			break;
		case 1800696: /* ERR_STREET_NAME_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_street_name_not_found();
			break;
		case 1800697: /* ERR_SUBSEQUENT_EVENTS_TAKEN_PLACE_AT_CANCELLATION */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_subsequent_events_taken_place_at_cancellation();
			break;
		case 1800698: /* ERR_SWITCH_SETTLE_FAILED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_switch_settle_failed();
			break;
		case 1800699: /* ERR_SYSTEM_UNAVAILABLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_system_unavailable();
			break;
		case 1800700: /* ERR_SYSTEMATIC_PROCESS_DATE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_systematic_process_date();
			break;
		case 1800701: /* ERR_TAX_JURIS_NOT_FOUND_FOR_OWNER */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_tax_juris_not_found_for_owner();
			break;
		case 1800702: /* ERR_TAX_TYPE_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_tax_type_not_found();
			break;
		case 1800703: /* ERR_TAX_TYPE_RULE_NOT_AVAIL */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_tax_type_rule_not_avail();
			break;
		case 1800704: /* ERR_TAX_TYPES_RULES_NOT_SET_UP */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_tax_types_rules_not_set_up();
			break;
		case 1800705: /* ERR_TAXEXEMPT_AUTH_ALREADY_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_taxexempt_auth_already_exists();
			break;
		case 1800706: /* ERR_TAXEXEMPT_AUTH_DOES_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_taxexempt_auth_does_not_exist();
			break;
		case 1800707: /* ERR_TAXTYPE_MUST_BE_ENTERED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_taxtype_must_be_entered();
			break;
		case 1800708: /* ERR_THIS_TAX_TYPE_NOT_LOCKED_IN */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_this_tax_type_not_locked_in();
			break;
		case 1800709: /* ERR_TIME_ZONE_INVALID */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_time_zone_invalid();
			break;
		case 1800710: /* ERR_TRADE_BANK_NOT_VERIFIED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_trade_bank_not_verified();
			break;
		case 1800711: /* ERR_TRADE_DATE_DELAY_EXIST_FOR_FUNDCLASS_UNABLE_TO */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_trade_date_delay_exist_for_fundclass_unable_to();
			break;
		case 1800712: /* ERR_TRADE_DATE_FUTURE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_trade_date_future();
			break;
		case 1800713: /* ERR_TRADE_DATE_IS_IN_FUTURE_FOR_THE_SELECTED_VALUATION_DATE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_trade_date_is_in_future_for_the_selected_valuation_date();
			break;
		case 1800714: /* ERR_TRADE_DATE_LATER_THAN_RESP_CONTRIB */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_trade_date_later_than_resp_contrib();
			break;
		case 1800715: /* ERR_TRADE_DATE_REQUIRED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_trade_date_required();
			break;
		case 1800716: /* ERR_TRADE_GUAR_ADJ_EXISTS_AFTER_TRADE_DATE_ACCT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_trade_guar_adj_exists_after_trade_date_acct();
			break;
		case 1800717: /* ERR_TRADE_IS_THIRTY_OLD_OLDER */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_trade_is_thirty_old_older();
			break;
		case 1800718: /* ERR_TRADE_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_trade_not_found();
			break;
		case 1800719: /* ERR_TRADE_PARTOF_DM_EVENT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_trade_partof_dm_event();
			break;
		case 1800720: /* ERR_TRADE_PAY_INSTRUCT_RECORD_ALREADY_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_trade_pay_instruct_record_already_exists();
			break;
		case 1800721: /* ERR_TRADE_PAY_INSTRUCT_RECORD_DOES_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_trade_pay_instruct_record_does_not_exist();
			break;
		case 1800722: /* ERR_TRADE_PAY_INSTRUCT_RECORD_LOCKED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_trade_pay_instruct_record_locked();
			break;
		case 1800723: /* ERR_TRADE_UNIT_ADJ_REQ_FOR_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_trade_unit_adj_req_for_account();
			break;
		case 1800724: /* ERR_TRADEADJUST_RECORDS_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_tradeadjust_records_exists();
			break;
		case 1800725: /* ERR_TRADEDATE_FUNDCLASS_BLANK */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_tradedate_fundclass_blank();
			break;
		case 1800726: /* ERR_TRADING_TIME_AGGR */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_trading_time_aggr();
			break;
		case 1800727: /* ERR_TRADING_TIME_CLIENT_CUT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_trading_time_client_cut();
			break;
		case 1800728: /* ERR_TRANS_CLEARING_SETTLE_REC_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_trans_clearing_settle_rec_exists();
			break;
		case 1800729: /* ERR_TRANS_MODIFIED_UNABLE_SETTLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_trans_modified_unable_settle();
			break;
		case 1800730: /* ERR_TRANS_MUST_BE_VERIFIED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_trans_must_be_verified();
			break;
		case 1800731: /* ERR_TRANS_NOT_ALLOWED_DURING_SETTLMENTPHASE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_trans_not_allowed_during_settlmentphase();
			break;
		case 1800732: /* ERR_TRANS_NUM_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_trans_num_exists();
			break;
		case 1800733: /* ERR_TRANS_NUM_MANDATORY */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_trans_num_mandatory();
			break;
		case 1800734: /* ERR_TRANS_NUM_OR_ACCT_REQUIRED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_trans_num_or_acct_required();
			break;
		case 1800735: /* ERR_TRANS_TYPE_REQUIRED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_trans_type_required();
			break;
		case 1800736: /* ERR_TRANSACTION_CANCELED_552 */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_transaction_canceled_552();
			break;
		case 1800737: /* ERR_TRANSACTION_CANNOT_BE_CANCELLED_BEFORE_NIGHT_RUN */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_transaction_cannot_be_cancelled_before_night_run();
			break;
		case 1800738: /* ERR_TRANSACTION_MORE_THAN_ONE_SHAREHOLDER */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_transaction_more_than_one_shareholder();
			break;
		case 1800739: /* ERR_TRANSACTION_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_transaction_not_found();
			break;
		case 1800740: /* ERR_TRANSACTION_PROCESSED_550 */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_transaction_processed_550();
			break;
		case 1800741: /* ERR_TRANSACTION_TYPE_INVALID */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_transaction_type_invalid();
			break;
		case 1800742: /* ERR_TRANSFER_ACCOUNT_PURGED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_transfer_account_purged();
			break;
		case 1800743: /* ERR_TRANSFER_DETAIL_RECORD_LOCKED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_transfer_detail_record_locked();
			break;
		case 1800744: /* ERR_TRANSFER_DETAIL_RECORD_NOT_AVAILABLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_transfer_detail_record_not_available();
			break;
		case 1800745: /* ERR_TRANSFER_NOT_BUY_OR_SELL */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_transfer_not_buy_or_sell();
			break;
		case 1800746: /* ERR_TRANSFER_TRACK_DEL_IF_OUTSTANDING */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_transfer_track_del_if_outstanding();
			break;
		case 1800747: /* ERR_TRANSFER_TRACK_HAS_NONOUTSTANDING */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_transfer_track_has_nonoutstanding();
			break;
		case 1800748: /* ERR_TRANSIT_NO_EXCEEDS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_transit_no_exceeds();
			break;
		case 1800749: /* ERR_TRANSIT_NUMBER_MUST_BE_ENTERED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_transit_number_must_be_entered();
			break;
		case 1800750: /* ERR_TRANSNUM_ALREADY_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_transnum_already_exists();
			break;
		case 1800751: /* ERR_TRANSPENDING_MUST_BE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_transpending_must_be();
			break;
		case 1800752: /* ERR_TRANSTYPE_RC_REQUIRES_FUNDCLASS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_transtype_rc_requires_fundclass();
			break;
		case 1800753: /* ERR_TRXR_CANCEL_FAILED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_trxr_cancel_failed();
			break;
		case 1800754: /* ERR_TXN_CANNOT_EXIST_AFTER_DECADE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_txn_cannot_exist_after_decade();
			break;
		case 1800755: /* ERR_TXN_EXIST_AFTER_CLOSING_DECADE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_txn_exist_after_closing_decade();
			break;
		case 1800756: /* ERR_TYPE_TRANS_NOT_SUPPORT_FAMILY */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_type_trans_not_support_family();
			break;
		case 1800757: /* ERR_UNABLE_ASSIGN_CONNUM */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_unable_assign_connum();
			break;
		case 1800758: /* ERR_UNABLE_MODIFY_COT_ACCT_CONTRACT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_unable_modify_cot_acct_contract();
			break;
		case 1800759: /* ERR_UNABLE_TO_ADD_ESOP_REC */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_unable_to_add_esop_rec();
			break;
		case 1800760: /* ERR_UNABLE_TO_ADD_PENSION_RECORD */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_unable_to_add_pension_record();
			break;
		case 1800761: /* ERR_UNABLE_TO_ADD_RECORD_ACCOUNT_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_unable_to_add_record_account_exists();
			break;
		case 1800762: /* ERR_UNABLE_TO_ADD_RECORD_ADDRESS_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_unable_to_add_record_address_exists();
			break;
		case 1800763: /* ERR_UNABLE_TO_ADD_RECORD_SHAREHOLDER_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_unable_to_add_record_shareholder_exists();
			break;
		case 1800764: /* ERR_UNABLE_TO_DELETE_ENTITY */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_unable_to_delete_entity();
			break;
		case 1800765: /* ERR_UNABLE_TO_DELETE_LAST_ADDRESS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_unable_to_delete_last_address();
			break;
		case 1800766: /* ERR_UNABLE_TO_DELETE_RECORD */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_unable_to_delete_record();
			break;
		case 1800767: /* ERR_UNABLE_TO_MOD_PAC_INDEX_RID_DIFF */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_unable_to_mod_pac_index_rid_diff();
			break;
		case 1800768: /* ERR_UNABLE_TO_MODIFY_ACCTREGDETAILS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_unable_to_modify_acctregdetails();
			break;
		case 1800769: /* ERR_UNABLE_TO_MODIFY_ENTITY */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_unable_to_modify_entity();
			break;
		case 1800770: /* ERR_UNABLE_TO_MODIFY_RECORD */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_unable_to_modify_record();
			break;
		case 1800771: /* ERR_UNABLE_TO_UPDATE_RECORD */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_unable_to_update_record();
			break;
		case 1800772: /* ERR_UNISSUED_CERT_UNIT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_unissued_cert_unit_exist();
			break;
		case 1800773: /* ERR_UNITDETL_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_unitdetl_not_found();
			break;
		case 1800774: /* ERR_UNITS_NOT_ALLOWED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_units_not_allowed();
			break;
		case 1800775: /* ERR_UNKNOW_RESPONSE_TYPE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_unknow_response_type();
			break;
		case 1800776: /* ERR_UNKNOWN_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_unknown_account();
			break;
		case 1800777: /* ERR_UNKNOWN_ERROR */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_unknown_error();
			break;
		case 1800778: /* ERR_UNKNOWN_FTP_READ_ERROR */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_unknown_ftp_read_error();
			break;
		case 1800779: /* ERR_UNKNOWN_RESPONSE_TYPE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_unknown_response_type();
			break;
		case 1800780: /* ERR_UNKNOWN_SCHED_USER_INTERFACE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_unknown_sched_user_interface();
			break;
		case 1800781: /* ERR_UNKNOWN_START_DATE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_unknown_start_date();
			break;
		case 1800782: /* ERR_UNSETTLE_CANNOT_CANCEL_FOR_DIVIDEND_FUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_unsettle_cannot_cancel_for_dividend_fund();
			break;
		case 1800783: /* ERR_USER_ACCESS_RECORD_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_user_access_record_not_found();
			break;
		case 1800784: /* ERR_USER_BATCH_ISNOT_ACTIVE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_user_batch_isnot_active();
			break;
		case 1800785: /* ERR_USER_CANNOT_ACCESS_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_user_cannot_access_account();
			break;
		case 1800786: /* ERR_USER_DO_NOT_HAVE_ACCESS_TO_DESKTOP */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_user_do_not_have_access_to_desktop();
			break;
		case 1800787: /* ERR_USER_DOES_NOT_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_user_does_not_exists();
			break;
		case 1800788: /* ERR_USER_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_user_exists();
			break;
		case 1800789: /* ERR_USER_ID_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_user_id_exist();
			break;
		case 1800790: /* ERR_USER_ID_NEDEED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_user_id_nedeed();
			break;
		case 1800791: /* ERR_USER_STATUS_IS_INACTIVE_IN_COMPANY_DB */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_user_status_is_inactive_in_company_db();
			break;
		case 1800792: /* ERR_USERTYPE_DOES_NOT_HAVE_ACCESS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_usertype_does_not_have_access();
			break;
		case 1800793: /* ERR_VALUATION_SCHEDULE_GROUP_FUND_SETUP */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_valuation_schedule_group_fund_setup();
			break;
		case 1800794: /* ERR_VERIFY_REQUEST_RECORD_LOCKED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_verify_request_record_locked();
			break;
		case 1800795: /* ERR_VERIFY_REQUEST_RECORD_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_verify_request_record_not_exist();
			break;
		case 1800796: /* ERR_VERIFY_REQUEST_RUN_MODE_NOT_VALID */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_verify_request_run_mode_not_valid();
			break;
		case 1800797: /* ERR_VERIFY_REQUEST_VERIFY_BLANK_LINKID */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_verify_request_verify_blank_linkid();
			break;
		case 1800798: /* ERR_VERIFY_REQUEST_VERIFY_BLANK_UUID */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_verify_request_verify_blank_uuid();
			break;
		case 1800799: /* ERR_VERIFY_REQUEST_VERIFY_CATEGORY_NOT_VALID */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_verify_request_verify_category_not_valid();
			break;
		case 1800800: /* ERR_VERIFY_REQUEST_VERIFY_LEVEL_NOT_VALID */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_verify_request_verify_level_not_valid();
			break;
		case 1800801: /* ERR_VERSION_NUM_DO_NOT_MATCH */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_version_num_do_not_match();
			break;
		case 1800802: /* ERR_VIEW_TIMEOUT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_view_timeout();
			break;
		case 1800803: /* ERR_WARNCODE_TABLE_NOT_AVAIL */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_warncode_table_not_avail();
			break;
		case 1800804: /* ERR_WHEREUSE_MUST_BE_01_03 */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_whereuse_must_be_01_03();
			break;
		case 1800805: /* ERR_WIRE_ORDER_REDEMP_NOT_ALLOW */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_wire_order_redemp_not_allow();
			break;
		case 1800806: /* ERR_WITHOUT_FULL_REDEMPTION */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_without_full_redemption();
			break;
		case 1800807: /* ERR_WRONG_BANK_VERSION */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_wrong_bank_version();
			break;
		case 1800808: /* ERR_WRONG_BANKENTITY */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_wrong_bankentity();
			break;
		case 1800809: /* ERR_WRONG_DISTRIBUTION_VERSION */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_wrong_distribution_version();
			break;
		case 1800810: /* ERR_WRONG_LAST_BANKTYPE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_wrong_last_banktype();
			break;
		case 1800811: /* ERR_WRONG_SHRHOLDER_VERSION */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_wrong_shrholder_version();
			break;
		case 1800812: /* ERR_WRONG_TRANS_PENDING */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_wrong_trans_pending();
			break;
		case 1800813: /* IFASTDBRKR_ALREADY_LOGGED_ON */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_already_logged_on();
			break;
		case 1800814: /* IFASTDBRKR_CND_VERSION */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_cnd_version();
			break;
		case 1800815: /* IFASTDBRKR_ERR_ACCT_BALANCE_BELOW_ZERO */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_acct_balance_below_zero();
			break;
		case 1800816: /* IFASTDBRKR_ERR_ACCT_CERT_UNIT_NOT_ENOUGH */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_acct_cert_unit_not_enough();
			break;
		case 1800817: /* IFASTDBRKR_ERR_ACCT_CONTROL_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_acct_control_exists();
			break;
		case 1800818: /* IFASTDBRKR_ERR_ACCT_CONTROL_NOT_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_acct_control_not_exists();
			break;
		case 1800819: /* IFASTDBRKR_ERR_ACCT_CONTROL_UNABLE_TO_MODIFY */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_acct_control_unable_to_modify();
			break;
		case 1800820: /* IFASTDBRKR_ERR_ACCT_NOT_ACTIVE */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_acct_not_active();
			break;
		case 1800821: /* IFASTDBRKR_ERR_ACCT_VALUE_DOES_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_acct_value_does_not_exist();
			break;
		case 1800822: /* IFASTDBRKR_ERR_CANCEL_NOTIONAL_DISTRIB_DSC */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_cancel_notional_distrib_dsc();
			break;
		case 1800823: /* IFASTDBRKR_ERR_CREATE_POST_ADJUSTMENT_DIV */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_create_post_adjustment_div();
			break;
		case 1800824: /* IFASTDBRKR_ERR_FUND_SCHED_VALN_GROUP_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_fund_sched_valn_group_not_found();
			break;
		case 1800825: /* IFASTDBRKR_ERR_GIC_DOES_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_gic_does_not_exist();
			break;
		case 1800826: /* IFASTDBRKR_ERR_GIC_MATURED */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_gic_matured();
			break;
		case 1800827: /* IFASTDBRKR_ERR_GIC_PURCHASE_REDUCED */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_gic_purchase_reduced();
			break;
		case 1800828: /* IFASTDBRKR_ERR_INSUFFICIENT_UNITS */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_insufficient_units();
			break;
		case 1800829: /* IFASTDBRKR_ERR_INSUFFICIENT_UNITS_CANCEL */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_insufficient_units_cancel();
			break;
		case 1800830: /* IFASTDBRKR_ERR_INSUFFICIENT_UNITS_NEG_ADJ */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_insufficient_units_neg_adj();
			break;
		case 1800831: /* IFASTDBRKR_ERR_INVENTORY_BALANCE_NEGATIVE */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_inventory_balance_negative();
			break;
		case 1800832: /* IFASTDBRKR_ERR_INVENTORY_DOES_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_inventory_does_not_exist();
			break;
		case 1800833: /* IFASTDBRKR_ERR_INVSUMM_ID_TO_NOT_PASSED */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_invsumm_id_to_not_passed();
			break;
		case 1800834: /* IFASTDBRKR_ERR_NIGHTCYCLE_ID_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_nightcycle_id_not_found();
			break;
		case 1800835: /* IFASTDBRKR_ERR_NO_FAMILY_CODE_SHRHOLDER */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_no_family_code_shrholder();
			break;
		case 1800836: /* IFASTDBRKR_ERR_NO_FUND_VALUATION_RECORD */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_no_fund_valuation_record();
			break;
		case 1800837: /* IFASTDBRKR_ERR_NO_INVSUMM_ID_RECORD */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_no_invsumm_id_record();
			break;
		case 1800838: /* IFASTDBRKR_ERR_NO_LLPWTHDRWL_RECORD_DEACTIV */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_no_llpwthdrwl_record_deactiv();
			break;
		case 1800839: /* IFASTDBRKR_ERR_NO_PERM_CANCEL_NOTIONAL_DISTRIB */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_no_perm_cancel_notional_distrib();
			break;
		case 1800840: /* IFASTDBRKR_ERR_REVERSE_INVENTORY_UNITS */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_reverse_inventory_units();
			break;
		case 1800841: /* IFASTDBRKR_ERR_TAX_JURIS_SHRHOLDER_BLANK */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_tax_juris_shrholder_blank();
			break;
		case 1800842: /* IFASTDBRKR_ERR_TRACE_NO_TO_NOT_PASSED */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_trace_no_to_not_passed();
			break;
		case 1800843: /* IFASTDBRKR_ERR_TRAN_ACCT_NOT_ACTIVE */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_tran_acct_not_active();
			break;
		case 1800844: /* IFASTDBRKR_ERR_TRANS_DETL_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_trans_detl_not_found();
			break;
		case 1800845: /* IFASTDBRKR_ERR_TXN_PERPETUAL_DSC */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_txn_perpetual_dsc();
			break;
		case 1800846: /* IFASTDBRKR_ERR_TXN_REDUCED_ALREADY */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_txn_reduced_already();
			break;
		case 1800847: /* IFASTDBRKR_ERR_UNKNOWN_FUNCTION_UPDATE */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_unknown_function_update();
			break;
		case 1800848: /* IFASTDBRKR_ERR_UPDATE_PDSC_INFO */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_update_pdsc_info();
			break;
		case 1800849: /* IFASTDBRKR_ERR_UPDATE_PERPETUAL_DSC_INFO */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_update_perpetual_dsc_info();
			break;
		case 1800850: /* IFASTDBRKR_ERR_UPDATING_LLPWTHDRWL_TABLE */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_updating_llpwthdrwl_table();
			break;
		case 1800851: /* IFASTDBRKR_ERR_USERDEFMAT_BLANK */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_userdefmat_blank();
			break;
		case 1800852: /* IFASTDBRKR_ERR_USERDEFMAT_DATE_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_userdefmat_date_exists();
			break;
		case 1800853: /* IFASTDBRKR_ERR_USERDEFMAT_GREATER_THAN_LEGAL */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_userdefmat_greater_than_legal();
			break;
		case 1800854: /* IFASTDBRKR_ERR_USERDEFMAT_RECORD_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_err_userdefmat_record_not_found();
			break;
		case 1800855: /* IFASTDBRKR_INVALID_WIDE_CHARACTER */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_invalid_wide_character();
			break;
		case 1800856: /* IFASTDBRKR_NOT_LOGGED_ON */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_not_logged_on();
			break;
		case 1800857: /* IFASTDBRKR_SEND_FAILED */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_send_failed();
			break;
		case 1800858: /* IFASTDBRKR_TRANS_FAILED */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_trans_failed();
			break;
		case 1800859: /* IFASTDBRKR_UNEXPECTED_END_OF_STREAM_FILE */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_unexpected_end_of_stream_file();
			break;
		case 1800860: /* IFASTDBRKR_UNKNOWN_ERROR */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_unknown_error();
			break;
		case 1800861: /* IFASTDBRKR_VMREQ_FAILED */
			conditionObj = new CIFast_IFast_ifastdbrkr_ifastdbrkr_vmreq_failed();
			break;
		case 1800862: /* PWD_RECENTLY_USED */
			conditionObj = new CIFast_IFast_ifastdbrkr_pwd_recently_used();
			break;
		case 1800863: /* WARN_RESP_TRANSACTION_AMT_EQ_LESS_FIFTHY_THSND */
			conditionObj = new CIFast_IFast_ifastdbrkr_warn_resp_transaction_amt_eq_less_fifthy_thsnd();
			break;
		case 1800864: /* WARN_STOP_REASON_DECEASED_SYSTEM */
			conditionObj = new CIFast_IFast_ifastdbrkr_warn_stop_reason_deceased_system();
			break;
		case 1800865: /* WARN_STOP_REASON_MISSING_SYSTEM */
			conditionObj = new CIFast_IFast_ifastdbrkr_warn_stop_reason_missing_system();
			break;
		case 1800866: /* WARN_STOP_REASON_STOPFLAGS_DECESED_REMOVED */
			conditionObj = new CIFast_IFast_ifastdbrkr_warn_stop_reason_stopflags_decesed_removed();
			break;
		case 1800867: /* WARN_STOP_REASON_STOPFLAGS_KYC_REMOVED */
			conditionObj = new CIFast_IFast_ifastdbrkr_warn_stop_reason_stopflags_kyc_removed();
			break;
		case 1800868: /* ERR_TRADE_DOES_NOT_BELONG_TO_EXISTING_FUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_trade_does_not_belong_to_existing_fund();
			break;
		case 1800869: /* ERR_ANNUITANT_AGE_BELOW_MINIMUM_REQUIREMENT_PER_CONTRACT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_annuitant_age_below_minimum_requirement_per_contract();
			break;
		case 1800870: /* ERR_CONTRACT_TYPE_IS_NOT_FOUND_FOR_THIS_ACCOUNT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_contract_type_is_not_found_for_this_account();
			break;
		case 1800871: /* ERR_CANCEL_ALL_TRANS_OR_CHANGE_TRADEDATE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_cancel_all_trans_or_change_tradedate();
			break;
		case 1800872: /* ERR_TRADE_ALREADY_VERIFIED */
            conditionObj = new CIFast_IFast_IFast_ifastdbrkr_err_trade_already_verified();
			break;
		case 1800877: /* ERR_FUND_CLASS_IS_NOT_LINKED_TO_CURRENT_ACTIVE_AMS_MODEL */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_Fund_class_is_not_linked_to_current_active_AMS_model();
			break;
		case 1800878: /* ERR_PAYENTITY_ALREADY_STOPDATED added for INC0031322*/
			conditionObj = new CIFast_IFast_ifastdbrkr_err_payentity_already_stopDated();
			break;
		case 1800879: /* ERR_ERJD_EXISTS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_erjd_exists();
			break;
		case 1800880: /* ERR_ALLOCATION_NOT_SUPPORT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_allocation_not_support();
			break;
		case 1800881: /* ERR_LINK_TYPE_IS_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_link_type_is_not_found();
			break;
		case 1800882: /* ERR_DBRKR_DILUTION_LINK_ID_DOES_NOT_EXIST */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_dilution_link_id_does_not_exist();
			break;
		case 1800883: /* ERR_DBRKR_FUND_SUSPENDED_NO_TRANSACTIONS_ALLOWED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_fund_suspensed_no_transactions_allowed();
			break;
		case 1800884: /* ERR_DBRKR_REDEMPTIONS_SUSPENDED_LIQUIDITY_MEASURE */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_redemptions_suspended_liquidity_measure();
			break;
		case 1800885: /* ERR_DBRKR_RDSP_CANNOT_CANCEL_MONEY_IN_BEFORE_MONEY_OUT */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_rdsp_cannot_cancel_money_in_before_money_out();
			break;
		case 1800886: /* ERR_DBRKR_RDSP_CANNOT_CANCEL_RECONCILED_EXTERNAL_TRANSFER_IN */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_rdsp_cannot_cancel_reconciled_external_transfer_in();
			break;
		case 1800887: /* ERR_DBRKR_RDSP_CANNOT_CANCEL_REPORTED_EXTERNAL_TRANSFER_IN */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_rdsp_cannot_cancel_reported_external_transfer_in();
			break;
		case 1900001: /* ERR_FTP_OPEN_FILE_FAILED */
			conditionObj = new CIFast_IFast_ifastgui_err_ftp_open_file_failed();
			break;
		case 1900002: /* ERR_NO_SETTELMENT_CURR_AVL */
			conditionObj = new CIFast_IFast_ifastgui_err_no_settelment_curr_avl();
			break;
		case 1900003: /* ERR_UNKNOWN_FTP_OPEN_FILE_ERROR */
			conditionObj = new CIFast_IFast_ifastgui_err_unknown_ftp_open_file_error();
			break;
		case 1900004: /* GUI_AWD_EXCEPTION */
			conditionObj = new CIFast_IFast_ifastgui_gui_awd_exception();
			break;
		case 1900005: /* GUI_AWD_FAILED_UPDATE_OR_CREATE */
			conditionObj = new CIFast_IFast_ifastgui_gui_awd_failed_update_or_create();
			break;
		case 1900006: /* GUI_AWD_INVALID_MAPPED_EVENT */
			conditionObj = new CIFast_IFast_ifastgui_gui_awd_invalid_mapped_event();
			break;
		case 1900007: /* GUI_AWD_LOOKUP_ERROR */
			conditionObj = new CIFast_IFast_ifastgui_gui_awd_lookup_error();
			break;
		case 1900008: /* GUI_AWD_MGMCO_ENTRY_MISSING */
			conditionObj = new CIFast_IFast_ifastgui_gui_awd_mgmco_entry_missing();
			break;
		case 1900009: /* GUI_AWD_MGMCO_TABLE_MISSING */
			conditionObj = new CIFast_IFast_ifastgui_gui_awd_mgmco_table_missing();
			break;
		case 1900010: /* GUI_AWD_NO_SESSION */
			conditionObj = new CIFast_IFast_ifastgui_gui_awd_no_session();
			break;
		case 1900011: /* GUI_AWD_NODATA */
			conditionObj = new CIFast_IFast_ifastgui_gui_awd_nodata();
			break;
		case 1900012: /* GUI_AWD_NOT_LOGGED_ON */
			conditionObj = new CIFast_IFast_ifastgui_gui_awd_not_logged_on();
			break;
		case 1900013: /* GUI_AWD_NOT_SETUP */
			conditionObj = new CIFast_IFast_ifastgui_gui_awd_not_setup();
			break;
		case 1900014: /* GUI_AWD_SEARCH_CRITERIA_INVALID */
			conditionObj = new CIFast_IFast_ifastgui_gui_awd_search_criteria_invalid();
			break;
		case 1900015: /* GUI_AWD_SYSTEM_CHANGED */
			conditionObj = new CIFast_IFast_ifastgui_gui_awd_system_changed();
			break;
		case 1900016: /* GUI_AWD_SYSTEM_ERROR */
			conditionObj = new CIFast_IFast_ifastgui_gui_awd_system_error();
			break;
		case 1900017: /* GUI_ENCORR_ALREADY_ACTIVE */
			conditionObj = new CIFast_IFast_ifastgui_gui_encorr_already_active();
			break;
		case 1900018: /* GUI_ENCORR_ERROR_MALLOC */
			conditionObj = new CIFast_IFast_ifastgui_gui_encorr_error_malloc();
			break;
		case 1900019: /* GUI_ENCORR_OLE_ERROR */
			conditionObj = new CIFast_IFast_ifastgui_gui_encorr_ole_error();
			break;
		case 1900020: /* GUI_ERR_AWD_PROFILE_REQUIRED */
			conditionObj = new CIFast_IFast_ifastgui_gui_err_awd_profile_required();
			break;
		case 1900021: /* GUI_ERR_COMMAND_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastgui_gui_err_command_not_found();
			break;
		case 1900022: /* GUI_ERR_DATA_NOT_FOUND */
			conditionObj = new CIFast_IFast_ifastgui_gui_err_data_not_found();
			break;
		case 1900023: /* GUI_ERR_DIALOG_CREATE_FAILED */
			conditionObj = new CIFast_IFast_ifastgui_gui_err_dialog_create_failed();
			break;
		case 1900024: /* GUI_ERR_DOMODAL_FAILED */
			conditionObj = new CIFast_IFast_ifastgui_gui_err_domodal_failed();
			break;
		case 1900025: /* GUI_ERR_INVALID_FIELD_ENTRY */
			conditionObj = new CIFast_IFast_ifastgui_gui_err_invalid_field_entry();
			break;
		case 1900026: /* GUI_ERR_NOT_PROFILE */
			conditionObj = new CIFast_IFast_ifastgui_gui_err_not_profile();
			break;
		case 1900027: /* GUI_ERR_PROFILE_SELECTION_FAILED */
			conditionObj = new CIFast_IFast_ifastgui_gui_err_profile_selection_failed();
			break;
		case 1900028: /* GUI_ERR_UNKNOWN_EXCEPTION */
			conditionObj = new CIFast_IFast_ifastgui_gui_err_unknown_exception();
			break;
		case 1900029: /* GUI_FORMS_ALREADY_ACTIVE */
			conditionObj = new CIFast_IFast_ifastgui_gui_forms_already_active();
			break;
		case 1900030: /* GUI_FORMS_ERROR_MALLOC */
			conditionObj = new CIFast_IFast_ifastgui_gui_forms_error_malloc();
			break;
		case 1900031: /* GUI_FORMS_OLE_ERROR */
			conditionObj = new CIFast_IFast_ifastgui_gui_forms_ole_error();
			break;
		case 1900032: /* GUI_INVALID_CONTRACT_TYPE */
			conditionObj = new CIFast_IFast_ifastgui_gui_invalid_contract_type();
			break;
		case 1900033: /* GUI_INVALID_POLICY */
			conditionObj = new CIFast_IFast_ifastgui_gui_invalid_policy();
			break;
		case 1900034: /* GUI_MGMTCO_ERR_NO_MANAGEMENT_COMPANIES_FOUND */
			conditionObj = new CIFast_IFast_ifastgui_gui_mgmtco_err_no_management_companies_found();
			break;
		case 1900035: /* GUI_NEW_PASSWORD_CONFIRMATION_NO_MATCH */
			conditionObj = new CIFast_IFast_ifastgui_gui_new_password_confirmation_no_match();
			break;
		case 1900036: /* GUI_NEW_PASSWORD_TOO_SIMPLE */
			conditionObj = new CIFast_IFast_ifastgui_gui_new_password_too_simple();
			break;
		case 1900037: /* GUI_NO_DESCRIPTION_ENTERED */
			conditionObj = new CIFast_IFast_ifastgui_gui_no_description_entered();
			break;
		case 1900038: /* GUI_NO_ENTITY_IN_LIST */
			conditionObj = new CIFast_IFast_ifastgui_gui_no_entity_in_list();
			break;
		case 1900039: /* GUI_NO_FIRE_FIGHTER_ID_ENTERED */
			conditionObj = new CIFast_IFast_ifastgui_gui_no_fire_fighter_id_entered();
			break;
		case 1900040: /* GUI_NO_INCIDENT_NUMBER_ENTERED */
			conditionObj = new CIFast_IFast_ifastgui_gui_no_incident_number_entered();
			break;
		case 1900041: /* GUI_NO_OPERATOR_ID_ENTERED */
			conditionObj = new CIFast_IFast_ifastgui_gui_no_operator_id_entered();
			break;
		case 1900042: /* GUI_NO_PASSWORD_ENTERED */
			conditionObj = new CIFast_IFast_ifastgui_gui_no_password_entered();
			break;
		case 1900043: /* GUI_SEARCH_CRITERIAS_NOT_DEFINED1 */
			conditionObj = new CIFast_IFast_ifastgui_gui_search_criterias_not_defined1();
			break;
		case 1900044: /* GUI_SEARCH_CRITERIAS_NOT_DEFINED2 */
			conditionObj = new CIFast_IFast_ifastgui_gui_search_criterias_not_defined2();
			break;
		case 1900045: /* GUI_SEARCH_CRITERIAS_NOT_DEFINED3 */
			conditionObj = new CIFast_IFast_ifastgui_gui_search_criterias_not_defined3();
			break;
		case 1900046: /* GUI_SEARCH_ENCORR_DISPATCH */
			conditionObj = new CIFast_IFast_ifastgui_gui_search_encorr_dispatch();
			break;
		case 1900047: /* GUI_SEARCH_ENCORR_NAMES */
			conditionObj = new CIFast_IFast_ifastgui_gui_search_encorr_names();
			break;
		case 1900048: /* GUI_SEARCH_FORMS_CLASS */
			conditionObj = new CIFast_IFast_ifastgui_gui_search_forms_class();
			break;
		case 1900049: /* GUI_SEARCH_FORMS_FACTORY */
			conditionObj = new CIFast_IFast_ifastgui_gui_search_forms_factory();
			break;
		case 1900050: /* GUI_SEARCH_FORMS_ID */
			conditionObj = new CIFast_IFast_ifastgui_gui_search_forms_id();
			break;
		case 1900051: /* GUI_SECURITY_VIOLATION */
			conditionObj = new CIFast_IFast_ifastgui_gui_security_violation();
			break;
		case 1900052: /* GUI_WRAPUP_ERR_MUST_ENTER_BATC */
			conditionObj = new CIFast_IFast_ifastgui_gui_wrapup_err_must_enter_batc();
			break;
		case 1900053: /* GUI_WRAPUP_ERR_MUST_ENTER_STAT */
			conditionObj = new CIFast_IFast_ifastgui_gui_wrapup_err_must_enter_stat();
			break;
		case 1900054: /* GUI_WRAPUP_ERR_MUST_ENTER_UNIT */
			conditionObj = new CIFast_IFast_ifastgui_gui_wrapup_err_must_enter_unit();
			break;
		case 1900055: /* GUI_WRAPUP_ERR_MUST_ENTER_WRKT */
			conditionObj = new CIFast_IFast_ifastgui_gui_wrapup_err_must_enter_wrkt();
			break;
		case 1900056: /* GUI_WRAPUP_ERR_UNIT_CHANGED */
			conditionObj = new CIFast_IFast_ifastgui_gui_wrapup_err_unit_changed();
			break;
		case 1900057: /* IFASTGUI_CND_VERSION */
			conditionObj = new CIFast_IFast_ifastgui_ifastgui_cnd_version();
			break;
		case 1900058: /* WARN_BACK_DATE_TRADE_NOT_ALLOWED_BEFORE_LE */
			conditionObj = new CIFast_IFast_ifastgui_warn_back_date_trade_not_allowed_before_le();
			break;
		case 1900059: /* GUI_ERR_PROFILE_SELECTION_FAILED_IDI */
			conditionObj = new CIFast_IFast_ifastgui_gui_err_profile_selection_failed_idi();
			break;
		case 2000001: /* ERR_NO_PERMISSION_FOR_TRADE */
			conditionObj = new CIFast_IFast_ifastxparser_err_no_permission_for_trade();
			break;
		case 2000002: /* WARN_AggregatedOrder_Loss */
			conditionObj = new CIFast_IFast_ifastxparser_warn_aggregatedorder_loss();
			break;
		case 2200001: /* ERR_ACCT_HAS_NO_HOLDING */
			conditionObj = new CIFast_IFast_vision_err_acct_has_no_holding();
			break;
		case 2200002: /* ERR_ACTION_UNIDENTIFIABLE */
			conditionObj = new CIFast_IFast_vision_err_action_unidentifiable();
			break;
		case 2200003: /* ERR_INVALID_DATE_FORMAT */
			conditionObj = new CIFast_IFast_vision_err_invalid_date_format();
			break;
		case 2200004: /* ERR_MISSING_USER_WK_ID */
			conditionObj = new CIFast_IFast_vision_err_missing_user_wk_id();
			break;
		case 2200005: /* ERR_NO_DATA_FOR_CRT_THREAD */
			conditionObj = new CIFast_IFast_vision_err_no_data_for_crt_thread();
			break;
		case 2200006: /* ERR_NO_DATA_FOUND */
			conditionObj = new CIFast_IFast_vision_err_no_data_found();
			break;
		case 2200007: /* ERR_NO_INITIALIZED_SERVICE */
			conditionObj = new CIFast_IFast_vision_err_no_initialized_service();
			break;
		case 2200008: /* ERR_NO_PASSWORD */
			conditionObj = new CIFast_IFast_vision_err_no_password();
			break;
		case 2200009: /* ERR_NO_SEARCH_CRITERIA */
			conditionObj = new CIFast_IFast_vision_err_no_search_criteria();
			break;
		case 2200010: /* ERR_NO_SEARCH_USING */
			conditionObj = new CIFast_IFast_vision_err_no_search_using();
			break;
		case 2200011: /* ERR_NO_SEARCH_VALUE */
			conditionObj = new CIFast_IFast_vision_err_no_search_value();
			break;
		case 2200012: /* ERR_NO_SERVICE_TO_END */
			conditionObj = new CIFast_IFast_vision_err_no_service_to_end();
			break;
		case 2200013: /* ERR_NO_USER_SESSION */
			conditionObj = new CIFast_IFast_vision_err_no_user_session();
			break;
		case 2200014: /* ERR_NO_WORK_SESSION */
			conditionObj = new CIFast_IFast_vision_err_no_work_session();
			break;
		case 2200015: /* ERR_NOT_ABLE_TO_PERFORM */
			conditionObj = new CIFast_IFast_vision_err_not_able_to_perform();
			break;
		case 2200016: /* ERR_PARSING_ERROR */
			conditionObj = new CIFast_IFast_vision_err_parsing_error();
			break;
		case 2200017: /* ERR_REQUEST_UNIDENTIFIABLE */
			conditionObj = new CIFast_IFast_vision_err_request_unidentifiable();
			break;
		case 2200018: /* ERR_SERVER_RESPONSE */
			conditionObj = new CIFast_IFast_vision_err_server_response();
			break;
		case 2200019: /* ERR_UNKNOWN_SERVICE */
			conditionObj = new CIFast_IFast_vision_err_unknown_service();
			break;
		case 2200020: /* VISION_CND_VERSION */
			conditionObj = new CIFast_IFast_vision_vision_cnd_version();
			break;
        default:
			//assert(0);
			break;
	}

	return conditionObj;
};

CConditionObject* CConditionBuilder::CreateIFastInfrastructureConditionObject(long conditionId) 
{
	CConditionObject* conditionObj = NULL;

	switch(conditionId)
	{
		case 600001: /* DIAWD23_AWD_EXCEPTION */
			conditionObj = new CIFast_Infrastructure_diawd23_diawd23_awd_exception();
			break;
		case 600002: /* DIAWD23_COMMENT_FAIL */
			conditionObj = new CIFast_Infrastructure_diawd23_diawd23_comment_fail();
			break;
		case 600003: /* DIAWD23_CONNECT_FAIL */
			conditionObj = new CIFast_Infrastructure_diawd23_diawd23_connect_fail();
			break;
		case 600004: /* DIAWD23_CONTAINER_ALREADY_OPEN */
			conditionObj = new CIFast_Infrastructure_diawd23_diawd23_container_already_open();
			break;
		case 600005: /* DIAWD23_CONTAINER_CLOSE_FAIL */
			conditionObj = new CIFast_Infrastructure_diawd23_diawd23_container_close_fail();
			break;
		case 600006: /* DIAWD23_CONTAINER_NOT_CLEAR */
			conditionObj = new CIFast_Infrastructure_diawd23_diawd23_container_not_clear();
			break;
		case 600007: /* DIAWD23_CONTAINER_NOT_OPEN */
			conditionObj = new CIFast_Infrastructure_diawd23_diawd23_container_not_open();
			break;
		case 600009: /* DIAWD23_CREATE_AWDOBJ_FAIL */
			conditionObj = new CIFast_Infrastructure_diawd23_diawd23_create_awdobj_fail();
			break;
		case 600011: /* DIAWD23_INIT_COM_FAIL */
			conditionObj = new CIFast_Infrastructure_diawd23_diawd23_init_com_fail();
			break;
		case 600014: /* DIAWD23_OBJECT_LOCKED */
			conditionObj = new CIFast_Infrastructure_diawd23_diawd23_object_locked();
			break;
		case 600015: /* DIAWD23_OLE_ARRAY_FAIL */
			conditionObj = new CIFast_Infrastructure_diawd23_diawd23_ole_array_fail();
			break;
		case 600017: /* DIAWD23_RELATE_FAIL */
			conditionObj = new CIFast_Infrastructure_diawd23_diawd23_relate_fail();
			break;
		case 600018: /* DIAWD23_RETRIEVE_AWDOBJ_FAIL */
			conditionObj = new CIFast_Infrastructure_diawd23_diawd23_retrieve_awdobj_fail();
			break;
		case 600020: /* DIAWD23_UPDATE_AWDOBJ_FAIL */
			conditionObj = new CIFast_Infrastructure_diawd23_diawd23_update_awdobj_fail();
			break;
		case 700001: /* DIAWDI_INVALID_DATE_TIME_PASSED */
			conditionObj = new CIFast_Infrastructure_diawdi_diawdi_invalid_date_time_passed();
			break;
		case 700002: /* DIAWDI_LOAD_MODULE_FAIL */
			conditionObj = new CIFast_Infrastructure_diawdi_diawdi_load_module_fail();
			break;
		case 700004: /* DIAWDI_LOGON_INVALID_NEW_PASSWORD */
			conditionObj = new CIFast_Infrastructure_diawdi_diawdi_logon_invalid_new_password();
			break;
		case 700005: /* DIAWDI_LOGON_INVALID_OPID */
			conditionObj = new CIFast_Infrastructure_diawdi_diawdi_logon_invalid_opid();
			break;
		case 700009: /* DIAWDI_LOGON_OTHER_ERROR */
			conditionObj = new CIFast_Infrastructure_diawdi_diawdi_logon_other_error();
			break;
		case 700010: /* DIAWDI_LOGON_PASSWORD_EXPIRED */
			conditionObj = new CIFast_Infrastructure_diawdi_diawdi_logon_password_expired();
			break;
		case 700011: /* DIAWDI_LOGON_USER_ALREADY_LOGGED_ON */
			conditionObj = new CIFast_Infrastructure_diawdi_diawdi_logon_user_already_logged_on();
			break;
		case 700012: /* DIAWDI_LOGON_USER_DISABLED */
			conditionObj = new CIFast_Infrastructure_diawdi_diawdi_logon_user_disabled();
			break;
		case 800001: /* DICORE_DATE_FORMAT_NOT_RECOGNIZED */
			conditionObj = new CIFast_Infrastructure_dicbocore_dicore_date_format_not_recognized();
			break;
		case 800003: /* ERR_CBE_LABEL_INVALID_FOR_UPDATE */
			conditionObj = new CIFast_Infrastructure_dicbocore_err_cbe_label_invalid_for_update();
			break;
		case 800005: /* ERR_EVENT_MIXING_NOT_ALLOWED */
			conditionObj = new CIFast_Infrastructure_dicbocore_err_event_mixing_not_allowed();
			break;
		case 800007: /* ERR_FIELD_GROUP_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_dicbocore_err_field_group_not_found();
			break;
		case 800009: /* ERR_FIELD_IS_UNDER_MINIMUM_ALLOWED */
			conditionObj = new CIFast_Infrastructure_dicbocore_err_field_is_under_minimum_allowed();
			break;
		case 800010: /* ERR_FIELD_MAX_LEN_EXCEEDED */
			conditionObj = new CIFast_Infrastructure_dicbocore_err_field_max_len_exceeded();
			break;
		case 800011: /* ERR_FIELD_READ_ONLY */
			conditionObj = new CIFast_Infrastructure_dicbocore_err_field_read_only();
			break;
		case 800014: /* ERR_FLD_NOT_VALIDATED */
			conditionObj = new CIFast_Infrastructure_dicbocore_err_fld_not_validated();
			break;
		case 800016: /* ERR_HOLIDAY_FILE */
			conditionObj = new CIFast_Infrastructure_dicbocore_err_holiday_file();
			break;
		case 800017: /* ERR_IMPROPER_CLASS_FIELD_VALID_VALUES */
			conditionObj = new CIFast_Infrastructure_dicbocore_err_improper_class_field_valid_values();
			break;
		case 800018: /* ERR_INCOMPATIBLE_REGISTERED_OBJECTS */
			conditionObj = new CIFast_Infrastructure_dicbocore_err_incompatible_registered_objects();
			break;
		case 800019: /* ERR_INDEX_OUT_OF_RANGE */
			conditionObj = new CIFast_Infrastructure_dicbocore_err_index_out_of_range();
			break;
		case 800022: /* ERR_INVALID_FIELD_TAG */
			conditionObj = new CIFast_Infrastructure_dicbocore_err_invalid_field_tag();
			break;
		case 800023: /* ERR_INVALID_FIELD_TYPE */
			conditionObj = new CIFast_Infrastructure_dicbocore_err_invalid_field_type();
			break;
		case 800024: /* ERR_INVALID_ITERATOR_POSITION */
			conditionObj = new CIFast_Infrastructure_dicbocore_err_invalid_iterator_position();
			break;
		case 800025: /* ERR_INVALID_METHOD_CALL */
			conditionObj = new CIFast_Infrastructure_dicbocore_err_invalid_method_call();
			break;
		case 800026: /* ERR_INVALID_OBJ_POINTER */
			conditionObj = new CIFast_Infrastructure_dicbocore_err_invalid_obj_pointer();
			break;
		case 800033: /* ERR_NO_ADDITIONAL_REPEAT_RECORDS */
			conditionObj = new CIFast_Infrastructure_dicbocore_err_no_additional_repeat_records();
			break;
		case 800035: /* ERR_NO_REGISTERED_OBJECT */
			conditionObj = new CIFast_Infrastructure_dicbocore_err_no_registered_object();
			break;
		case 800036: /* ERR_NO_UPDATES_TO_APPLY */
			conditionObj = new CIFast_Infrastructure_dicbocore_err_no_updates_to_apply();
			break;
		case 800039: /* ERR_OBJECT_COPY_ONLY */
			conditionObj = new CIFast_Infrastructure_dicbocore_err_object_copy_only();
			break;
		case 800040: /* ERR_OBJECT_DOES_NOT_ALLOW_GROUPS */
			conditionObj = new CIFast_Infrastructure_dicbocore_err_object_does_not_allow_groups();
			break;
		case 800041: /* ERR_OBJECT_INVALID_TYPE */
			conditionObj = new CIFast_Infrastructure_dicbocore_err_object_invalid_type();
			break;
		case 800042: /* ERR_OBJECT_NOT_COPYABLE */
			conditionObj = new CIFast_Infrastructure_dicbocore_err_object_not_copyable();
			break;
		case 800045: /* ERR_OBJECT_OWNED_BY_LIST */
			conditionObj = new CIFast_Infrastructure_dicbocore_err_object_owned_by_list();
			break;
		case 800047: /* ERR_OBJECT_PTR_ACCESS_ONLY */
			conditionObj = new CIFast_Infrastructure_dicbocore_err_object_ptr_access_only();
			break;
		case 800049: /* ERR_OBJECT_REQUIRED */
			conditionObj = new CIFast_Infrastructure_dicbocore_err_object_required();
			break;
		case 800051: /* ERR_SEARCH_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_dicbocore_err_search_not_found();
			break;
		case 800052: /* ERR_STRING_EXCEPTION */
			conditionObj = new CIFast_Infrastructure_dicbocore_err_string_exception();
			break;
		case 800053: /* ERR_UNABLE_TO_RETRIEVE_LABEL_DATA */
			conditionObj = new CIFast_Infrastructure_dicbocore_err_unable_to_retrieve_label_data();
			break;
		case 800054: /* ERR_UNKNOWN_EXCEPTION */
			conditionObj = new CIFast_Infrastructure_dicbocore_err_unknown_exception();
			break;
		case 800055: /* ERR_VIEW_MGR */
			conditionObj = new CIFast_Infrastructure_dicbocore_err_view_mgr();
			break;
		case 800056: /* ERR_WORKORDER_CBE_ALREADY_REGISTERED */
			conditionObj = new CIFast_Infrastructure_dicbocore_err_workorder_cbe_already_registered();
			break;
		case 800057: /* ERR_WORKORDER_CBEKEY_DUPLICATED */
			conditionObj = new CIFast_Infrastructure_dicbocore_err_workorder_cbekey_duplicated();
			break;
		case 800058: /* ERR_WORKORDER_CBEKEY_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_dicbocore_err_workorder_cbekey_not_found();
			break;
		case 900003: /* DICORE_BUFFER_SIZE_TOO_SMALL */
			conditionObj = new CIFast_Infrastructure_dicore_dicore_buffer_size_too_small();
			break;
		case 900004: /* DICORE_CANNOT_PERSIST_UNDEFINED_MGR */
			conditionObj = new CIFast_Infrastructure_dicore_dicore_cannot_persist_undefined_mgr();
			break;
		case 900005: /* DICORE_CANNOT_READ_DEFINITION */
			conditionObj = new CIFast_Infrastructure_dicore_dicore_cannot_read_definition();
			break;
		case 900007: /* DICORE_DATAPATH_REG_NOT_DEFINED */
			conditionObj = new CIFast_Infrastructure_dicore_dicore_datapath_reg_not_defined();
			break;
		case 900010: /* DICORE_DELETE_VALUE_FAIL */
			conditionObj = new CIFast_Infrastructure_dicore_dicore_delete_value_fail();
			break;
		case 900011: /* DICORE_DIVIDE_BY_ZERO */
			conditionObj = new CIFast_Infrastructure_dicore_dicore_divide_by_zero();
			break;
		case 900012: /* DICORE_DLL_LOAD_FAIL */
			conditionObj = new CIFast_Infrastructure_dicore_dicore_dll_load_fail();
			break;
		case 900014: /* DICORE_EVENTSEM_OPEN_FAIL */
			conditionObj = new CIFast_Infrastructure_dicore_dicore_eventsem_open_fail();
			break;
		case 900021: /* DICORE_KEY_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_dicore_dicore_key_not_found();
			break;
		case 900024: /* DICORE_MUTEXSEM_OPEN_FAIL */
			conditionObj = new CIFast_Infrastructure_dicore_dicore_mutexsem_open_fail();
			break;
		case 900032: /* DICORE_PARSE_IDI_MISSING_VALUE */
			conditionObj = new CIFast_Infrastructure_dicore_dicore_parse_idi_missing_value();
			break;
		case 900033: /* DICORE_PERSIST_REGISTRY_FAIL */
			conditionObj = new CIFast_Infrastructure_dicore_dicore_persist_registry_fail();
			break;
		case 900034: /* DICORE_PIPE_INIT_FAIL */
			conditionObj = new CIFast_Infrastructure_dicore_dicore_pipe_init_fail();
			break;
		case 900037: /* DICORE_READ_REGISTRY_FAIL */
			conditionObj = new CIFast_Infrastructure_dicore_dicore_read_registry_fail();
			break;
		case 900038: /* DICORE_SAVE_KEY_FAIL */
			conditionObj = new CIFast_Infrastructure_dicore_dicore_save_key_fail();
			break;
		case 900040: /* DICORE_VMAPPREQUEST_FAIL */
			conditionObj = new CIFast_Infrastructure_dicore_dicore_vmapprequest_fail();
			break;
		case 900041: /* DICORE_VMAPPREQUEST_TIMEOUT */
			conditionObj = new CIFast_Infrastructure_dicore_dicore_vmapprequest_timeout();
			break;
		case 900042: /* DICORE_VMCONNECT_FAIL */
			conditionObj = new CIFast_Infrastructure_dicore_dicore_vmconnect_fail();
			break;
		case 900045: /* DICORE_VMNOTIFYWIN_FAIL */
			conditionObj = new CIFast_Infrastructure_dicore_dicore_vmnotifywin_fail();
			break;
		case 900046: /* DICORE_VMREADRESPONSE_FAIL */
			conditionObj = new CIFast_Infrastructure_dicore_dicore_vmreadresponse_fail();
			break;
		case 900047: /* DICORE_VMREQUEST_CALLBACK_CONDITIONEXCEPTION_THROWN */
			conditionObj = new CIFast_Infrastructure_dicore_dicore_vmrequest_callback_conditionexception_thrown();
			break;
		case 900048: /* DICORE_VMREQUEST_CALLBACK_ERROR_CONDITION */
			conditionObj = new CIFast_Infrastructure_dicore_dicore_vmrequest_callback_error_condition();
			break;
		case 900049: /* DICORE_VMREQUEST_CALLBACK_UNKNOWN_EXCEPTION_THROWN */
			conditionObj = new CIFast_Infrastructure_dicore_dicore_vmrequest_callback_unknown_exception_thrown();
			break;
		case 900050: /* DICORE_VMREQUEST_FAIL */
			conditionObj = new CIFast_Infrastructure_dicore_dicore_vmrequest_fail();
			break;
		case 900051: /* DICORE_VMREQUEST_INIT_FAIL */
			conditionObj = new CIFast_Infrastructure_dicore_dicore_vmrequest_init_fail();
			break;
		case 900052: /* DICORE_VMREQUEST_WAIT_FAIL */
			conditionObj = new CIFast_Infrastructure_dicore_dicore_vmrequest_wait_fail();
			break;
		case 900053: /* DILOCAL_JNI_EXCEPTION_CREATEJVM */
			conditionObj = new CIFast_Infrastructure_dicore_dilocal_jni_exception_createjvm();
			break;
		case 900054: /* DILOCAL_JNI_EXCEPTION_EXECUTE */
			conditionObj = new CIFast_Infrastructure_dicore_dilocal_jni_exception_execute();
			break;
		case 900056: /* ERR_AMS_ACCOUNT_TAX_JURISDICTION */
			conditionObj = new CIFast_Infrastructure_dicore_err_ams_account_tax_jurisdiction();
			break;
		case 900057: /* ERR_KYC_DATA_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_dicore_err_kyc_data_not_found();
			break;
		case 900058: /* VIRTUAL_BASE_METHOD_NOT_SUPPORTED */
			conditionObj = new CIFast_Infrastructure_dicore_virtual_base_method_not_supported();
			break;
		case 900059: /* WARN_INPUTDATATYPE_EMPTY */
			conditionObj = new CIFast_Infrastructure_dicore_warn_inputdatatype_empty();
			break;
		case 1000001: /* DIDBRKR_BAD_FORMAT_IN_STREAM_FILE */
			conditionObj = new CIFast_Infrastructure_didbrkr_didbrkr_bad_format_in_stream_file();
			break;
		case 1000002: /* DIDBRKR_CANNOT_ASSIGN_DATA_OBJECTS */
			conditionObj = new CIFast_Infrastructure_didbrkr_didbrkr_cannot_assign_data_objects();
			break;
		case 1000004: /* DIDBRKR_CANT_OPEN_PROPERTIES_FILE */
			conditionObj = new CIFast_Infrastructure_didbrkr_didbrkr_cant_open_properties_file();
			break;
		case 1000005: /* DIDBRKR_CANT_SET_VALUES */
			conditionObj = new CIFast_Infrastructure_didbrkr_didbrkr_cant_set_values();
			break;
		case 1000006: /* DIDBRKR_COMPONENT_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_didbrkr_didbrkr_component_not_found();
			break;
		case 1000007: /* DIDBRKR_DATA_HAS_NO_REPEATS */
			conditionObj = new CIFast_Infrastructure_didbrkr_didbrkr_data_has_no_repeats();
			break;
		case 1000008: /* DIDBRKR_DATASET_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_didbrkr_didbrkr_dataset_not_found();
			break;
		case 1000009: /* DIDBRKR_DUPLICATE_PROPERTIES */
			conditionObj = new CIFast_Infrastructure_didbrkr_didbrkr_duplicate_properties();
			break;
		case 1000010: /* DIDBRKR_ELEMENT_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_didbrkr_didbrkr_element_not_found();
			break;
		case 1000012: /* DIDBRKR_EXTRA_LINES_IN_PROPERTIES_FILE */
			conditionObj = new CIFast_Infrastructure_didbrkr_didbrkr_extra_lines_in_properties_file();
			break;
		case 1000014: /* DIDBRKR_I18N_MASK_FORMAT_ERROR */
			conditionObj = new CIFast_Infrastructure_didbrkr_didbrkr_i18n_mask_format_error();
			break;
		case 1000015: /* DIDBRKR_INDEX_OUT_OF_RANGE */
			conditionObj = new CIFast_Infrastructure_didbrkr_didbrkr_index_out_of_range();
			break;
		case 1000016: /* DIDBRKR_INVALID_LINE_LENGTH */
			conditionObj = new CIFast_Infrastructure_didbrkr_didbrkr_invalid_line_length();
			break;
		case 1000018: /* DIDBRKR_INVALID_REDEFINE */
			conditionObj = new CIFast_Infrastructure_didbrkr_didbrkr_invalid_redefine();
			break;
		case 1000019: /* DIDBRKR_KEY_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_didbrkr_didbrkr_key_not_found();
			break;
		case 1000020: /* DIDBRKR_LOCALE_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_didbrkr_didbrkr_locale_not_found();
			break;
		case 1000022: /* DIDBRKR_NOT_A_DATA_OBJECT */
			conditionObj = new CIFast_Infrastructure_didbrkr_didbrkr_not_a_data_object();
			break;
		case 1000023: /* DIDBRKR_NOT_A_DATAELEMENT_OBJECT */
			conditionObj = new CIFast_Infrastructure_didbrkr_didbrkr_not_a_dataelement_object();
			break;
		case 1000024: /* DIDBRKR_NOT_REPEATABLE */
			conditionObj = new CIFast_Infrastructure_didbrkr_didbrkr_not_repeatable();
			break;
		case 1000025: /* DIDBRKR_PROPERTIES_DONT_MATCH */
			conditionObj = new CIFast_Infrastructure_didbrkr_didbrkr_properties_dont_match();
			break;
		case 1000026: /* DIDBRKR_PROPERTY_DOES_NOT_EXIST */
			conditionObj = new CIFast_Infrastructure_didbrkr_didbrkr_property_does_not_exist();
			break;
		case 1000029: /* DIDBRKR_REDEFINE_HAS_DUPLICATE */
			conditionObj = new CIFast_Infrastructure_didbrkr_didbrkr_redefine_has_duplicate();
			break;
		case 1000030: /* DIDBRKR_REDEFINE_LENGTH_MISMATCH */
			conditionObj = new CIFast_Infrastructure_didbrkr_didbrkr_redefine_length_mismatch();
			break;
		case 1000032: /* DIDBRKR_REPEAT_COUNT_ELEMENT_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_didbrkr_didbrkr_repeat_count_element_not_found();
			break;
		case 1000033: /* DIDBRKR_REPEAT_INDEX_OUT_OF_RANGE */
			conditionObj = new CIFast_Infrastructure_didbrkr_didbrkr_repeat_index_out_of_range();
			break;
		case 1000034: /* DIDBRKR_TARGET_LOCALE_MISSING */
			conditionObj = new CIFast_Infrastructure_didbrkr_didbrkr_target_locale_missing();
			break;
		case 1100001: /* DIODBC_CONNECT_ERROR */
			conditionObj = new CIFast_Infrastructure_disessn_diodbc_connect_error();
			break;
		case 1100003: /* DIODBC_INFO */
			conditionObj = new CIFast_Infrastructure_disessn_diodbc_info();
			break;
		case 1100006: /* DISESSN_CHILD_NOT_REMOVED */
			conditionObj = new CIFast_Infrastructure_disessn_disessn_child_not_removed();
			break;
		case 1100007: /* DISESSN_DEFAULT_LABEL_USED */
			conditionObj = new CIFast_Infrastructure_disessn_disessn_default_label_used();
			break;
		case 1100008: /* DISESSN_UNDEFINED_AWD_PARAMETER */
			conditionObj = new CIFast_Infrastructure_disessn_disessn_undefined_awd_parameter();
			break;
		case 1200001: /* DITA2KDB_A52_INFO_UNAVAIL */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_a52_info_unavail();
			break;
		case 1200002: /* DITA2KDB_A52_REC_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_a52_rec_not_found();
			break;
		case 1200004: /* DITA2KDB_A58_REC_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_a58_rec_not_found();
			break;
		case 1200006: /* DITA2KDB_A87_REC_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_a87_rec_not_found();
			break;
		case 1200007: /* DITA2KDB_A90_INFO_UNAVAIL */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_a90_info_unavail();
			break;
		case 1200008: /* DITA2KDB_A90_REC_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_a90_rec_not_found();
			break;
		case 1200009: /* DITA2KDB_ALREADY_SIGNED_ON */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_already_signed_on();
			break;
		case 1200012: /* DITA2KDB_AUDIT_FILE_BAD_OPEN */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_audit_file_bad_open();
			break;
		case 1200013: /* DITA2KDB_AUDIT_REC_NOT_WRITTEN */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_audit_rec_not_written();
			break;
		case 1200015: /* DITA2KDB_B06_REC_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_b06_rec_not_found();
			break;
		case 1200018: /* DITA2KDB_B15_INFO_UNAVAIL */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_b15_info_unavail();
			break;
		case 1200019: /* DITA2KDB_B15_REC_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_b15_rec_not_found();
			break;
		case 1200023: /* DITA2KDB_CANT_INIT_VIEW_THREAD */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_cant_init_view_thread();
			break;
		case 1200025: /* DITA2KDB_CANT_READ_DATA_FILE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_cant_read_data_file();
			break;
		case 1200026: /* DITA2KDB_CHANGED_BY_DIFF_OPER */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_changed_by_diff_oper();
			break;
		case 1200027: /* DITA2KDB_CHG_REC_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_chg_rec_not_found();
			break;
		case 1200028: /* DITA2KDB_CURR_A79_NOT_DEL */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_curr_a79_not_del();
			break;
		case 1200029: /* DITA2KDB_DATA_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_data_not_found();
			break;
		case 1200030: /* DITA2KDB_DEFAULT_VALUE_USED */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_default_value_used();
			break;
		case 1200031: /* DITA2KDB_DEL_REC_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_del_rec_not_found();
			break;
		case 1200033: /* DITA2KDB_END_OF_DATA */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_end_of_data();
			break;
		case 1200035: /* DITA2KDB_F17_REC_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_f17_rec_not_found();
			break;
		case 1200036: /* DITA2KDB_FAILED_TO_CONNECT_WITH_LOGON_MGR */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_failed_to_connect_with_logon_mgr();
			break;
		case 1200040: /* DITA2KDB_INVALID_ALPHA_CODE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_alpha_code();
			break;
		case 1200045: /* DITA2KDB_INVALID_CERT_NUM */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_cert_num();
			break;
		case 1200049: /* DITA2KDB_INVALID_DATA */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_data();
			break;
		case 1200051: /* DITA2KDB_INVALID_DATE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_date();
			break;
		case 1200053: /* DITA2KDB_INVALID_DEALER_BRANCH */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_dealer_branch();
			break;
		case 1200054: /* DITA2KDB_INVALID_DEALER_NUM */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_dealer_num();
			break;
		case 1200055: /* DITA2KDB_INVALID_DEBIT_CARD */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_debit_card();
			break;
		case 1200056: /* DITA2KDB_INVALID_DEBIT_TYPE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_debit_type();
			break;
		case 1200058: /* DITA2KDB_INVALID_DLR_BRN_SEC */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_dlr_brn_sec();
			break;
		case 1200059: /* DITA2KDB_INVALID_DLR_SUMMARY */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_dlr_summary();
			break;
		case 1200060: /* DITA2KDB_INVALID_DSCS_APPREC */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_dscs_apprec();
			break;
		case 1200061: /* DITA2KDB_INVALID_EXCH_PUR_CANC */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_exch_pur_canc();
			break;
		case 1200064: /* DITA2KDB_INVALID_FID_ACCOUNT */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_fid_account();
			break;
		case 1200065: /* DITA2KDB_INVALID_FRONT_END */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_front_end();
			break;
		case 1200066: /* DITA2KDB_INVALID_FUNCTION_TYPE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_function_type();
			break;
		case 1200071: /* DITA2KDB_INVALID_LOI_NUM */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_loi_num();
			break;
		case 1200075: /* DITA2KDB_INVALID_NET_CHG */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_net_chg();
			break;
		case 1200076: /* DITA2KDB_INVALID_OPER_ID */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_oper_id();
			break;
		case 1200077: /* DITA2KDB_INVALID_PAF_BUCKET */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_paf_bucket();
			break;
		case 1200082: /* DITA2KDB_INVALID_PURCH_CANCEL */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_purch_cancel();
			break;
		case 1200084: /* DITA2KDB_INVALID_REDMPT_CANCEL */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_redmpt_cancel();
			break;
		case 1200086: /* DITA2KDB_INVALID_REIN_SHARES */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_rein_shares();
			break;
		case 1200088: /* DITA2KDB_INVALID_RES_STATE_CODE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_res_state_code();
			break;
		case 1200091: /* DITA2KDB_INVALID_START_YEAR */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_start_year();
			break;
		case 1200093: /* DITA2KDB_INVALID_TRANS_NUM */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_trans_num();
			break;
		case 1200095: /* DITA2KDB_INVALID_YIELD_DATE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_yield_date();
			break;
		case 1200096: /* DITA2KDB_MAX_IO_LIMIT */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_max_io_limit();
			break;
		case 1200099: /* DITA2KDB_NO_A53_DUMMY_REC */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_no_a53_dummy_rec();
			break;
		case 1200100: /* DITA2KDB_NO_A53_FOR_VERIFY_DTE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_no_a53_for_verify_dte();
			break;
		case 1200101: /* DITA2KDB_NO_A56_REC_FOUND */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_no_a56_rec_found();
			break;
		case 1200106: /* DITA2KDB_NO_UPDATE_DETECTED */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_no_update_detected();
			break;
		case 1200107: /* DITA2KDB_NO_UPDATES_TO_APPLY */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_no_updates_to_apply();
			break;
		case 1200108: /* DITA2KDB_NOT_AUTHORIZED */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_not_authorized();
			break;
		case 1200109: /* DITA2KDB_NOT_SIGNED_ON */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_not_signed_on();
			break;
		case 1200111: /* DITA2KDB_OPER_NOT_AUTH_DEALER */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_oper_not_auth_dealer();
			break;
		case 1200112: /* DITA2KDB_OPER_NOT_AUTH_DLR_BR */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_oper_not_auth_dlr_br();
			break;
		case 1200113: /* DITA2KDB_PASSWORD_EXPIRED */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_password_expired();
			break;
		case 1200114: /* DITA2KDB_PASSWORD_TOO_SIMILAR */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_password_too_similar();
			break;
		case 1200115: /* DITA2KDB_POTENTIAL_DUPLICATE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_potential_duplicate();
			break;
		case 1200116: /* DITA2KDB_RECORD_ALREADY_EXIST */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_record_already_exist();
			break;
		case 1200117: /* DITA2KDB_RECORD_UNAVAIL */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_record_unavail();
			break;
		case 1200118: /* DITA2KDB_RETURN_ACCT_EXISTS */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_return_acct_exists();
			break;
		case 1200119: /* DITA2KDB_RETURN_INFO_UNAVAIL */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_return_info_unavail();
			break;
		case 1200121: /* DITA2KDB_RETURN_VIEW_ERROR */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_return_view_error();
			break;
		case 1200122: /* DITA2KDB_RETURN_WITH_ERRORS */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_return_with_errors();
			break;
		case 1200123: /* DITA2KDB_S0_MASTER_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_s0_master_not_found();
			break;
		case 1200130: /* DITA2KDB_SYSTRAN_NO_P47 */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_systran_no_p47();
			break;
		case 1200132: /* DITA2KDB_TAF_NOT_EQUAL_MASTER */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_taf_not_equal_master();
			break;
		case 1200137: /* DITA2KDB_UPDATES_MFL_ONLY */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_updates_mfl_only();
			break;
		case 1200141: /* DITA2KDB_VMAPPREQUEST_ERROR */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_vmapprequest_error();
			break;
		case 1200143: /* DITA2KDB_VMDISCONNECT_ERROR */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_vmdisconnect_error();
			break;
		case 1200150: /* DITA2KDB_VMREQUEST_SEND_FAILED */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_vmrequest_send_failed();
			break;
		case 1200151: /* DITA2KDB_VMREQUEST_SEND_FAILED2 */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_vmrequest_send_failed2();
			break;
		case 1200152: /* DITA2KDB_WS00221C_ACCESS_DENIED */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_access_denied();
			break;
		case 1200156: /* DITA2KDB_WS00221C_CONNECT_INTERNAL_ERROR */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_connect_internal_error();
			break;
		case 1200157: /* DITA2KDB_WS00221C_CONNECT_LOST */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_connect_lost();
			break;
		case 1200158: /* DITA2KDB_WS00221C_CONNECT_NOT_ESTABLISHED */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_connect_not_established();
			break;
		case 1200159: /* DITA2KDB_WS00221C_CONSTRAINT_NAME_RESTRICTS_DELT */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_constraint_name_restricts_delt();
			break;
		case 1200160: /* DITA2KDB_WS00221C_CUM_DISC_INV_BELOW_THRESHOLD */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_cum_disc_inv_below_threshold();
			break;
		case 1200161: /* DITA2KDB_WS00221C_DATA_SET_ID_ERROR */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_data_set_id_error();
			break;
		case 1200163: /* DITA2KDB_WS00221C_DEADLOCK_ROLLED_BCK */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_deadlock_rolled_bck();
			break;
		case 1200164: /* DITA2KDB_WS00221C_DEADLOCK_TIMEOUT_ROLL_BCK */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_deadlock_timeout_roll_bck();
			break;
		case 1200165: /* DITA2KDB_WS00221C_DIFFERENT_RECORD_LENGTH */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_different_record_length();
			break;
		case 1200169: /* DITA2KDB_WS00221C_EXCEPTION_ERROR */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_exception_error();
			break;
		case 1200170: /* DITA2KDB_WS00221C_FILE_ACCESS_ERROR */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_file_access_error();
			break;
		case 1200171: /* DITA2KDB_WS00221C_FILE_AT_END */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_file_at_end();
			break;
		case 1200172: /* DITA2KDB_WS00221C_FILE_INFO_MISSING */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_file_info_missing();
			break;
		case 1200173: /* DITA2KDB_WS00221C_FILE_NOT_CLOSED */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_file_not_closed();
			break;
		case 1200174: /* DITA2KDB_WS00221C_FILE_NOT_ON_REEL */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_file_not_on_reel();
			break;
		case 1200176: /* DITA2KDB_WS00221C_FILE_TYPE_NOT_SUPPORTED */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_file_type_not_supported();
			break;
		case 1200177: /* DITA2KDB_WS00221C_FUNCTION_DISABLED */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_function_disabled();
			break;
		case 1200178: /* DITA2KDB_WS00221C_INVALID_AUTHORIZATION */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_invalid_authorization();
			break;
		case 1200179: /* DITA2KDB_WS00221C_INVALID_OPERATION_AUTHORITY_1 */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_invalid_operation_authority_1();
			break;
		case 1200180: /* DITA2KDB_WS00221C_INVALID_OPERATION_AUTHORITY_2 */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_invalid_operation_authority_2();
			break;
		case 1200182: /* DITA2KDB_WS00221C_LOAD_TIMESTAMP_DIFFERENT */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_load_timestamp_different();
			break;
		case 1200184: /* DITA2KDB_WS00221C_NLS_ERROR */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_nls_error();
			break;
		case 1200185: /* DITA2KDB_WS00221C_NO_CRP_SET */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_no_crp_set();
			break;
		case 1200188: /* DITA2KDB_WS00221C_NO_SPACE_AVAILABLE_2 */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_no_space_available_2();
			break;
		case 1200192: /* DITA2KDB_WS00221C_OBJECT_DELETED */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_object_deleted();
			break;
		case 1200193: /* DITA2KDB_WS00221C_OPEN_AFTER_CLOSE_WITH_LOCK */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_open_after_close_with_lock();
			break;
		case 1200194: /* DITA2KDB_WS00221C_OPEN_FOR_FILE_ALREADY_OPEN */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_open_for_file_already_open();
			break;
		case 1200195: /* DITA2KDB_WS00221C_PASSWORD_FAILURE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_password_failure();
			break;
		case 1200196: /* DITA2KDB_WS00221C_PERMANENT_IO_ERROR */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_permanent_io_error();
			break;
		case 1200197: /* DITA2KDB_WS00221C_PERMANENT_SPACE_ERROR */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_permanent_space_error();
			break;
		case 1200199: /* DITA2KDB_WS00221C_READ_WITHOUT_OPEN_FOR_IO */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_read_without_open_for_io();
			break;
		case 1200201: /* DITA2KDB_WS00221C_RESOURCE_LIMIT_EXCEEDED */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resource_limit_exceeded();
			break;
		case 1200202: /* DITA2KDB_WS00221C_RESOURCE_NOT_AVAILABLE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resource_not_available();
			break;
		case 1200207: /* DITA2KDB_WS00221C_RESP_ACCT_CODED_BANK_CARD */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_acct_coded_bank_card();
			break;
		case 1200208: /* DITA2KDB_WS00221C_RESP_ACCT_CODED_TELE_TRANS */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_acct_coded_tele_trans();
			break;
		case 1200209: /* DITA2KDB_WS00221C_RESP_ACCT_DEALER_CONTROLLED */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_acct_dealer_controlled();
			break;
		case 1200210: /* DITA2KDB_WS00221C_RESP_ACCT_GRP_LIST_EMPTY */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_acct_grp_list_empty();
			break;
		case 1200214: /* DITA2KDB_WS00221C_RESP_ACCT_MARKED_NO_ACH_ACTIVY */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_acct_marked_no_ach_activy();
			break;
		case 1200215: /* DITA2KDB_WS00221C_RESP_ACCT_MARKED_NO_EXPD_EXCH */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_acct_marked_no_expd_exch();
			break;
		case 1200216: /* DITA2KDB_WS00221C_RESP_ACCT_MARKED_NO_REDMP_CHKS */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_acct_marked_no_redmp_chks();
			break;
		case 1200219: /* DITA2KDB_WS00221C_RESP_ACCT_MARKED_STOP_TRANSFER */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_acct_marked_stop_transfer();
			break;
		case 1200220: /* DITA2KDB_WS00221C_RESP_ACCT_MARKED_SUBACCOUNT */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_acct_marked_subaccount();
			break;
		case 1200221: /* DITA2KDB_WS00221C_RESP_ACCT_MKD_NO_MTHLY_PURCH */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_acct_mkd_no_mthly_purch();
			break;
		case 1200222: /* DITA2KDB_WS00221C_RESP_ACCT_NON_DEALER_CONTROL */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_acct_non_dealer_control();
			break;
		case 1200225: /* DITA2KDB_WS00221C_RESP_ACCTS_NOT_RELATED */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_accts_not_related();
			break;
		case 1200229: /* DITA2KDB_WS00221C_RESP_ALL_SHR_TRAN_REC_FOUND */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_all_shr_tran_rec_found();
			break;
		case 1200230: /* DITA2KDB_WS00221C_RESP_ALREADY_SIGNED_ON */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_already_signed_on();
			break;
		case 1200232: /* DITA2KDB_WS00221C_RESP_AMT_GT_MAX_ALLOWED */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_amt_gt_max_allowed();
			break;
		case 1200233: /* DITA2KDB_WS00221C_RESP_AMT_LT_MIN_REQUIRED */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_amt_lt_min_required();
			break;
		case 1200234: /* DITA2KDB_WS00221C_RESP_AUTH_BUT_NO_DESC */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_auth_but_no_desc();
			break;
		case 1200235: /* DITA2KDB_WS00221C_RESP_BAD_LINK_TO_CRTCSERV */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_bad_link_to_crtcserv();
			break;
		case 1200238: /* DITA2KDB_WS00221C_RESP_CALCULATION_ERROR */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_calculation_error();
			break;
		case 1200242: /* DITA2KDB_WS00221C_RESP_COMM_SHARES_REC_ERROR */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_comm_shares_rec_error();
			break;
		case 1200244: /* DITA2KDB_WS00221C_RESP_COPY_EXCH_SSN_MISMATCH */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_copy_exch_ssn_mismatch();
			break;
		case 1200245: /* DITA2KDB_WS00221C_RESP_COPY_MGMTS_NOT_EQUAL */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_copy_mgmts_not_equal();
			break;
		case 1200246: /* DITA2KDB_WS00221C_RESP_COPY_PURCH_ATEMPT_INVALID */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_copy_purch_atempt_invalid();
			break;
		case 1200248: /* DITA2KDB_WS00221C_RESP_CUM_DISC_ALRDY_EXIST */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_cum_disc_alrdy_exist();
			break;
		case 1200249: /* DITA2KDB_WS00221C_RESP_DATA_NOT_FND_ON_WS_TABLE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_data_not_fnd_on_ws_table();
			break;
		case 1200250: /* DITA2KDB_WS00221C_RESP_DATA_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_data_not_found();
			break;
		case 1200251: /* DITA2KDB_WS00221C_RESP_DEL_REC_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_del_rec_not_found();
			break;
		case 1200253: /* DITA2KDB_WS00221C_RESP_DFHRESP_DSNOTFOUND */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_dsnotfound();
			break;
		case 1200254: /* DITA2KDB_WS00221C_RESP_DFHRESP_DUPKEY */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_dupkey();
			break;
		case 1200255: /* DITA2KDB_WS00221C_RESP_DFHRESP_ENDFILE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_endfile();
			break;
		case 1200257: /* DITA2KDB_WS00221C_RESP_DFHRESP_ILLOGIC */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_illogic();
			break;
		case 1200258: /* DITA2KDB_WS00221C_RESP_DFHRESP_INVREQ */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_invreq();
			break;
		case 1200260: /* DITA2KDB_WS00221C_RESP_DFHRESP_ISCINVREQ */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_iscinvreq();
			break;
		case 1200262: /* DITA2KDB_WS00221C_RESP_DFHRESP_LOADING */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_loading();
			break;
		case 1200263: /* DITA2KDB_WS00221C_RESP_DFHRESP_NOTAUTH */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_notauth();
			break;
		case 1200264: /* DITA2KDB_WS00221C_RESP_DFHRESP_NOTFND */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_notfnd();
			break;
		case 1200265: /* DITA2KDB_WS00221C_RESP_DFHRESP_NOTOPEN */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_notopen();
			break;
		case 1200266: /* DITA2KDB_WS00221C_RESP_DFHRESP_PGMIDERR */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_pgmiderr();
			break;
		case 1200268: /* DITA2KDB_WS00221C_RESP_DFHRESP_ROLLEDBACK */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_rolledback();
			break;
		case 1200269: /* DITA2KDB_WS00221C_RESP_DFHRESP_SYSIDERR */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_sysiderr();
			break;
		case 1200270: /* DITA2KDB_WS00221C_RESP_DFHRESP_TERMERR */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_termerr();
			break;
		case 1200271: /* DITA2KDB_WS00221C_RESP_DFHRESP_USERIDERR */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_useriderr();
			break;
		case 1200273: /* DITA2KDB_WS00221C_RESP_ERROR_IN_BINARY_SEARCH */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_error_in_binary_search();
			break;
		case 1200274: /* DITA2KDB_WS00221C_RESP_EXCESS_FUNDS_FOR_INV_NUM */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_excess_funds_for_inv_num();
			break;
		case 1200275: /* DITA2KDB_WS00221C_RESP_EXCESS_TABLE_DATA */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_excess_table_data();
			break;
		case 1200277: /* DITA2KDB_WS00221C_RESP_EXCH_BANKS_NOT_EQUAL */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_exch_banks_not_equal();
			break;
		case 1200278: /* DITA2KDB_WS00221C_RESP_EXCH_FUNDS_EQUAL */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_exch_funds_equal();
			break;
		case 1200280: /* DITA2KDB_WS00221C_RESP_EXR_ACTIVITY_NOT_ALLOWED */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_exr_activity_not_allowed();
			break;
		case 1200281: /* DITA2KDB_WS00221C_RESP_EXR_ON_MATR_NOT_ALLOWED */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_exr_on_matr_not_allowed();
			break;
		case 1200282: /* DITA2KDB_WS00221C_RESP_FACILITY_NOT_PASSED */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_facility_not_passed();
			break;
		case 1200284: /* DITA2KDB_WS00221C_RESP_FUND_CLOSED */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_fund_closed();
			break;
		case 1200286: /* DITA2KDB_WS00221C_RESP_FUND_MARKED_NO_REDMP_CHKS */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_fund_marked_no_redmp_chks();
			break;
		case 1200289: /* DITA2KDB_WS00221C_RESP_INVALID_ACCESS_METHOD */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_access_method();
			break;
		case 1200290: /* DITA2KDB_WS00221C_RESP_INVALID_ACCOUNT_NMBR */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_account_nmbr();
			break;
		case 1200291: /* DITA2KDB_WS00221C_RESP_INVALID_ACCT_ALRDY_HS_LOI */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_acct_alrdy_hs_loi();
			break;
		case 1200292: /* DITA2KDB_WS00221C_RESP_INVALID_ACCT_GRP_CDE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_acct_grp_cde();
			break;
		case 1200293: /* DITA2KDB_WS00221C_RESP_INVALID_ACCT_OPTION */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_acct_option();
			break;
		case 1200294: /* DITA2KDB_WS00221C_RESP_INVALID_ACCT_RELATIONSHIP */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_acct_relationship();
			break;
		case 1200295: /* DITA2KDB_WS00221C_RESP_INVALID_ACCT_SHARE_LOT */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_acct_share_lot();
			break;
		case 1200296: /* DITA2KDB_WS00221C_RESP_INVALID_ACCUM_YEARS */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_accum_years();
			break;
		case 1200297: /* DITA2KDB_WS00221C_RESP_INVALID_ACH_DIVIDEND_CDE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_ach_dividend_cde();
			break;
		case 1200298: /* DITA2KDB_WS00221C_RESP_INVALID_ACH_SPEC_PURCH_CD */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_ach_spec_purch_cd();
			break;
		case 1200299: /* DITA2KDB_WS00221C_RESP_INVALID_ACH_SPEC_RDMPT_CD */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_ach_spec_rdmpt_cd();
			break;
		case 1200302: /* DITA2KDB_WS00221C_RESP_INVALID_ADDRESS_ENTERED */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_address_entered();
			break;
		case 1200303: /* DITA2KDB_WS00221C_RESP_INVALID_AGENT_FOR_FIRM */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_agent_for_firm();
			break;
		case 1200305: /* DITA2KDB_WS00221C_RESP_INVALID_AMOUNT */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_amount();
			break;
		case 1200306: /* DITA2KDB_WS00221C_RESP_INVALID_APO_FPO_CITY_CDE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_apo_fpo_city_cde();
			break;
		case 1200307: /* DITA2KDB_WS00221C_RESP_INVALID_APO_FPO_REG_FMT */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_apo_fpo_reg_fmt();
			break;
		case 1200310: /* DITA2KDB_WS00221C_RESP_INVALID_AVAILABLE_SHARES */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_available_shares();
			break;
		case 1200311: /* DITA2KDB_WS00221C_RESP_INVALID_BANK_ACCT_NBR */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_bank_acct_nbr();
			break;
		case 1200313: /* DITA2KDB_WS00221C_RESP_INVALID_BANK_MICR_ID */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_bank_micr_id();
			break;
		case 1200314: /* DITA2KDB_WS00221C_RESP_INVALID_BANK_NOT_ENTERED */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_bank_not_entered();
			break;
		case 1200315: /* DITA2KDB_WS00221C_RESP_INVALID_BANK_OPTION */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_bank_option();
			break;
		case 1200316: /* DITA2KDB_WS00221C_RESP_INVALID_BANK_REG */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_bank_reg();
			break;
		case 1200318: /* DITA2KDB_WS00221C_RESP_INVALID_BENEFICIARY_NAME */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_beneficiary_name();
			break;
		case 1200320: /* DITA2KDB_WS00221C_RESP_INVALID_CALL */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_call();
			break;
		case 1200323: /* DITA2KDB_WS00221C_RESP_INVALID_CDSC_SLS */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_cdsc_sls();
			break;
		case 1200324: /* DITA2KDB_WS00221C_RESP_INVALID_CERT_NUMBER */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_cert_number();
			break;
		case 1200326: /* DITA2KDB_WS00221C_RESP_INVALID_CITY_NOT_APO_FPO */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_city_not_apo_fpo();
			break;
		case 1200328: /* DITA2KDB_WS00221C_RESP_INVALID_CNFRM_FREQ */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_cnfrm_freq();
			break;
		case 1200329: /* DITA2KDB_WS00221C_RESP_INVALID_CONTRIB_YEAR_CODE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_contrib_year_code();
			break;
		case 1200330: /* DITA2KDB_WS00221C_RESP_INVALID_CORR_CODE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_corr_code();
			break;
		case 1200332: /* DITA2KDB_WS00221C_RESP_INVALID_CUMDISC */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_cumdisc();
			break;
		case 1200334: /* DITA2KDB_WS00221C_RESP_INVALID_DATA_REQ */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_data_req();
			break;
		case 1200335: /* DITA2KDB_WS00221C_RESP_INVALID_DATE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_date();
			break;
		case 1200336: /* DITA2KDB_WS00221C_RESP_INVALID_DAY_CDE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_day_cde();
			break;
		case 1200338: /* DITA2KDB_WS00221C_RESP_INVALID_DEBIT_TYPE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_debit_type();
			break;
		case 1200339: /* DITA2KDB_WS00221C_RESP_INVALID_DIVIDEND_CDE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_dividend_cde();
			break;
		case 1200340: /* DITA2KDB_WS00221C_RESP_INVALID_DLR_BR_SUMMRY */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_dlr_br_summry();
			break;
		case 1200342: /* DITA2KDB_WS00221C_RESP_INVALID_DLR_BRN_SEC */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_dlr_brn_sec();
			break;
		case 1200343: /* DITA2KDB_WS00221C_RESP_INVALID_DLR_NUMBER */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_dlr_number();
			break;
		case 1200344: /* DITA2KDB_WS00221C_RESP_INVALID_DLR_SUMMARY */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_dlr_summary();
			break;
		case 1200345: /* DITA2KDB_WS00221C_RESP_INVALID_DSCS_APPREC */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_dscs_apprec();
			break;
		case 1200346: /* DITA2KDB_WS00221C_RESP_INVALID_EML_ADR_ENTERED */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_eml_adr_entered();
			break;
		case 1200347: /* DITA2KDB_WS00221C_RESP_INVALID_ESCROW_SHRS */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_escrow_shrs();
			break;
		case 1200349: /* DITA2KDB_WS00221C_RESP_INVALID_EXCH_RED_CANC */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_exch_red_canc();
			break;
		case 1200350: /* DITA2KDB_WS00221C_RESP_INVALID_EXIST_CDE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_exist_cde();
			break;
		case 1200351: /* DITA2KDB_WS00221C_RESP_INVALID_FID_ACCOUNT */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_fid_account();
			break;
		case 1200353: /* DITA2KDB_WS00221C_RESP_INVALID_FIRM_ACCT_NBR */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_firm_acct_nbr();
			break;
		case 1200356: /* DITA2KDB_WS00221C_RESP_INVALID_FLD_ID */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_fld_id();
			break;
		case 1200359: /* DITA2KDB_WS00221C_RESP_INVALID_FREQ_FOR_BALANCE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_freq_for_balance();
			break;
		case 1200360: /* DITA2KDB_WS00221C_RESP_INVALID_FRONT_END */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_front_end();
			break;
		case 1200361: /* DITA2KDB_WS00221C_RESP_INVALID_FULL_CODE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_full_code();
			break;
		case 1200362: /* DITA2KDB_WS00221C_RESP_INVALID_FUNCTION_TYPE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_function_type();
			break;
		case 1200363: /* DITA2KDB_WS00221C_RESP_INVALID_FUND_AGREEMENT */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_fund_agreement();
			break;
		case 1200364: /* DITA2KDB_WS00221C_RESP_INVALID_FUND_CODE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_fund_code();
			break;
		case 1200366: /* DITA2KDB_WS00221C_RESP_INVALID_FUND_OPTION */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_fund_option();
			break;
		case 1200368: /* DITA2KDB_WS00221C_RESP_INVALID_HOUSE_ACCOUNT */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_house_account();
			break;
		case 1200369: /* DITA2KDB_WS00221C_RESP_INVALID_IDV_DMS_ADR_CD */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_idv_dms_adr_cd();
			break;
		case 1200370: /* DITA2KDB_WS00221C_RESP_INVALID_INDIVIDUAL_ID */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_individual_id();
			break;
		case 1200371: /* DITA2KDB_WS00221C_RESP_INVALID_INSTRUCTION_ID */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_instruction_id();
			break;
		case 1200372: /* DITA2KDB_WS00221C_RESP_INVALID_KEY_DATA */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_key_data();
			break;
		case 1200373: /* DITA2KDB_WS00221C_RESP_INVALID_KEY_SUFFIX */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_key_suffix();
			break;
		case 1200376: /* DITA2KDB_WS00221C_RESP_INVALID_LOI_EFF_DTE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_loi_eff_dte();
			break;
		case 1200378: /* DITA2KDB_WS00221C_RESP_INVALID_LOT_VALUE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_lot_value();
			break;
		case 1200379: /* DITA2KDB_WS00221C_RESP_INVALID_MARITAL_STATUS */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_marital_status();
			break;
		case 1200380: /* DITA2KDB_WS00221C_RESP_INVALID_MAX_AMT */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_max_amt();
			break;
		case 1200381: /* DITA2KDB_WS00221C_RESP_INVALID_MGMT_CODE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_mgmt_code();
			break;
		case 1200383: /* DITA2KDB_WS00221C_RESP_INVALID_MONTHLY_ACCUM */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_monthly_accum();
			break;
		case 1200385: /* DITA2KDB_WS00221C_RESP_INVALID_NAV_CDE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_nav_cde();
			break;
		case 1200386: /* DITA2KDB_WS00221C_RESP_INVALID_NAV_PER_SHR */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_nav_per_shr();
			break;
		case 1200388: /* DITA2KDB_WS00221C_RESP_INVALID_NO_ACCT_TO_UPD */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_no_acct_to_upd();
			break;
		case 1200389: /* DITA2KDB_WS00221C_RESP_INVALID_NO_SPC_CTYST_CD */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_no_spc_ctyst_cd();
			break;
		case 1200390: /* DITA2KDB_WS00221C_RESP_INVALID_NUM_ABBREV_ST */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_num_abbrev_st();
			break;
		case 1200391: /* DITA2KDB_WS00221C_RESP_INVALID_OPTION */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_option();
			break;
		case 1200392: /* DITA2KDB_WS00221C_RESP_INVALID_OPTION_REQUEST */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_option_request();
			break;
		case 1200393: /* DITA2KDB_WS00221C_RESP_INVALID_ORDER_NUMBER */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_order_number();
			break;
		case 1200394: /* DITA2KDB_WS00221C_RESP_INVALID_OUT_OF_BLC_HI_RT */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_out_of_blc_hi_rt();
			break;
		case 1200396: /* DITA2KDB_WS00221C_RESP_INVALID_PAF_BUCKET */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_paf_bucket();
			break;
		case 1200397: /* DITA2KDB_WS00221C_RESP_INVALID_PARM_DATA */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_parm_data();
			break;
		case 1200398: /* DITA2KDB_WS00221C_RESP_INVALID_PIN_INACTIVE_CDE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_pin_inactive_cde();
			break;
		case 1200401: /* DITA2KDB_WS00221C_RESP_INVALID_PRE_AGREEMENT */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_pre_agreement();
			break;
		case 1200402: /* DITA2KDB_WS00221C_RESP_INVALID_PRE_EX_MAIL_CDE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_pre_ex_mail_cde();
			break;
		case 1200405: /* DITA2KDB_WS00221C_RESP_INVALID_PRICE_SCHED_CDE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_price_sched_cde();
			break;
		case 1200406: /* DITA2KDB_WS00221C_RESP_INVALID_PROCESS_CODE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_process_code();
			break;
		case 1200407: /* DITA2KDB_WS00221C_RESP_INVALID_PROCESS_TYPE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_process_type();
			break;
		case 1200411: /* DITA2KDB_WS00221C_RESP_INVALID_PURCH_CANCEL */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_purch_cancel();
			break;
		case 1200412: /* DITA2KDB_WS00221C_RESP_INVALID_RE_BLC_EXCL_CD */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_re_blc_excl_cd();
			break;
		case 1200413: /* DITA2KDB_WS00221C_RESP_INVALID_REDEMPT_OPT */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_redempt_opt();
			break;
		case 1200414: /* DITA2KDB_WS00221C_RESP_INVALID_REDMPT_CANCEL */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_redmpt_cancel();
			break;
		case 1200415: /* DITA2KDB_WS00221C_RESP_INVALID_REIN_DOLLAR */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_rein_dollar();
			break;
		case 1200416: /* DITA2KDB_WS00221C_RESP_INVALID_REIN_SHARES */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_rein_shares();
			break;
		case 1200419: /* DITA2KDB_WS00221C_RESP_INVALID_RES_STATE_CD */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_res_state_cd();
			break;
		case 1200422: /* DITA2KDB_WS00221C_RESP_INVALID_RULE_ID */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_rule_id();
			break;
		case 1200423: /* DITA2KDB_WS00221C_RESP_INVALID_SEC_ISS_ID */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_sec_iss_id();
			break;
		case 1200424: /* DITA2KDB_WS00221C_RESP_INVALID_SHAREOWNER_NAME */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_shareowner_name();
			break;
		case 1200425: /* DITA2KDB_WS00221C_RESP_INVALID_SHARES */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_shares();
			break;
		case 1200426: /* DITA2KDB_WS00221C_RESP_INVALID_SOC_SEC_NBR */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_soc_sec_nbr();
			break;
		case 1200427: /* DITA2KDB_WS00221C_RESP_INVALID_SOCIAL_CODE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_social_code();
			break;
		case 1200428: /* DITA2KDB_WS00221C_RESP_INVALID_SORT_CODE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_sort_code();
			break;
		case 1200430: /* DITA2KDB_WS00221C_RESP_INVALID_SS_CODE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_ss_code();
			break;
		case 1200433: /* DITA2KDB_WS00221C_RESP_INVALID_START_DTE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_start_dte();
			break;
		case 1200438: /* DITA2KDB_WS00221C_RESP_INVALID_STOP_DTE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_stop_dte();
			break;
		case 1200441: /* DITA2KDB_WS00221C_RESP_INVALID_SYST_TRANS_CDE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_syst_trans_cde();
			break;
		case 1200442: /* DITA2KDB_WS00221C_RESP_INVALID_SYSTEM_ID */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_system_id();
			break;
		case 1200445: /* DITA2KDB_WS00221C_RESP_INVALID_TBL_LD_OR_ST_POS */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_tbl_ld_or_st_pos();
			break;
		case 1200447: /* DITA2KDB_WS00221C_RESP_INVALID_TIME_OF_DAY */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_time_of_day();
			break;
		case 1200448: /* DITA2KDB_WS00221C_RESP_INVALID_TIMESTAMP */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_timestamp();
			break;
		case 1200449: /* DITA2KDB_WS00221C_RESP_INVALID_TO_ACCT_NBR */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_to_acct_nbr();
			break;
		case 1200450: /* DITA2KDB_WS00221C_RESP_INVALID_TO_FUND_CODE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_to_fund_code();
			break;
		case 1200451: /* DITA2KDB_WS00221C_RESP_INVALID_TO_MGMT_CODE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_to_mgmt_code();
			break;
		case 1200452: /* DITA2KDB_WS00221C_RESP_INVALID_TRADE_VALUE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_trade_value();
			break;
		case 1200456: /* DITA2KDB_WS00221C_RESP_INVALID_USER_STATUS */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_user_status();
			break;
		case 1200457: /* DITA2KDB_WS00221C_RESP_INVALID_VERSION */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_version();
			break;
		case 1200459: /* DITA2KDB_WS00221C_RESP_INVALID_WITHH_CNT */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_withh_cnt();
			break;
		case 1200460: /* DITA2KDB_WS00221C_RESP_INVALID_YIELD_DATE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_yield_date();
			break;
		case 1200461: /* DITA2KDB_WS00221C_RESP_INVALID_ZIP_CODE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_zip_code();
			break;
		case 1200462: /* DITA2KDB_WS00221C_RESP_INVALID_ZIP_FOR_STATE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_invalid_zip_for_state();
			break;
		case 1200463: /* DITA2KDB_WS00221C_RESP_LAST_ACCT_NUMBER_ASSIGNED */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_last_acct_number_assigned();
			break;
		case 1200464: /* DITA2KDB_WS00221C_RESP_LAST_CUM_NBR_ASSIGN */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_last_cum_nbr_assign();
			break;
		case 1200465: /* DITA2KDB_WS00221C_RESP_NET_DLR_CODE_NOT_ALLOWED */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_net_dlr_code_not_allowed();
			break;
		case 1200466: /* DITA2KDB_WS00221C_RESP_NO_PRE_AUTH_CHECKS */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_no_pre_auth_checks();
			break;
		case 1200467: /* DITA2KDB_WS00221C_RESP_NO_TWENTY_FOUR_HR_TRADING */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_no_twenty_four_hr_trading();
			break;
		case 1200468: /* DITA2KDB_WS00221C_RESP_NO_UPDATE_DETECTED */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_no_update_detected();
			break;
		case 1200469: /* DITA2KDB_WS00221C_RESP_NO_UPDATES_TO_APPLY */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_no_updates_to_apply();
			break;
		case 1200471: /* DITA2KDB_WS00221C_RESP_NOT_AUTHORIZED */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_not_authorized();
			break;
		case 1200473: /* DITA2KDB_WS00221C_RESP_OPERATOR_DISABLED */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_operator_disabled();
			break;
		case 1200474: /* DITA2KDB_WS00221C_RESP_OPERATOR_NOT_ATH_DEALER */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_operator_not_ath_dealer();
			break;
		case 1200475: /* DITA2KDB_WS00221C_RESP_OPERATOR_NOT_ATH_DLR_BR */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_operator_not_ath_dlr_br();
			break;
		case 1200476: /* DITA2KDB_WS00221C_RESP_OPERATOR_NOT_PASSED */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_operator_not_passed();
			break;
		case 1200478: /* DITA2KDB_WS00221C_RESP_PIN_MASK_INVALID */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_pin_mask_invalid();
			break;
		case 1200479: /* DITA2KDB_WS00221C_RESP_PIN_NBR_INVALID_CUSTOM */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_pin_nbr_invalid_custom();
			break;
		case 1200483: /* DITA2KDB_WS00221C_RESP_PIN_NUMBER_HOLD */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_pin_number_hold();
			break;
		case 1200484: /* DITA2KDB_WS00221C_RESP_PIN_NUMBER_INACTIVE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_pin_number_inactive();
			break;
		case 1200485: /* DITA2KDB_WS00221C_RESP_PIN_NUMBER_INVALID */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_pin_number_invalid();
			break;
		case 1200488: /* DITA2KDB_WS00221C_RESP_PIN_NUMBER_SUSPENDED */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_pin_number_suspended();
			break;
		case 1200490: /* DITA2KDB_WS00221C_RESP_PRC_RECORD_NOT_FND */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_prc_record_not_fnd();
			break;
		case 1200491: /* DITA2KDB_WS00221C_RESP_PROCESS_ERROR */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_process_error();
			break;
		case 1200492: /* DITA2KDB_WS00221C_RESP_RECORD_BYPASSED */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_record_bypassed();
			break;
		case 1200493: /* DITA2KDB_WS00221C_RESP_RED_AMT_GT_ACCT_VALUE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_red_amt_gt_acct_value();
			break;
		case 1200494: /* DITA2KDB_WS00221C_RESP_REQUEST_ON_UNINIT_TBL */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_request_on_uninit_tbl();
			break;
		case 1200496: /* DITA2KDB_WS00221C_RESP_RETURN_NASU_ACCT */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_return_nasu_acct();
			break;
		case 1200498: /* DITA2KDB_WS00221C_RESP_RETURN_SYSTEM_DOWN */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_return_system_down();
			break;
		case 1200499: /* DITA2KDB_WS00221C_RESP_SHR_TRAN_NOT_AUTHORIZED */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_shr_tran_not_authorized();
			break;
		case 1200503: /* DITA2KDB_WS00221C_RESP_STOCK_SPLIT_HST_NOT_FND */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_stock_split_hst_not_fnd();
			break;
		case 1200505: /* DITA2KDB_WS00221C_RESP_SYS_EXCH_REC_EXISTS */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_sys_exch_rec_exists();
			break;
		case 1200507: /* DITA2KDB_WS00221C_RESP_TRAN_SHRS_CONTAIN_CERTS */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_tran_shrs_contain_certs();
			break;
		case 1200508: /* DITA2KDB_WS00221C_RESP_TRAN_SHRS_CONTAIN_ESCROW */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_tran_shrs_contain_escrow();
			break;
		case 1200510: /* DITA2KDB_WS00221C_RESP_TRAN_TYPE_NOT_DEFINED */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_tran_type_not_defined();
			break;
		case 1200511: /* DITA2KDB_WS00221C_RESP_UNABLE_TO_ASSGN_NEXT_ACCT */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_unable_to_assgn_next_acct();
			break;
		case 1200513: /* DITA2KDB_WS00221C_RESP_ZERO_UNISSUED_SHARES */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_resp_zero_unissued_shares();
			break;
		case 1200514: /* DITA2KDB_WS00221C_REWRITE_WITHOUT_OPEN_FOR_IO */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_rewrite_without_open_for_io();
			break;
		case 1200515: /* DITA2KDB_WS00221C_ROW_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_row_not_found();
			break;
		case 1200516: /* DITA2KDB_WS00221C_SEQ_READ_AFTER_EOF */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_seq_read_after_eof();
			break;
		case 1200517: /* DITA2KDB_WS00221C_SEQUENCE_ERROR */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_sequence_error();
			break;
		case 1200518: /* DITA2KDB_WS00221C_SEVERE_SQL_ERROR */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_severe_sql_error();
			break;
		case 1200520: /* DITA2KDB_WS00221C_SYSTEM_ERROR */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_system_error();
			break;
		case 1200521: /* DITA2KDB_WS00221C_UNAVAILABLE_RESOURCE */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_unavailable_resource();
			break;
		case 1200522: /* DITA2KDB_WS00221C_UNEXPECTED_DATA_LENGTH_RETURNED */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_unexpected_data_length_returned();
			break;
		case 1200525: /* DITA2KDB_WS00221C_WRITE_WITHOUT_OPEN_FOR_IO */
			conditionObj = new CIFast_Infrastructure_dita2kdb_dita2kdb_ws00221c_write_without_open_for_io();
			break;
		case 1200527: /* ERR_WARN_ACCOUNT_TYPE_DONT_MATCH_FOR_IN_KIND_TRANS */
			conditionObj = new CIFast_Infrastructure_dita2kdb_err_warn_account_type_dont_match_for_in_kind_trans();
			break;
		case 1300001: /* ERR_CITY_NAME_NOT_ALLOWED */
			conditionObj = new CIFast_Infrastructure_ditabuscore_err_city_name_not_allowed();
			break;
		case 1300002: /* ERR_CITY_NAME_REQUIRED */
			conditionObj = new CIFast_Infrastructure_ditabuscore_err_city_name_required();
			break;
		case 1300004: /* ERR_FIELD_MUSTBE_EMPTY */
			conditionObj = new CIFast_Infrastructure_ditabuscore_err_field_mustbe_empty();
			break;
		case 1300005: /* ERR_FIELD_NOT_NUMERIC */
			conditionObj = new CIFast_Infrastructure_ditabuscore_err_field_not_numeric();
			break;
		case 1300006: /* ERR_FIELD_VALUE_ZERO */
			conditionObj = new CIFast_Infrastructure_ditabuscore_err_field_value_zero();
			break;
		case 1300007: /* ERR_FINALIST_ERR */
			conditionObj = new CIFast_Infrastructure_ditabuscore_err_finalist_err();
			break;
		case 1300008: /* ERR_INVALID_ADDRESS_LINE */
			conditionObj = new CIFast_Infrastructure_ditabuscore_err_invalid_address_line();
			break;
		case 1300009: /* ERR_INVALID_CERTIFICATION_STATUS_CODE */
			conditionObj = new CIFast_Infrastructure_ditabuscore_err_invalid_certification_status_code();
			break;
		case 1300010: /* ERR_INVALID_CITY_NAME_WRT_STATE_CODE */
			conditionObj = new CIFast_Infrastructure_ditabuscore_err_invalid_city_name_wrt_state_code();
			break;
		case 1300013: /* ERR_INVALID_MILITARY_LOCATION */
			conditionObj = new CIFast_Infrastructure_ditabuscore_err_invalid_military_location();
			break;
		case 1300015: /* ERR_INVALID_STATE_COUNTRY */
			conditionObj = new CIFast_Infrastructure_ditabuscore_err_invalid_state_country();
			break;
		case 1300018: /* ERR_INVALID_ZIPCODE */
			conditionObj = new CIFast_Infrastructure_ditabuscore_err_invalid_zipcode();
			break;
		case 1300020: /* ERR_MILITARY_LOCATION_NOT_ALLOWED */
			conditionObj = new CIFast_Infrastructure_ditabuscore_err_military_location_not_allowed();
			break;
		case 1300021: /* ERR_POSTAL_ADDRESS_NOT_FORMATTED */
			conditionObj = new CIFast_Infrastructure_ditabuscore_err_postal_address_not_formatted();
			break;
		case 1300022: /* ERR_S017PE_ERR */
			conditionObj = new CIFast_Infrastructure_ditabuscore_err_s017pe_err();
			break;
		case 1300023: /* ERR_STATE_COUNTRY_CODE_REQUIRED */
			conditionObj = new CIFast_Infrastructure_ditabuscore_err_state_country_code_required();
			break;
		case 1300026: /* ERR_ZIP_CODE_SUFFIX_REQUIRED */
			conditionObj = new CIFast_Infrastructure_ditabuscore_err_zip_code_suffix_required();
			break;
		case 1300031: /* WRN_FINALIST_WRN */
			conditionObj = new CIFast_Infrastructure_ditabuscore_wrn_finalist_wrn();
			break;
		case 1600001: /* BP_ERR_ACCOUNT_WAS_NOT_ACTIVE */
			conditionObj = new CIFast_Infrastructure_ifastbp_bp_err_account_was_not_active();
			break;
		case 1600023: /* BP_ERR_NO_SEARCH_CRITERIA */
			conditionObj = new CIFast_Infrastructure_ifastbp_bp_err_no_search_criteria();
			break;
		case 1600024: /* BP_ERR_NOT_ALLOW_SETFOCUS */
			conditionObj = new CIFast_Infrastructure_ifastbp_bp_err_not_allow_setfocus();
			break;
		case 1600025: /* BP_ERR_RESP_BENEFICIARY */
			conditionObj = new CIFast_Infrastructure_ifastbp_bp_err_resp_beneficiary();
			break;
		case 1600028: /* BP_NO_ACCESS_TO_ACCTDETAILS */
			conditionObj = new CIFast_Infrastructure_ifastbp_bp_no_access_to_acctdetails();
			break;
		case 1600035: /* ERR_AGENT_LIST_EMPTY */
			conditionObj = new CIFast_Infrastructure_ifastbp_err_agent_list_empty();
			break;
		case 1600036: /* ERR_BRANCH_LIST_EMPTY */
			conditionObj = new CIFast_Infrastructure_ifastbp_err_branch_list_empty();
			break;
		case 1600037: /* ERR_BROKER_LIST_EMPTY */
			conditionObj = new CIFast_Infrastructure_ifastbp_err_broker_list_empty();
			break;
		case 1600038: /* ERR_BROKER_NAME_EMPTY */
			conditionObj = new CIFast_Infrastructure_ifastbp_err_broker_name_empty();
			break;
		case 1600045: /* ERR_NO_VALID_SHAREHOLDER_OR_ACCOUNT */
			conditionObj = new CIFast_Infrastructure_ifastbp_err_no_valid_shareholder_or_account();
			break;
		case 1700001: /* ACC_TAX_TYPE_NOT_MATCH */
			conditionObj = new CIFast_Infrastructure_ifastcbo_acc_tax_type_not_match();
			break;
		case 1700041: /* BP_ERR_NO_SEARCH_CRTITERIA */
			conditionObj = new CIFast_Infrastructure_ifastcbo_bp_err_no_search_crtiteria();
			break;
		case 1700046: /* ERR_ACC_TAX_TYPE_NOT_MATCH */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_acc_tax_type_not_match();
			break;
		case 1700048: /* ERR_ACCOUNT_CODED_AS_ASSIGNED */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_account_coded_as_assigned();
			break;
		case 1700051: /* ERR_ACCOUNT_EMPTY */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_account_empty();
			break;
		case 1700055: /* ERR_ACCOUNT_NOT_IN_REPOSITORY */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_account_not_in_repository();
			break;
		case 1700057: /* ERR_ACCOUNT_NUM_CANNOT_BE_LEFT_EMPTY */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_account_num_cannot_be_left_empty();
			break;
		case 1700059: /* ERR_ACCOUNT_NUMBER_CANNOT_START_WITH_ZERO */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_account_number_cannot_start_with_zero();
			break;
		case 1700060: /* ERR_ACCOUNT_NUMBER_EMPTY */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_account_number_empty();
			break;
		case 1700061: /* ERR_ACCOUNT_NUMBER_EXISTS */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_account_number_exists();
			break;
		case 1700062: /* ERR_ACCOUNT_NUMBER_NOT_ALL_DIGITS */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_account_number_not_all_digits();
			break;
		case 1700064: /* ERR_ACCOUNT_OWNER_ENTITY_MUST_BE_SETUP */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_account_owner_entity_must_be_setup();
			break;
		case 1700066: /* ERR_ACCOUNT_STOP_FLAG_ON */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_account_stop_flag_on();
			break;
		case 1700068: /* ERR_ACCOUNT_TYPE_EMPTY */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_account_type_empty();
			break;
		case 1700070: /* ERR_ACCOUNTABILITY_FOR_BACKDATE_TRADE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_accountability_for_backdate_trade();
			break;
		case 1700071: /* ERR_ACCOUNTABILITY_ONLY_FOR_BACKDATE_TRADE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_accountability_only_for_backdate_trade();
			break;
		case 1700081: /* ERR_ACCT_BALANCE_TERM_AND_DEL */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_acct_balance_term_and_del();
			break;
		case 1700082: /* ERR_ACCT_BALANCE_TERM_AND_DEL_MAINT */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_acct_balance_term_and_del_maint();
			break;
		case 1700083: /* ERR_ACCT_BALANCE_ZERO */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_acct_balance_zero();
			break;
		case 1700093: /* ERR_ACCT_DOES_NOT_EXIST */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_acct_does_not_exist();
			break;
		case 1700096: /* ERR_ACCT_FUND_CLASS_NOT_UNIQUE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_acct_fund_class_not_unique();
			break;
		case 1700098: /* ERR_ACCT_HAS_STOPPED_PAC_OR_PURCH */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_acct_has_stopped_pac_or_purch();
			break;
		case 1700099: /* ERR_ACCT_HAS_STOPPED_SWP_OR_REDEM */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_acct_has_stopped_swp_or_redem();
			break;
		case 1700101: /* ERR_ACCT_INACTIVE_ON_TRADE_DATE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_acct_inactive_on_trade_date();
			break;
		case 1700103: /* ERR_ACCT_INVALID_FOR_THIS_SHR */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_acct_invalid_for_this_shr();
			break;
		case 1700108: /* ERR_ACCT_NBR_ALREADY_EXISTS */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_acct_nbr_already_exists();
			break;
		case 1700112: /* ERR_ACCT_OWNER_DUPLICATE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_acct_owner_duplicate();
			break;
		case 1700114: /* ERR_ACCT_OWNER_SEQ_ONE_NEEDED */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_acct_owner_seq_one_needed();
			break;
		case 1700125: /* ERR_ACCT_TYPE_NOT_VALID_FOR_TAX_TYPE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_acct_type_not_valid_for_tax_type();
			break;
		case 1700133: /* ERR_ACCTUSE_ALREADY_EXIST */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_acctuse_already_exist();
			break;
		case 1700139: /* ERR_ADD_ENTITY_DEATH_DATE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_add_entity_death_date();
			break;
		case 1700144: /* ERR_ADDRESS_CODE_NOT_EFFECTIVE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_address_code_not_effective();
			break;
		case 1700145: /* ERR_ADDRESS_CODE_NOT_SETUP */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_address_code_not_setup();
			break;
		case 1700146: /* ERR_ADDRESS_CODE_REQUIRED */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_address_code_required();
			break;
		case 1700147: /* ERR_ADDRESS_CODE_USEDBY_MAILING */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_address_code_usedby_mailing();
			break;
		case 1700149: /* ERR_ADDRESS_ID_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_address_id_not_found();
			break;
		case 1700150: /* ERR_ADDRESS_LINE_MISSING */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_address_line_missing();
			break;
		case 1700151: /* ERR_ADDRESS_LINE45 */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_address_line45();
			break;
		case 1700153: /* ERR_ADDRESS_TWO_LINE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_address_two_line();
			break;
		case 1700168: /* ERR_ALLOC_FOR_ACCT_TYPE06 */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_alloc_for_acct_type06();
			break;
		case 1700169: /* ERR_ALLOC_FOR_INACTIVE_ACCT */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_alloc_for_inactive_acct();
			break;
		case 1700171: /* ERR_ALLOCAMOUNT_GREATER_THAN_TOTAL */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_allocamount_greater_than_total();
			break;
		case 1700173: /* ERR_ALLOCATION_MUST_BE_ENTERED */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_allocation_must_be_entered();
			break;
		case 1700175: /* ERR_ALLOCATION_TOTAL_INCORRECT */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_allocation_total_incorrect();
			break;
		case 1700179: /* ERR_AMOUNT_EXCEED_MAX_LIMIT */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_amount_exceed_max_limit();
			break;
		case 1700196: /* ERR_AMOUNT_TYPE_IS_MANDATORY */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_amount_type_is_mandatory();
			break;
		case 1700230: /* ERR_AMT_TYPE_MUST_BE_AMOUNT */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_amt_type_must_be_amount();
			break;
		case 1700236: /* ERR_ANNUITANT_ENTITY_IS_NOT_ALLOWED */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_annuitant_entity_is_not_allowed();
			break;
		case 1700237: /* ERR_ANNUITANT_ENTITY_SHOULD_BE_SETUP */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_annuitant_entity_should_be_setup();
			break;
		case 1700239: /* ERR_ANNUITANT_INVALID_FOR_ACCT_TYPE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_annuitant_invalid_for_acct_type();
			break;
		case 1700247: /* ERR_ASSIGNNED_ACCOUNT */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_assignned_account();
			break;
		case 1700251: /* ERR_AT_ACCOUNT_NOT_EXIST */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_at_account_not_exist();
			break;
		case 1700252: /* ERR_AT_AMOUNT_TRANSFER */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_at_amount_transfer();
			break;
		case 1700253: /* ERR_AT_AMOUNT_TYPE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_at_amount_type();
			break;
		case 1700255: /* ERR_AT_DEEMED_FULL */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_at_deemed_full();
			break;
		case 1700256: /* ERR_AT_FOR_ESCROW_ACCT */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_at_for_escrow_acct();
			break;
		case 1700257: /* ERR_AT_FROM_FUND_CLASS_TO_FUND_CLASS */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_at_from_fund_class_to_fund_class();
			break;
		case 1700258: /* ERR_AT_FUNDCLASS_TRANSFER_NOT_ALLOWED */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_at_fundclass_transfer_not_allowed();
			break;
		case 1700259: /* ERR_AT_FUNDTO_CLASSTO_ACOUNTTO_SAME_AS_FROM */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_at_fundto_classto_acountto_same_as_from();
			break;
		case 1700260: /* ERR_AT_HAS_STOPPED_TRANSFER_IN */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_at_has_stopped_transfer_in();
			break;
		case 1700261: /* ERR_AT_HAS_STOPPED_TRANSFER_OR_EXCH */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_at_has_stopped_transfer_or_exch();
			break;
		case 1700262: /* ERR_AT_INVALID_ACCT_TAXTYPE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_at_invalid_acct_taxtype();
			break;
		case 1700263: /* ERR_AT_INVALID_ZERO_AMOUNT */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_at_invalid_zero_amount();
			break;
		case 1700265: /* ERR_AT_LEAST_ONE_MONTH_MUST_ACTIVE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_at_least_one_month_must_active();
			break;
		case 1700269: /* ERR_AVAILABLE_PERCENT_FOR_PRIMARY_BENEF */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_available_percent_for_primary_benef();
			break;
		case 1700272: /* ERR_BACKDATE_TRADE_NOT_ALLOWED */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_backdate_trade_not_allowed();
			break;
		case 1700286: /* ERR_BANKACCTNUM_TOO_BIG */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_bankacctnum_too_big();
			break;
		case 1700287: /* ERR_BANKINFO_REQUIRED */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_bankinfo_required();
			break;
		case 1700295: /* ERR_BENEF_PERCENT_REQUIRED */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_benef_percent_required();
			break;
		case 1700307: /* ERR_BIRTHNAME_REQUIRED */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_birthname_required();
			break;
		case 1700308: /* ERR_BLANK_CLASS */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_blank_class();
			break;
		case 1700311: /* ERR_BLANK_FUND */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_blank_fund();
			break;
		case 1700316: /* ERR_BRANCH_EMPTY */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_branch_empty();
			break;
		case 1700327: /* ERR_BROKER_BRANCH_CFG */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_broker_branch_cfg();
			break;
		case 1700331: /* ERR_BROKER_EMPTY */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_broker_empty();
			break;
		case 1700333: /* ERR_BROKER_INTERMEDIARY_ADDRESS_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_broker_intermediary_address_not_found();
			break;
		case 1700357: /* ERR_CANNOT_CHANGE_TAX_TYPE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_cannot_change_tax_type();
			break;
		case 1700368: /* ERR_CAPPEDFUND_STATUSE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_cappedfund_statuse();
			break;
		case 1700369: /* ERR_CAPPEDFUND_STATUSW */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_cappedfund_statusw();
			break;
		case 1700371: /* ERR_CASH_FUND_NOT_ALLOWED */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_cash_fund_not_allowed();
			break;
		case 1700378: /* ERR_CERT_NOT_FOR_FUND_CLASS */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_cert_not_for_fund_class();
			break;
		case 1700382: /* ERR_CHANGE_ALL_MARKET_MAILING */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_change_all_market_mailing();
			break;
		case 1700404: /* ERR_CLIENTS_AGE_BEYOND */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_clients_age_beyond();
			break;
		case 1700432: /* ERR_CONTRACT_MUST_BE_CREATED */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_contract_must_be_created();
			break;
		case 1700433: /* ERR_CONTRACT_NOT_EFFECTIVE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_contract_not_effective();
			break;
		case 1700434: /* ERR_CONTRACT_STATUS */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_contract_status();
			break;
		case 1700436: /* ERR_CONTRACT_TYPE_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_contract_type_not_found();
			break;
		case 1700439: /* ERR_COPY_OBJECT_NOT_INITIALIZED */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_copy_object_not_initialized();
			break;
		case 1700452: /* ERR_CURRENCY_SHOULD_BE_SAME */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_currency_should_be_same();
			break;
		case 1700454: /* ERR_CURRENT_FUND_BALANCES */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_current_fund_balances();
			break;
		case 1700463: /* ERR_DATE_FUNCTIONS */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_date_functions();
			break;
		case 1700464: /* ERR_DATE_MUST_BE_BUSINESS_DATE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_date_must_be_business_date();
			break;
		case 1700472: /* ERR_DAYOFWEEK_REQUIRED */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_dayofweek_required();
			break;
		case 1700479: /* ERR_DEATH_NOTIF_BEFORE_DEATH_DATE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_death_notif_before_death_date();
			break;
		case 1700480: /* ERR_DEATH_NOTIF_NO_DEATH_DATE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_death_notif_no_death_date();
			break;
		case 1700485: /* ERR_DEFF_STOP_DATE_RANGE_EXISTS */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_deff_stop_date_range_exists();
			break;
		case 1700488: /* ERR_DELETE_ENTITY */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_delete_entity();
			break;
		case 1700497: /* ERR_DEPOSIT_DATE_AFFECT_MIN_MAX_AMT */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_deposit_date_affect_min_max_amt();
			break;
		case 1700507: /* ERR_DEPOSITS_NOT_ALLOWED */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_deposits_not_allowed();
			break;
		case 1700513: /* ERR_DESIGNATION_INSTITUTION_HAS_NOT_BEEN_SETUP */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_designation_institution_has_not_been_setup();
			break;
		case 1700536: /* ERR_DISPOSITION_NOT_UPDATABLE_FOR_ACCT_TYPE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_disposition_not_updatable_for_acct_type();
			break;
		case 1700550: /* ERR_DUPLICATE_ADDRESS_CODE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_duplicate_address_code();
			break;
		case 1700571: /* ERR_DUPLICATE_SYSTEMATIC */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_duplicate_systematic();
			break;
		case 1700572: /* ERR_DUPLICATE_TRADE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_duplicate_trade();
			break;
		case 1700583: /* ERR_EARLY_DEATH_DATE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_early_death_date();
			break;
		case 1700588: /* ERR_EFF_DATE_LATE_THAN_STOP_DATE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_eff_date_late_than_stop_date();
			break;
		case 1700589: /* ERR_EFF_STOP_DATE_RANGE_OVERLAP */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_eff_stop_date_range_overlap();
			break;
		case 1700591: /* ERR_EFFECTIVE_DATE_BACKWARD */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_effective_date_backward();
			break;
		case 1700593: /* ERR_EFFECTIVE_DATE_CONTRACT_EARLIER_THAN_EFFECTIVE_DATE_MFACCOUNT */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_effective_date_contract_earlier_than_effective_date_mfaccount();
			break;
		case 1700595: /* ERR_EFFECTIVE_DATE_LATE_THAN_STOP_DATE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_effective_date_late_than_stop_date();
			break;
		case 1700596: /* ERR_EFFECTIVE_DATE_MUST_BE_ENTERED */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_effective_date_must_be_entered();
			break;
		case 1700600: /* ERR_EFT_IN_UNITS_NOT_FOR_PURCHASE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_eft_in_units_not_for_purchase();
			break;
		case 1700636: /* ERR_ENTRY_BOTH_FIELDS */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_entry_both_fields();
			break;
		case 1700637: /* ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_entry_empty_or_contains_only_space();
			break;
		case 1700640: /* ERR_ESCROW_AMOUNT_TYPE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_escrow_amount_type();
			break;
		case 1700643: /* ERR_ESCROW_FUND_CLASS_BLANK */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_escrow_fund_class_blank();
			break;
		case 1700644: /* ERR_ESCROW_LOCKED_ALL_UNITS */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_escrow_locked_all_units();
			break;
		case 1700645: /* ERR_ESCROW_LOCKED_PARTIAL_UNITS */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_escrow_locked_partial_units();
			break;
		case 1700646: /* ERR_ESCROW_REP_SHOULD_BE_DELETED */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_escrow_rep_should_be_deleted();
			break;
		case 1700647: /* ERR_ESCROW_REPREZENTATIVE_ENTITY_MUST_BE_SETUP */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_escrow_reprezentative_entity_must_be_setup();
			break;
		case 1700648: /* ERR_ESCROWFUND_CLASS */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_escrowfund_class();
			break;
		case 1700649: /* ERR_ESCROWFUND_ENTITY_TYPE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_escrowfund_entity_type();
			break;
		case 1700664: /* ERR_EXEMPT_HOLDING_EXCESS */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_exempt_holding_excess();
			break;
		case 1700669: /* ERR_FEDERAL_JURISDICTION */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_federal_jurisdiction();
			break;
		case 1700670: /* ERR_FEDERAL_NOT_VALID_TAX */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_federal_not_valid_tax();
			break;
		case 1700686: /* ERR_FEE_MORE_THAN_MAX */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_fee_more_than_max();
			break;
		case 1700709: /* ERR_FIELD_INACTIVE_AS_OF_TRADE_DATE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_field_inactive_as_of_trade_date();
			break;
		case 1700710: /* ERR_FIELD_INVALID_F4_FOR_SEARCH */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_field_invalid_f4_for_search();
			break;
		case 1700711: /* ERR_FIELD_INVALID_F4_FOR_SELECTION */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_field_invalid_f4_for_selection();
			break;
		case 1700713: /* ERR_FIELD_MANDATORY_F4_FOR_SEARCH */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_field_mandatory_f4_for_search();
			break;
		case 1700714: /* ERR_FIELD_MANDATORY_F4_FOR_SELECTION */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_field_mandatory_f4_for_selection();
			break;
		case 1700715: /* ERR_FIELD_REQUIRED_PLS_ENTER */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_field_required_pls_enter();
			break;
		case 1700716: /* ERR_FIELD_REQUIRED_PLS_SELECT */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_field_required_pls_select();
			break;
		case 1700720: /* ERR_FIELDS_MUST_BE_UNIQUE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_fields_must_be_unique();
			break;
		case 1700730: /* ERR_FREQ_DIFF_FROM_DEF */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_freq_diff_from_def();
			break;
		case 1700731: /* ERR_FROM_AFC_MATCH_TO_AFC */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_from_afc_match_to_afc();
			break;
		case 1700749: /* ERR_FULL_WITHDRAW_FOR_OMNIBUS_ACCT */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_full_withdraw_for_omnibus_acct();
			break;
		case 1700761: /* ERR_FUND_CAN_NOT_BE_BLANK */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_fund_can_not_be_blank();
			break;
		case 1700784: /* ERR_FUND_CLASS_NOT_AVAILABLE_FOR_BROKER */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_fund_class_not_available_for_broker();
			break;
		case 1700787: /* ERR_FUND_CLASS_NOT_AVAILABLE_TO_GROUP */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_fund_class_not_available_to_group();
			break;
		case 1700788: /* ERR_FUND_CLASS_NOT_EFFECTIVE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_fund_class_not_effective();
			break;
		case 1700795: /* ERR_FUND_CLASS_STOP_FLAG_ON */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_fund_class_stop_flag_on();
			break;
		case 1700801: /* ERR_FUND_CLASS_XFER_NOT_ALLOWED */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_fund_class_xfer_not_allowed();
			break;
		case 1700813: /* ERR_FUND_INVALID_FOR_REGISTER_ACCOUNT */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_fund_invalid_for_register_account();
			break;
		case 1700819: /* ERR_FUND_NOT_EFFECTIVE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_fund_not_effective();
			break;
		case 1700826: /* ERR_FUND_NOT_RRIF_ELIGIBLE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_fund_not_rrif_eligible();
			break;
		case 1700827: /* ERR_FUND_NOT_RRSP_ELIGIBLE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_fund_not_rrsp_eligible();
			break;
		case 1700829: /* ERR_FUND_OR_ALLOCATION_MUST_ENTER */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_fund_or_allocation_must_enter();
			break;
		case 1700836: /* ERR_FUNDTO_CLASSTO_ACCOUNTTO */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_fundto_classto_accountto();
			break;
		case 1700838: /* ERR_FUNDTO_GIC_NOT_ALLOWED */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_fundto_gic_not_allowed();
			break;
		case 1700839: /* ERR_FUTURE_BIRTHDATE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_future_birthdate();
			break;
		case 1700846: /* ERR_FUTURE_DEATHDATE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_future_deathdate();
			break;
		case 1700856: /* ERR_GIC_PURCHASE_NOT_ALLOWED */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_gic_purchase_not_allowed();
			break;
		case 1700864: /* ERR_GROUP_CODE_LEVEL */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_group_code_level();
			break;
		case 1700865: /* ERR_GROUP_NUMBER_IS_REQUIRED */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_group_number_is_required();
			break;
		case 1700866: /* ERR_GROUP_STOP_FLAG_ON */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_group_stop_flag_on();
			break;
		case 1700882: /* ERR_ID_TYPE_REQUIRED */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_id_type_required();
			break;
		case 1700884: /* ERR_IDENTICAL_ACCT_DEFAULT_ALLOCS */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_identical_acct_default_allocs();
			break;
		case 1700885: /* ERR_IDENTICAL_FUND_ALLOCS */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_identical_fund_allocs();
			break;
		case 1700886: /* ERR_IDENTICAL_SHR_DEFAULT_ALLOCS */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_identical_shr_default_allocs();
			break;
		case 1700889: /* ERR_IDTYPE_MISSING */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_idtype_missing();
			break;
		case 1700891: /* ERR_INACTIVE_SALES_REP */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_inactive_sales_rep();
			break;
		case 1700894: /* ERR_INCORRECT_PRECISION */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_incorrect_precision();
			break;
		case 1700903: /* ERR_INPUT_FUND_DOMESTIC */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_input_fund_domestic();
			break;
		case 1700906: /* ERR_INSTCODE_NOT_EXIST */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_instcode_not_exist();
			break;
		case 1700908: /* ERR_INSTCODE_TOO_BIG */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_instcode_too_big();
			break;
		case 1700934: /* ERR_INVALID_AMTTYPE_FOR_PURCHASE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_invalid_amttype_for_purchase();
			break;
		case 1700937: /* ERR_INVALID_AMTTYPE_FOR_TRADETYPE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_invalid_amttype_for_tradetype();
			break;
		case 1700943: /* ERR_INVALID_CHAR */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_invalid_char();
			break;
		case 1700950: /* ERR_INVALID_CONTRACT_TERM */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_invalid_contract_term();
			break;
		case 1700957: /* ERR_INVALID_EMAIL */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_invalid_email();
			break;
		case 1700964: /* ERR_INVALID_FOR_FOREIGN_CONTENT_TRANSFER */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_invalid_for_foreign_content_transfer();
			break;
		case 1700968: /* ERR_INVALID_FUND_CLASS_CODES */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_invalid_fund_class_codes();
			break;
		case 1700972: /* ERR_INVALID_FUND_NUMBER */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_invalid_fund_number();
			break;
		case 1700981: /* ERR_INVALID_INSTITUTE_CODE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_invalid_institute_code();
			break;
		case 1700989: /* ERR_INVALID_MATURITY_TYPE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_invalid_maturity_type();
			break;
		case 1700991: /* ERR_INVALID_NEGATIVE_AMOUNT */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_invalid_negative_amount();
			break;
		case 1700992: /* ERR_INVALID_NET */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_invalid_net();
			break;
		case 1700996: /* ERR_INVALID_PAY_TYPE_FOR_TRADETYPE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_invalid_pay_type_for_tradetype();
			break;
		case 1701000: /* ERR_INVALID_PENSION */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_invalid_pension();
			break;
		case 1701002: /* ERR_INVALID_POSTAL_CODE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_invalid_postal_code();
			break;
		case 1701003: /* ERR_INVALID_POSTAL_CODE_PROVINCE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_invalid_postal_code_province();
			break;
		case 1701005: /* ERR_INVALID_RANGE_FOR_VALUE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_invalid_range_for_value();
			break;
		case 1701013: /* ERR_INVALID_SETTLEMENT_DATE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_invalid_settlement_date();
			break;
		case 1701019: /* ERR_INVALID_TAX_TYPE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_invalid_tax_type();
			break;
		case 1701020: /* ERR_INVALID_TAX_TYPE_FOR_RESP */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_invalid_tax_type_for_resp();
			break;
		case 1701022: /* ERR_INVALID_TAXTYPE_FOR_PAC_ALLOC */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_invalid_taxtype_for_pac_alloc();
			break;
		case 1701027: /* ERR_INVALID_TRADE_DATE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_invalid_trade_date();
			break;
		case 1701035: /* ERR_IRREVOCABLE_NOT_UPDATABLE_FOR_ACCT_TYPE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_irrevocable_not_updatable_for_acct_type();
			break;
		case 1701037: /* ERR_ITF_ENTITY_SHOULD_BE_SETUP */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_itf_entity_should_be_setup();
			break;
		case 1701038: /* ERR_JOINT_TYPE_NOT_UPDATABLE_FOR_ACCT_TYPE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_joint_type_not_updatable_for_acct_type();
			break;
		case 1701043: /* ERR_LANGUAGE_MUST_BE_ENTERED */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_language_must_be_entered();
			break;
		case 1701044: /* ERR_LAST_NAME_REQUIRED */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_last_name_required();
			break;
		case 1701051: /* ERR_LEGAL_MATURITY_DATE_EARLY_THAN_TODAY */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_legal_maturity_date_early_than_today();
			break;
		case 1701052: /* ERR_LESS_THAN_XII_MONTH */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_less_than_xii_month();
			break;
		case 1701096: /* ERR_MINIMUM_FUND_BALANCE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_minimum_fund_balance();
			break;
		case 1701097: /* ERR_MINIMUM_INIT_AMT */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_minimum_init_amt();
			break;
		case 1701098: /* ERR_MINIMUM_SUBSEQUENT_AMT */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_minimum_subsequent_amt();
			break;
		case 1701118: /* ERR_MOD_ACCT_TYPE_TRANS_EXIST */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_mod_acct_type_trans_exist();
			break;
		case 1701119: /* ERR_MOD_TAX_TYPE_FOR_ACCT_WITH_TRADES */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_mod_tax_type_for_acct_with_trades();
			break;
		case 1701122: /* ERR_MULTIPLE_ACCOUNT_OWNER_ENTITY_SHOULD_SETUP */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_multiple_account_owner_entity_should_setup();
			break;
		case 1701123: /* ERR_MULTIPLE_ACCT_OWNER */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_multiple_acct_owner();
			break;
		case 1701124: /* ERR_MULTIPLE_ACCT_OWNER_NEEDED */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_multiple_acct_owner_needed();
			break;
		case 1701125: /* ERR_MULTIPLE_ANNUITANT */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_multiple_annuitant();
			break;
		case 1701133: /* ERR_MULTIPLE_NOMINEE_NOT_ALLOWED */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_multiple_nominee_not_allowed();
			break;
		case 1701137: /* ERR_MULTIPLE_SPOUSAL */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_multiple_spousal();
			break;
		case 1701138: /* ERR_MUST_BE_BUSINESS_DATE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_must_be_business_date();
			break;
		case 1701151: /* ERR_NET_NOT_FOR_ALLOCATION */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_net_not_for_allocation();
			break;
		case 1701152: /* ERR_NET_NOT_FOR_BEL_FUND */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_net_not_for_bel_fund();
			break;
		case 1701153: /* ERR_NET_NOT_FOR_MULTICURRENCY */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_net_not_for_multicurrency();
			break;
		case 1701163: /* ERR_NEW_ACCT_TERM_AND_DEL */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_new_acct_term_and_del();
			break;
		case 1701169: /* ERR_NO_ACCT_OWNER */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_no_acct_owner();
			break;
		case 1701171: /* ERR_NO_ADDRESSES_FOR_THIS_SHAREHOLDER */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_no_addresses_for_this_shareholder();
			break;
		case 1701172: /* ERR_NO_ALLOC_SYSTEMATIC_ON_CLAN_PLAN */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_no_alloc_systematic_on_clan_plan();
			break;
		case 1701181: /* ERR_NO_DATE_OF_BIRTH */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_no_date_of_birth();
			break;
		case 1701188: /* ERR_NO_FUNDS_FOR_ACCOUNT */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_no_funds_for_account();
			break;
		case 1701199: /* ERR_NO_PENSION_INFORMATION */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_no_pension_information();
			break;
		case 1701203: /* ERR_NO_SALES_REP_EXISTS */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_no_sales_rep_exists();
			break;
		case 1701204: /* ERR_NO_TAX_TYPE_RULES */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_no_tax_type_rules();
			break;
		case 1701207: /* ERR_NO_VALID_DECIMAL_VALUE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_no_valid_decimal_value();
			break;
		case 1701209: /* ERR_NO_VALUE_FOR_ID */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_no_value_for_id();
			break;
		case 1701211: /* ERR_NOMINEE_INVALID_FOR_ACCT_TYPE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_nominee_invalid_for_acct_type();
			break;
		case 1701212: /* ERR_NOMINEE_OWNER_ENTITY_MUST_BE_SETUP */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_nominee_owner_entity_must_be_setup();
			break;
		case 1701213: /* ERR_NOMINEE_REQUIRED */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_nominee_required();
			break;
		case 1701224: /* ERR_NOT_A_RIF_ACCOUNT */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_not_a_rif_account();
			break;
		case 1701228: /* ERR_NOT_CONF_FOR_REBALANCING */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_not_conf_for_rebalancing();
			break;
		case 1701230: /* ERR_NOT_IN_ALLOWABLE_TRANSFER */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_not_in_allowable_transfer();
			break;
		case 1701235: /* ERR_NUMBER_SIN */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_number_sin();
			break;
		case 1701250: /* ERR_ONLY_GIC_PURCHASES_ALLOWED */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_only_gic_purchases_allowed();
			break;
		case 1701252: /* ERR_ONLY_ONE_ACCOUNT_OWNER_ENTITY_IS_ALLOWED */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_only_one_account_owner_entity_is_allowed();
			break;
		case 1701258: /* ERR_ONLY_ONE_PARENT_ENTITY_IS_ALLOWED */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_only_one_parent_entity_is_allowed();
			break;
		case 1701264: /* ERR_ORDER_SRC_INVALID_FOR_WIRE_ORDER */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_order_src_invalid_for_wire_order();
			break;
		case 1701265: /* ERR_ORDER_SRC_MUST_BE_I_FOR_INTERMEDIARY */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_order_src_must_be_i_for_intermediary();
			break;
		case 1701273: /* ERR_PAC_LESS_THAN_MINIMUM_ALLOW */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_pac_less_than_minimum_allow();
			break;
		case 1701275: /* ERR_PAC_SWP_ALLOCATION_REQUIRED */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_pac_swp_allocation_required();
			break;
		case 1701276: /* ERR_PAC_SWP_UNITS_NOT_ALLOWED */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_pac_swp_units_not_allowed();
			break;
		case 1701277: /* ERR_PAC_UNITS_NOT_ALLOWED */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_pac_units_not_allowed();
			break;
		case 1701278: /* ERR_PARENT_ENTITY_SHOULD_BE_SETUP */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_parent_entity_should_be_setup();
			break;
		case 1701281: /* ERR_PARENT_HAS_NOT_BEEN_SETUP */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_parent_has_not_been_setup();
			break;
		case 1701295: /* ERR_PAYTYPE_NOT_AVAIL_FOR_FUND */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_paytype_not_avail_for_fund();
			break;
		case 1701312: /* ERR_PERCENTAGE_LESS_THAN_100 */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_percentage_less_than_100();
			break;
		case 1701313: /* ERR_PERCENTAGE_NOT_EQUAL_100 */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_percentage_not_equal_100();
			break;
		case 1701326: /* ERR_PRIMARY_BENEF_PERCENT_SHOULD_ADD_UP_TO_100 */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_primary_benef_percent_should_add_up_to_100();
			break;
		case 1701336: /* ERR_PURCH_STOPPED_FOR_PAC */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_purch_stopped_for_pac();
			break;
		case 1701354: /* ERR_REASONCODE_COLLATERAL */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_reasoncode_collateral();
			break;
		case 1701355: /* ERR_REASONCODE_RRSP_LOAN */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_reasoncode_rrsp_loan();
			break;
		case 1701369: /* ERR_REDEMP_STOPPED_FOR_SWP */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_redemp_stopped_for_swp();
			break;
		case 1701389: /* ERR_REFNUMBER_NOT_EXIST */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_refnumber_not_exist();
			break;
		case 1701402: /* ERR_RELATE_CODE_REQUIRED */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_relate_code_required();
			break;
		case 1701407: /* ERR_REP_BY_BRANCH_CFG */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rep_by_branch_cfg();
			break;
		case 1701414: /* ERR_RESET_DONE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_reset_done();
			break;
		case 1701419: /* ERR_RESIDENCE_PROVINCE_EMPTY */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_residence_province_empty();
			break;
		case 1701427: /* ERR_RESP_BENEFICIARY_ENTITY_IS_NOT_ALLOWED_FOR_THIS_TAX_TYPE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_resp_beneficiary_entity_is_not_allowed_for_this_tax_type();
			break;
		case 1701428: /* ERR_RESP_BENEFICIARY_ENTITY_MUST_BE_SETUP */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_resp_beneficiary_entity_must_be_setup();
			break;
		case 1701433: /* ERR_RESP_DESIGNATED_INSTIT_ENTITY_SHOULD_BE_SETUP */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_resp_designated_instit_entity_should_be_setup();
			break;
		case 1701447: /* ERR_RIF_AMS_FUND_FUND_CODE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_ams_fund_fund_code();
			break;
		case 1701449: /* ERR_RIF_BAD_RECORD */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_bad_record();
			break;
		case 1701450: /* ERR_RIF_CASH_FUND_CODE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_cash_fund_code();
			break;
		case 1701451: /* ERR_RIF_DIFF_CALC_VALUE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_diff_calc_value();
			break;
		case 1701452: /* ERR_RIF_EMPTY_EFFECTIVE_DATE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_empty_effective_date();
			break;
		case 1701453: /* ERR_RIF_EOM_EFFECTIVE_DATE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_eom_effective_date();
			break;
		case 1701454: /* ERR_RIF_EOM_MONTH_END */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_eom_month_end();
			break;
		case 1701456: /* ERR_RIF_FUTURE_BIRTHDATE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_future_birthdate();
			break;
		case 1701457: /* ERR_RIF_FUTURE_EFFECTIVE_DATE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_future_effective_date();
			break;
		case 1701458: /* ERR_RIF_INVALID_COMBINATION_FUND_CODE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_invalid_combination_fund_code();
			break;
		case 1701461: /* ERR_RIF_INVALID_GROSS_OR_NET */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_invalid_gross_or_net();
			break;
		case 1701462: /* ERR_RIF_INVALID_PAY_OPTION */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_invalid_pay_option();
			break;
		case 1701463: /* ERR_RIF_INVALID_PAY_TYPE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_invalid_pay_type();
			break;
		case 1701464: /* ERR_RIF_INVALID_RATE_PUD */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_invalid_rate_pud();
			break;
		case 1701465: /* ERR_RIF_INVALID_RIF_SRC_OF_FUND */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_invalid_rif_src_of_fund();
			break;
		case 1701466: /* ERR_RIF_MANDATORY_MIN_WITH_AGE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_mandatory_min_with_age();
			break;
		case 1701467: /* ERR_RIF_MANDATORY_PAY_TYPE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_mandatory_pay_type();
			break;
		case 1701469: /* ERR_RIF_MONTH */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_month();
			break;
		case 1701470: /* ERR_RIF_NEGATIVE_AMOUNT */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_negative_amount();
			break;
		case 1701471: /* ERR_RIF_NO_FLAG_ON_FUND_CODE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_no_flag_on_fund_code();
			break;
		case 1701472: /* ERR_RIF_NO_MAXIMUM_PAY_OPTION */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_no_maximum_pay_option();
			break;
		case 1701473: /* ERR_RIF_NO_PAYMENT_MONTH_END */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_no_payment_month_end();
			break;
		case 1701474: /* ERR_RIF_NO_SHAREHOLDER_BIRTHDATE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_no_shareholder_birthdate();
			break;
		case 1701475: /* ERR_RIF_NON_100_TOTAL_PERCENTAGE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_non_100_total_percentage();
			break;
		case 1701476: /* ERR_RIF_NON_FRACTIONAL */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_non_fractional();
			break;
		case 1701477: /* ERR_RIF_NON_ZERO_INDEX_RATE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_non_zero_index_rate();
			break;
		case 1701478: /* ERR_RIF_NON_ZERO_RATE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_non_zero_rate();
			break;
		case 1701479: /* ERR_RIF_NOT_MIN_AMOUNT */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_not_min_amount();
			break;
		case 1701480: /* ERR_RIF_NOT_UNIQUE_FUND_CODE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_not_unique_fund_code();
			break;
		case 1701481: /* ERR_RIF_ONLY_ONE_GOOD_RECORD */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_only_one_good_record();
			break;
		case 1701482: /* ERR_RIF_OUT_OF_LIMITS_ALLOC_AMOUNT */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_out_of_limits_alloc_amount();
			break;
		case 1701483: /* ERR_RIF_OUT_OF_LIMITS_PERCENTAGE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_out_of_limits_percentage();
			break;
		case 1701484: /* ERR_RIF_OUT_OF_RANGE_INDEX_RATE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_out_of_range_index_rate();
			break;
		case 1701485: /* ERR_RIF_PAST_EFFECTIVE_DATE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_past_effective_date();
			break;
		case 1701487: /* ERR_RIF_QUALIFIED */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_qualified();
			break;
		case 1701488: /* ERR_RIF_SPOUSE_OLDER_BIRTHDATE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_spouse_older_birthdate();
			break;
		case 1701490: /* ERR_RIF_STOP_RED_NOT_OFF_FUND_CODE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_stop_red_not_off_fund_code();
			break;
		case 1701491: /* ERR_RIF_SUM_TOO_BIG1_RATE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_sum_too_big1_rate();
			break;
		case 1701492: /* ERR_RIF_SUM_TOO_BIG2_RATE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_sum_too_big2_rate();
			break;
		case 1701493: /* ERR_RIF_TOO_BIG_AMOUNT */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_too_big_amount();
			break;
		case 1701494: /* ERR_RIF_TOO_BIG_MAND_AMT_YR */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_too_big_mand_amt_yr();
			break;
		case 1701495: /* ERR_RIF_TOO_BIG_MAX_AMT_YR */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_too_big_max_amt_yr();
			break;
		case 1701496: /* ERR_RIF_TOO_BIG_MIN_WITH_AGE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_too_big_min_with_age();
			break;
		case 1701497: /* ERR_RIF_TOO_BIG_RATE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_too_big_rate();
			break;
		case 1701498: /* ERR_RIF_TOO_MANY_DECIMALS_RATE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_too_many_decimals_rate();
			break;
		case 1701499: /* ERR_RIF_TOO_MANY_FUND_CODE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_too_many_fund_code();
			break;
		case 1701500: /* ERR_RIF_TOO_SMALL_AMOUNT */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_too_small_amount();
			break;
		case 1701501: /* ERR_RIF_TOO_SMALL_MAX_AMT_YR */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_too_small_max_amt_yr();
			break;
		case 1701502: /* ERR_RIF_UNKNOWN_ADDRESS_CODE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_unknown_address_code();
			break;
		case 1701505: /* ERR_RIF_WRONG_CURRENCY_FUND_CODE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_wrong_currency_fund_code();
			break;
		case 1701506: /* ERR_RIF_WRONG_RATE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_wrong_rate();
			break;
		case 1701507: /* ERR_RIF_WRONG_STOP_DATE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_wrong_stop_date();
			break;
		case 1701508: /* ERR_RIF_WRONG_VALUE_MAND_AMT_YR */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_wrong_value_mand_amt_yr();
			break;
		case 1701509: /* ERR_RIF_ZERO_ALLOC_AMOUNT */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_zero_alloc_amount();
			break;
		case 1701510: /* ERR_RIF_ZERO_OR_NEGATIVE_AMOUNT */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_rif_zero_or_negative_amount();
			break;
		case 1701529: /* ERR_SALES_REP_EMPTY */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_sales_rep_empty();
			break;
		case 1701530: /* ERR_SALESPERSON_IS_NOT_PERMITTED */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_salesperson_is_not_permitted();
			break;
		case 1701534: /* ERR_SAME_FROM_TO_FUND_CLASS_NOT_ALLOW */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_same_from_to_fund_class_not_allow();
			break;
		case 1701540: /* ERR_SECONDARY_BENEF_PERCENT_SHOULD_ADD_UP_TO_100 */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_secondary_benef_percent_should_add_up_to_100();
			break;
		case 1701541: /* ERR_SECONDARY_BENEFICIARY_ENTITY_ONLY_ALLOWED_IF_PRIMARY_ENTITY_EXIST */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_secondary_beneficiary_entity_only_allowed_if_primary_entity_exist();
			break;
		case 1701569: /* ERR_SHAREHOLDER_BELOW_69 */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_shareholder_below_69();
			break;
		case 1701571: /* ERR_SHAREHOLDER_NUM_CANNOT_BE_LEFT_EMPTY */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_shareholder_num_cannot_be_left_empty();
			break;
		case 1701572: /* ERR_SHAREHOLDER_NUMBER_CANNOT_START_WITH_ZERO */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_shareholder_number_cannot_start_with_zero();
			break;
		case 1701573: /* ERR_SHAREHOLDER_NUMBER_EMPTY */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_shareholder_number_empty();
			break;
		case 1701574: /* ERR_SHAREHOLDER_NUMBER_EXISTS */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_shareholder_number_exists();
			break;
		case 1701602: /* ERR_SPOUSAL_CONTRIBUTOR_ENTITY_SHOULD_BE_SETUP */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_spousal_contributor_entity_should_be_setup();
			break;
		case 1701603: /* ERR_SPOUSAL_INVALID_FOR_ACCT_TYPE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_spousal_invalid_for_acct_type();
			break;
		case 1701619: /* ERR_STATUS_CHANGED */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_status_changed();
			break;
		case 1701620: /* ERR_STATUS_IS_BLANK */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_status_is_blank();
			break;
		case 1701627: /* ERR_STOP_DATE_LESS_THAN_DEFF */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_stop_date_less_than_deff();
			break;
		case 1701629: /* ERR_STOP_FLAG_ACTIVE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_stop_flag_active();
			break;
		case 1701630: /* ERR_STOP_FLAG_ACTIVE_IGNORED */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_stop_flag_active_ignored();
			break;
		case 1701641: /* ERR_SUM_OF_PERCENTAGES_NOT_100 */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_sum_of_percentages_not_100();
			break;
		case 1701645: /* ERR_SWIFTCODE_NOT_EXIST */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_swiftcode_not_exist();
			break;
		case 1701647: /* ERR_SWP_FUND_BLANK */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_swp_fund_blank();
			break;
		case 1701648: /* ERR_SWP_LESS_THAN_MINIMUM_ALLOW */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_swp_less_than_minimum_allow();
			break;
		case 1701653: /* ERR_SYS_DEFF_LESS_THAN_ACCT_DEFF */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_sys_deff_less_than_acct_deff();
			break;
		case 1701663: /* ERR_TAX_JURIS_EMPTY */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_tax_juris_empty();
			break;
		case 1701667: /* ERR_TAX_TYPE_EMTPY */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_tax_type_emtpy();
			break;
		case 1701671: /* ERR_TAX_TYPE_NO_NON_REGISTER */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_tax_type_no_non_register();
			break;
		case 1701706: /* ERR_TRADE_DATE_IN_PRIOR_YEAR */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_trade_date_in_prior_year();
			break;
		case 1701708: /* ERR_TRADE_DATE_NOT_VALUATION_DATE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_trade_date_not_valuation_date();
			break;
		case 1701712: /* ERR_TRADE_FOR_PRIOR_TAX_YEAR */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_trade_for_prior_tax_year();
			break;
		case 1701731: /* ERR_TRANSFER_EXCH_STOPPED_FOR_AT */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_transfer_exch_stopped_for_at();
			break;
		case 1701737: /* ERR_TRANSFER_TAX_TYPE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_transfer_tax_type();
			break;
		case 1701745: /* ERR_TRANSITNO_NOT_EXIST */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_transitno_not_exist();
			break;
		case 1701747: /* ERR_TRANSITNO_TOO_BIG */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_transitno_too_big();
			break;
		case 1701751: /* ERR_TRUSTEE_ENTITY_SHOULD_BE_SETUP */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_trustee_entity_should_be_setup();
			break;
		case 1701752: /* ERR_TRUSTEE_INVALID_FOR_ACCT_TYPE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_trustee_invalid_for_acct_type();
			break;
		case 1701758: /* ERR_TWO_DECIMAL_POINT_ONLY */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_two_decimal_point_only();
			break;
		case 1701764: /* ERR_UNIT_NOT_FOR_ALLOCATION */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_unit_not_for_allocation();
			break;
		case 1701782: /* ERR_USER_MATURITY_DATE_EMPTY */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_user_maturity_date_empty();
			break;
		case 1701783: /* ERR_VALUE_BETWEEN_0_AND_100 */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_value_between_0_and_100();
			break;
		case 1701786: /* ERR_VALUE_CANNOT_BE_ZERO */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_value_cannot_be_zero();
			break;
		case 1701788: /* ERR_VALUE_NOT_EQUAL_100_PER */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_value_not_equal_100_per();
			break;
		case 1701795: /* ERR_W_INVALID_SIN */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_w_invalid_sin();
			break;
		case 1701893: /* ERR_WIRE_ORDER_NOT_ALLOWED_FOR_FUND */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_wire_order_not_allowed_for_fund();
			break;
		case 1701894: /* ERR_WIRE_ORDER_NUM_MUST_BE_NUMERIC */
			conditionObj = new CIFast_Infrastructure_ifastcbo_err_wire_order_num_must_be_numeric();
			break;
		case 1701906: /* INFO_SHAREHOLDER_HAS_MULTIPLE_ADDRESSES */
			conditionObj = new CIFast_Infrastructure_ifastcbo_info_shareholder_has_multiple_addresses();
			break;
		case 1702187: /* WARN_INVALID_PROVINCE */
			conditionObj = new CIFast_Infrastructure_ifastcbo_warn_invalid_province();
			break;
		case 1702253: /* WARN_PAC_LESS_THAN_MINIMUM_ALLOW */
			conditionObj = new CIFast_Infrastructure_ifastcbo_warn_pac_less_than_minimum_allow();
			break;
		case 1800003: /* ERR_ACCESS_DENIED_NO_SESSION_RECORD */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_access_denied_no_session_record();
			break;
		case 1800004: /* ERR_ACCESS_DENIED_PASS_LOGOFF_TIME */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_access_denied_pass_logoff_time();
			break;
		case 1800005: /* ERR_ACCESS_DENIED_PASSWORD_MUST_BE_RESET */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_access_denied_password_must_be_reset();
			break;
		case 1800009: /* ERR_ACCOUNT_ENTITY_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_account_entity_not_found();
			break;
		case 1800011: /* ERR_ACCOUNT_MAY_ONLY_HAVE_ONE_NOMINEE_OWNER */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_account_may_only_have_one_nominee_owner();
			break;
		case 1800012: /* ERR_ACCOUNT_NUMBER_IS_INVALID */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_account_number_is_invalid();
			break;
		case 1800020: /* ERR_ACCOUNTENTITY_ALREADY_EXISTS */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_accountentity_already_exists();
			break;
		case 1800021: /* ERR_ACCOUNTENTITY_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_accountentity_not_found();
			break;
		case 1800025: /* ERR_ACCT_ENTITY_BENEF_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_acct_entity_benef_not_found();
			break;
		case 1800026: /* ERR_ACCT_ENTITY_JOINT_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_acct_entity_joint_not_found();
			break;
		case 1800037: /* ERR_ACCT_UPDATE_FAILED_AS_ACCTENTITY_UPDATE_FAILED */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_acct_update_failed_as_acctentity_update_failed();
			break;
		case 1800042: /* ERR_AD_AFTER_MANDATORY_LOGOFF_TIME */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_ad_after_mandatory_logoff_time();
			break;
		case 1800043: /* ERR_AD_BEFORE_ALLOWABLE_LOGON_TIME */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_ad_before_allowable_logon_time();
			break;
		case 1800044: /* ERR_AD_INVALID_PASSWORD */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_ad_invalid_password();
			break;
		case 1800045: /* ERR_AD_INVALID_PROFILE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_ad_invalid_profile();
			break;
		case 1800046: /* ERR_AD_MAXIMUM_SESSIONS_ALREADY_RUNNING */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_ad_maximum_sessions_already_running();
			break;
		case 1800047: /* ERR_AD_NO_COMPANY_ACCESS */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_ad_no_company_access();
			break;
		case 1800048: /* ERR_AD_PAST_PASSWORD_GRACE_PERIOD */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_ad_past_password_grace_period();
			break;
		case 1800049: /* ERR_AD_PROFLE_HAS_NO_ACCESS_TODAY */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_ad_profle_has_no_access_today();
			break;
		case 1800050: /* ERR_AD_SHAREHOLDER_DOES_NOT_EXIST */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_ad_shareholder_does_not_exist();
			break;
		case 1800051: /* ERR_AD_TOO_MANY_FAILED_LOGONS */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_ad_too_many_failed_logons();
			break;
		case 1800052: /* ERR_AD_UNKNOWN_ACCESS_PROFILE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_ad_unknown_access_profile();
			break;
		case 1800053: /* ERR_AD_UNKNOWN_USER */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_ad_unknown_user();
			break;
		case 1800054: /* ERR_AD_USER_ACCOUNT_NOT_ACTIVE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_ad_user_account_not_active();
			break;
		case 1800055: /* ERR_AD_USER_HAS_NO_COMPANY_ACCESS */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_ad_user_has_no_company_access();
			break;
		case 1800057: /* ERR_ADDRESS_CODE_AT_LEAST_TWO */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_address_code_at_least_two();
			break;
		case 1800058: /* ERR_ADDRESS_USED_FOR_MAILING */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_address_used_for_mailing();
			break;
		case 1800059: /* ERR_ADDRID_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_addrid_not_found();
			break;
		case 1800064: /* ERR_ALLFUNDS_OR_FUND_CLASSCODE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_allfunds_or_fund_classcode();
			break;
		case 1800069: /* ERR_AMOUNT_GREATER */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_amount_greater();
			break;
		case 1800071: /* ERR_AMOUNT_SHOULD_MANDATORY */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_amount_should_mandatory();
			break;
		case 1800086: /* ERR_APARTMENT_NUM_MISSING */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_apartment_num_missing();
			break;
		case 1800087: /* ERR_AS_OF_DATE_WAS_NOT_ENTERED */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_as_of_date_was_not_entered();
			break;
		case 1800088: /* ERR_ASSIGN_INFO_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_assign_info_not_found();
			break;
		case 1800095: /* ERR_BANK_ACC_EXCEEDS */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_bank_acc_exceeds();
			break;
		case 1800096: /* ERR_BANK_ACC_MUST_BE_ENTERED */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_bank_acc_must_be_entered();
			break;
		case 1800097: /* ERR_BANK_ACC_NUMERIC */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_bank_acc_numeric();
			break;
		case 1800101: /* ERR_BANK_RECORD_SHOULD */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_bank_record_should();
			break;
		case 1800103: /* ERR_BANKACCT_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_bankacct_not_found();
			break;
		case 1800105: /* ERR_BANKMST_UNAVAILABLE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_bankmst_unavailable();
			break;
		case 1800107: /* ERR_BATCH_CANNOT_BE_BLANK */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_batch_cannot_be_blank();
			break;
		case 1800111: /* ERR_BATCH_NOT_ACTIVE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_batch_not_active();
			break;
		case 1800112: /* ERR_BATCHES_NOT_MATCH */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_batches_not_match();
			break;
		case 1800113: /* ERR_BATCHNAME_CANNOT_BLANK */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_batchname_cannot_blank();
			break;
		case 1800114: /* ERR_BATCHNAME_SHOULD_BLANK */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_batchname_should_blank();
			break;
		case 1800116: /* ERR_BATCHTYPE_INVALID */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_batchtype_invalid();
			break;
		case 1800118: /* ERR_BOX_NUM_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_box_num_not_found();
			break;
		case 1800127: /* ERR_BROKER_NOT_ELIGIBLE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_broker_not_eligible();
			break;
		case 1800130: /* ERR_BROKER_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_broker_not_found();
			break;
		case 1800157: /* ERR_CANNOT_DELETE_ACCOWNER */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_cannot_delete_accowner();
			break;
		case 1800166: /* ERR_CANNOT_PRINT_DUPLICATE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_cannot_print_duplicate();
			break;
		case 1800171: /* ERR_CHEQUE_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_cheque_not_found();
			break;
		case 1800173: /* ERR_CLAN_PLAN_NOT_AVAILABLE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_clan_plan_not_available();
			break;
		case 1800176: /* ERR_CLIENT_ACCOUNT_CANNOT_HAVE_A_NOMINEE_OWNER */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_client_account_cannot_have_a_nominee_owner();
			break;
		case 1800178: /* ERR_CLOSEACCTCODE_NOT_FUND */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_closeacctcode_not_fund();
			break;
		case 1800190: /* ERR_CONTRACT_RECORD_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_contract_record_not_found();
			break;
		case 1800192: /* ERR_CONTROLS_NAME_RECORD_ENTITYID_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_controls_name_record_entityid_not_found();
			break;
		case 1800193: /* ERR_COULD_NOT_CREATE_THE_SHAREHOLDER_REMARKS_RECORD */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_could_not_create_the_shareholder_remarks_record();
			break;
		case 1800197: /* ERR_CYCLE_RUN_UNAVAILABLE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_cycle_run_unavailable();
			break;
		case 1800202: /* ERR_DATA_PROBLEM_MISSING_PRICE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_data_problem_missing_price();
			break;
		case 1800203: /* ERR_DATABASE_NOT_CONNECTED */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_database_not_connected();
			break;
		case 1800204: /* ERR_DATABASE_UNAVAILABLE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_database_unavailable();
			break;
		case 1800205: /* ERR_DATE_OF_BIRTH_MANDATORY */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_date_of_birth_mandatory();
			break;
		case 1800208: /* ERR_DEALER_FUNDS_NA */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_dealer_funds_na();
			break;
		case 1800216: /* ERR_DISTRIB_NA */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_distrib_na();
			break;
		case 1800218: /* ERR_DISTRIBANK_IS_LOCKED */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_distribank_is_locked();
			break;
		case 1800219: /* ERR_DISTRIBANK_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_distribank_not_found();
			break;
		case 1800220: /* ERR_DISTRIBUTION_IS_LOCKED */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_distribution_is_locked();
			break;
		case 1800221: /* ERR_DISTRIBUTION_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_distribution_not_found();
			break;
		case 1800229: /* ERR_DUPLICATE_AUTO_TRANSFER */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_duplicate_auto_transfer();
			break;
		case 1800231: /* ERR_DUPLICATE_DISTRIBUTION */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_duplicate_distribution();
			break;
		case 1800235: /* ERR_EFT_PAYMENT_DETAILS_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_eft_payment_details_not_found();
			break;
		case 1800246: /* ERR_ENTITY_ADDR_NA */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_entity_addr_na();
			break;
		case 1800247: /* ERR_ENTITY_ADDR_XREF_NA */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_entity_addr_xref_na();
			break;
		case 1800248: /* ERR_ENTITY_NOT_ASSOCIATED_WITH_AN_ACCOUNT */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_entity_not_associated_with_an_account();
			break;
		case 1800249: /* ERR_ENTITY_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_entity_not_found();
			break;
		case 1800251: /* ERR_ENTITYTYPE_MUST_POPULATED */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_entitytype_must_populated();
			break;
		case 1800255: /* ERR_ERROR_UPD_BANK_TABLE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_error_upd_bank_table();
			break;
		case 1800274: /* ERR_FEE_RECORD_NA */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_fee_record_na();
			break;
		case 1800281: /* ERR_FINANCIAL_TIMEZONE_INVALID */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_financial_timezone_invalid();
			break;
		case 1800290: /* ERR_FULL_REDEMPTION_NOT_ALLOWED */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_full_redemption_not_allowed();
			break;
		case 1800299: /* ERR_FUND_INFO_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_fund_info_not_found();
			break;
		case 1800303: /* ERR_FUND_RECORD_NA */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_fund_record_na();
			break;
		case 1800320: /* ERR_IDENTIFICATION_RECORD_NOT_EXIST */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_identification_record_not_exist();
			break;
		case 1800325: /* ERR_INPUT_ACCOUNT_IS_NOT_RESP */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_input_account_is_not_resp();
			break;
		case 1800326: /* ERR_INPUT_ACCOUNT_IS_NOT_RIF */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_input_account_is_not_rif();
			break;
		case 1800327: /* ERR_INST_CODE_EXCEEDS */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_inst_code_exceeds();
			break;
		case 1800330: /* ERR_INSUFFICIENT_INFO */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_insufficient_info();
			break;
		case 1800335: /* ERR_INTERMEDIARY_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_intermediary_not_found();
			break;
		case 1800342: /* ERR_INVALID_ADDRESS */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_invalid_address();
			break;
		case 1800352: /* ERR_INVALID_CALLNUM */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_invalid_callnum();
			break;
		case 1800354: /* ERR_INVALID_CHUIR */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_invalid_chuir();
			break;
		case 1800355: /* ERR_INVALID_CLASS_CODE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_invalid_class_code();
			break;
		case 1800360: /* ERR_INVALID_DEPOSIT_ID */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_invalid_deposit_id();
			break;
		case 1800361: /* ERR_INVALID_DEPOSIT_TYPE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_invalid_deposit_type();
			break;
		case 1800366: /* ERR_INVALID_FUND_AND_CLASS */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_invalid_fund_and_class();
			break;
		case 1800367: /* ERR_INVALID_FUND_CODE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_invalid_fund_code();
			break;
		case 1800368: /* ERR_INVALID_FUND_GROUP_TYPE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_invalid_fund_group_type();
			break;
		case 1800370: /* ERR_INVALID_GROUP */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_invalid_group();
			break;
		case 1800371: /* ERR_INVALID_GROUP_CODE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_invalid_group_code();
			break;
		case 1800372: /* ERR_INVALID_ID_TYPE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_invalid_id_type();
			break;
		case 1800376: /* ERR_INVALID_MRS_ACCOUNT */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_invalid_mrs_account();
			break;
		case 1800384: /* ERR_INVALID_PROFILE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_invalid_profile();
			break;
		case 1800388: /* ERR_INVALID_REQUEST_TYPE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_invalid_request_type();
			break;
		case 1800397: /* ERR_INVALID_SHAREHOLDER */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_invalid_shareholder();
			break;
		case 1800398: /* ERR_INVALID_SORT_BY */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_invalid_sort_by();
			break;
		case 1800410: /* ERR_JOINT_INFORMATION_ONLY_FOR_JOINT_ACCOUNTS */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_joint_information_only_for_joint_accounts();
			break;
		case 1800420: /* ERR_MANAGEMENT_COMPANY_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_management_company_not_found();
			break;
		case 1800422: /* ERR_MATURITY_DATE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_maturity_date();
			break;
		case 1800429: /* ERR_MISSING_ALLOCATION_INFO */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_missing_allocation_info();
			break;
		case 1800438: /* ERR_MULITIPLE_ADDRESS */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_mulitiple_address();
			break;
		case 1800449: /* ERR_NEXT_KEY_DID_NOT_MATCH_EXPECTED_FORMAT */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_next_key_did_not_match_expected_format();
			break;
		case 1800450: /* ERR_NO_ACCESS_TO_SLSREP */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_no_access_to_slsrep();
			break;
		case 1800451: /* ERR_NO_ACCOUNT_SHR_NUMBER */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_no_account_shr_number();
			break;
		case 1800452: /* ERR_NO_ACCOUNTHOLDING */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_no_accountholding();
			break;
		case 1800453: /* ERR_NO_ACCT_CONTRACT_AVAILABLE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_no_acct_contract_available();
			break;
		case 1800456: /* ERR_NO_ACTIVE_BATCH */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_no_active_batch();
			break;
		case 1800459: /* ERR_NO_ADDRESS_RECORD_AVAILABLE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_no_address_record_available();
			break;
		case 1800463: /* ERR_NO_BENEFICIARY_RECORD_AVAILABLE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_no_beneficiary_record_available();
			break;
		case 1800464: /* ERR_NO_BRANCH_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_no_branch_found();
			break;
		case 1800466: /* ERR_NO_CLAN_PLAN_UPDATE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_no_clan_plan_update();
			break;
		case 1800468: /* ERR_NO_COMPANY_RECORD */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_no_company_record();
			break;
		case 1800469: /* ERR_NO_CONTRACTMSTR */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_no_contractmstr();
			break;
		case 1800470: /* ERR_NO_COT_CONTRACT_SHGROUP */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_no_cot_contract_shgroup();
			break;
		case 1800475: /* ERR_NO_ENOUGH_INPUT */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_no_enough_input();
			break;
		case 1800477: /* ERR_NO_ESCROW_REP_RECORD_AVAILABLE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_no_escrow_rep_record_available();
			break;
		case 1800482: /* ERR_NO_FUTURE_DATE_MIN_MAX */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_no_future_date_min_max();
			break;
		case 1800483: /* ERR_NO_INTEREST_ACCRUAL_INFORMATION_AVAILABLE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_no_interest_accrual_information_available();
			break;
		case 1800485: /* ERR_NO_JOINT_ENTITY_RECORD_AVAILABLE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_no_joint_entity_record_available();
			break;
		case 1800486: /* ERR_NO_MAILING_INFO_AVAILABLE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_no_mailing_info_available();
			break;
		case 1800487: /* ERR_NO_MATCHES_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_no_matches_found();
			break;
		case 1800489: /* ERR_NO_PENDING_RESP_TRADES */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_no_pending_resp_trades();
			break;
		case 1800490: /* ERR_NO_PENDING_TRADES_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_no_pending_trades_found();
			break;
		case 1800493: /* ERR_NO_PROCESSED_RESP_TRADES */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_no_processed_resp_trades();
			break;
		case 1800494: /* ERR_NO_PROCESSED_TRADES_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_no_processed_trades_found();
			break;
		case 1800496: /* ERR_NO_PURCHASE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_no_purchase();
			break;
		case 1800497: /* ERR_NO_RELATED_CHUI_FUNCTIONS */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_no_related_chui_functions();
			break;
		case 1800498: /* ERR_NO_RESP_ACCOUNT_INFORMATION */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_no_resp_account_information();
			break;
		case 1800500: /* ERR_NO_RIF_ALLOCATION_INFO */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_no_rif_allocation_info();
			break;
		case 1800501: /* ERR_NO_RIF_SETUP_INFO */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_no_rif_setup_info();
			break;
		case 1800502: /* ERR_NO_SETUP_RECORD */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_no_setup_record();
			break;
		case 1800504: /* ERR_NO_SLSREP_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_no_slsrep_found();
			break;
		case 1800505: /* ERR_NO_TAXTYPE_AVAILABLE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_no_taxtype_available();
			break;
		case 1800508: /* ERR_NO_UNIQE_NAME_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_no_uniqe_name_found();
			break;
		case 1800510: /* ERR_NO_USERID */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_no_userid();
			break;
		case 1800517: /* ERR_NON_JOINT_ACCOUNT_ONE_ACCOUNTHOLDER */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_non_joint_account_one_accountholder();
			break;
		case 1800518: /* ERR_NOT_AN_EFT_TRANSACTION */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_not_an_eft_transaction();
			break;
		case 1800521: /* ERR_NOT_CONFIGURED */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_not_configured();
			break;
		case 1800523: /* ERR_NOT_ENOUGH_INPUT_INFO_FOR_RECORD_SELECTION */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_not_enough_input_info_for_record_selection();
			break;
		case 1800526: /* ERR_NOT_VALID_FUND */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_not_valid_fund();
			break;
		case 1800535: /* ERR_ORIGTRANSLD_MUST_BLANK */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_origtransld_must_blank();
			break;
		case 1800539: /* ERR_PASSWORD_DENIED_CHANGE_NO_ALLOWED */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_password_denied_change_no_allowed();
			break;
		case 1800550: /* ERR_PD_CANNOT_CHANGE_PASSORD_FOR */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_pd_cannot_change_passord_for();
			break;
		case 1800551: /* ERR_PD_HAS_BEEN_USED_RECENTLY_CHOOSE_ANOTHER */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_pd_has_been_used_recently_choose_another();
			break;
		case 1800552: /* ERR_PD_NEED_TWO_OR_MORE_ALPHABETIC_CHARS */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_pd_need_two_or_more_alphabetic_chars();
			break;
		case 1800553: /* ERR_PD_NEED_TWO_OR_MORE_NON_ALPHA_CHARS */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_pd_need_two_or_more_non_alpha_chars();
			break;
		case 1800554: /* ERR_PD_NO_BLANKS_ALLOWED */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_pd_no_blanks_allowed();
			break;
		case 1800555: /* ERR_PD_OLD_PASSWORD_INCORRECT */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_pd_old_password_incorrect();
			break;
		case 1800556: /* ERR_PD_ONLY_ONE_REPETITION_OF_CHARS_ALLOWED */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_pd_only_one_repetition_of_chars_allowed();
			break;
		case 1800557: /* ERR_PD_ONLY_SEVEN_CHARS_IN_A_ROW */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_pd_only_seven_chars_in_a_row();
			break;
		case 1800558: /* ERR_PD_PASSWORD_CAN_ONLY_BE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_pd_password_can_only_be();
			break;
		case 1800559: /* ERR_PD_PASSWORD_MUST_BE_AT_LEAST */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_pd_password_must_be_at_least();
			break;
		case 1800560: /* ERR_PD_THREE_OF_SAME_CHARS_NOT_ALLOWED */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_pd_three_of_same_chars_not_allowed();
			break;
		case 1800561: /* ERR_PD_UNKNOWN_ACCESS_PROFILE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_pd_unknown_access_profile();
			break;
		case 1800562: /* ERR_PD_UNKNOWN_USER */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_pd_unknown_user();
			break;
		case 1800564: /* ERR_PENDING_TRADE_BANK_INVALID */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_pending_trade_bank_invalid();
			break;
		case 1800566: /* ERR_PENDING_TRADE_NOT_EXISTS */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_pending_trade_not_exists();
			break;
		case 1800567: /* ERR_PENDING_TRADE_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_pending_trade_not_found();
			break;
		case 1800568: /* ERR_PENSION_INFORMATION_NA */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_pension_information_na();
			break;
		case 1800570: /* ERR_PERSISTENT_FREERESP_FAILED */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_persistent_freeresp_failed();
			break;
		case 1800571: /* ERR_PERSISTENT_NEEDED */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_persistent_needed();
			break;
		case 1800575: /* ERR_PLEASE_SEND_AGAIN_AS_LAST_RECORD_WAS_DELETED */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_please_send_again_as_last_record_was_deleted();
			break;
		case 1800576: /* ERR_POSTAL_CODE_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_postal_code_not_found();
			break;
		case 1800582: /* ERR_PROGRESS_ERROR */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_progress_error();
			break;
		case 1800585: /* ERR_PROVINCE_FILE_NA */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_province_file_na();
			break;
		case 1800594: /* ERR_RECORD_LOCKED */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_record_locked();
			break;
		case 1800600: /* ERR_REDEMPTIONCODE_NOT_AVAILABLE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_redemptioncode_not_available();
			break;
		case 1800601: /* ERR_REGISTER_ADDRESS_NOT_AVAILABLE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_register_address_not_available();
			break;
		case 1800602: /* ERR_REGISTERED_ADDRESS_DEFAULT_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_registered_address_default_not_found();
			break;
		case 1800605: /* ERR_REMARKS_NO_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_remarks_no_found();
			break;
		case 1800624: /* ERR_RRIF_ALREADY_EXISTS */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_rrif_already_exists();
			break;
		case 1800625: /* ERR_RRIF_DETAIL_RECID_INVALID */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_rrif_detail_recid_invalid();
			break;
		case 1800626: /* ERR_RRIFINFO_ALREADY_EXISTS */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_rrifinfo_already_exists();
			break;
		case 1800633: /* ERR_RUN_MODE_INVALID */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_run_mode_invalid();
			break;
		case 1800637: /* ERR_SALESREP_CANNOT_ACCESS_THIS_ACCOUNT */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_salesrep_cannot_access_this_account();
			break;
		case 1800641: /* ERR_SEARCH_FOR_SLSREP_BY_BROKER_CODE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_search_for_slsrep_by_broker_code();
			break;
		case 1800644: /* ERR_SECURITY_SETUP_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_security_setup_not_found();
			break;
		case 1800650: /* ERR_SEQNUM_NOT_EXIST */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_seqnum_not_exist();
			break;
		case 1800662: /* ERR_SHAREHOLDER_NUMBER_GREATER_THEN_ZERO */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_shareholder_number_greater_then_zero();
			break;
		case 1800663: /* ERR_SHAREHOLDER_NUMBER_NOT_GREATER_THEN_SIX_DIGITS */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_shareholder_number_not_greater_then_six_digits();
			break;
		case 1800696: /* ERR_STREET_NAME_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_street_name_not_found();
			break;
		case 1800704: /* ERR_TAX_TYPES_RULES_NOT_SET_UP */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_tax_types_rules_not_set_up();
			break;
		case 1800708: /* ERR_THIS_TAX_TYPE_NOT_LOCKED_IN */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_this_tax_type_not_locked_in();
			break;
		case 1800709: /* ERR_TIME_ZONE_INVALID */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_time_zone_invalid();
			break;
		case 1800718: /* ERR_TRADE_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_trade_not_found();
			break;
		case 1800739: /* ERR_TRANSACTION_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_transaction_not_found();
			break;
		case 1800741: /* ERR_TRANSACTION_TYPE_INVALID */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_transaction_type_invalid();
			break;
		case 1800748: /* ERR_TRANSIT_NO_EXCEEDS */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_transit_no_exceeds();
			break;
		case 1800750: /* ERR_TRANSNUM_ALREADY_EXISTS */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_transnum_already_exists();
			break;
		case 1800757: /* ERR_UNABLE_ASSIGN_CONNUM */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_unable_assign_connum();
			break;
		case 1800758: /* ERR_UNABLE_MODIFY_COT_ACCT_CONTRACT */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_unable_modify_cot_acct_contract();
			break;
		case 1800761: /* ERR_UNABLE_TO_ADD_RECORD_ACCOUNT_EXISTS */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_unable_to_add_record_account_exists();
			break;
		case 1800762: /* ERR_UNABLE_TO_ADD_RECORD_ADDRESS_EXISTS */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_unable_to_add_record_address_exists();
			break;
		case 1800763: /* ERR_UNABLE_TO_ADD_RECORD_SHAREHOLDER_EXISTS */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_unable_to_add_record_shareholder_exists();
			break;
		case 1800764: /* ERR_UNABLE_TO_DELETE_ENTITY */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_unable_to_delete_entity();
			break;
		case 1800765: /* ERR_UNABLE_TO_DELETE_LAST_ADDRESS */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_unable_to_delete_last_address();
			break;
		case 1800766: /* ERR_UNABLE_TO_DELETE_RECORD */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_unable_to_delete_record();
			break;
		case 1800769: /* ERR_UNABLE_TO_MODIFY_ENTITY */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_unable_to_modify_entity();
			break;
		case 1800771: /* ERR_UNABLE_TO_UPDATE_RECORD */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_unable_to_update_record();
			break;
		case 1800773: /* ERR_UNITDETL_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_unitdetl_not_found();
			break;
		case 1800774: /* ERR_UNITS_NOT_ALLOWED */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_units_not_allowed();
			break;
		case 1800775: /* ERR_UNKNOW_RESPONSE_TYPE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_unknow_response_type();
			break;
		case 1800776: /* ERR_UNKNOWN_ACCOUNT */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_unknown_account();
			break;
		case 1800777: /* ERR_UNKNOWN_ERROR */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_unknown_error();
			break;
		case 1800781: /* ERR_UNKNOWN_START_DATE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_unknown_start_date();
			break;
		case 1800783: /* ERR_USER_ACCESS_RECORD_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_user_access_record_not_found();
			break;
		case 1800791: /* ERR_USER_STATUS_IS_INACTIVE_IN_COMPANY_DB */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_user_status_is_inactive_in_company_db();
			break;
		case 1800806: /* ERR_WITHOUT_FULL_REDEMPTION */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_without_full_redemption();
			break;
		case 1800807: /* ERR_WRONG_BANK_VERSION */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_wrong_bank_version();
			break;
		case 1800809: /* ERR_WRONG_DISTRIBUTION_VERSION */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_wrong_distribution_version();
			break;
		case 1800811: /* ERR_WRONG_SHRHOLDER_VERSION */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_err_wrong_shrholder_version();
			break;
		case 1800813: /* IFASTDBRKR_ALREADY_LOGGED_ON */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_ifastdbrkr_already_logged_on();
			break;
		case 1800855: /* IFASTDBRKR_INVALID_WIDE_CHARACTER */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_ifastdbrkr_invalid_wide_character();
			break;
		case 1800856: /* IFASTDBRKR_NOT_LOGGED_ON */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_ifastdbrkr_not_logged_on();
			break;
		case 1800857: /* IFASTDBRKR_SEND_FAILED */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_ifastdbrkr_send_failed();
			break;
		case 1800858: /* IFASTDBRKR_TRANS_FAILED */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_ifastdbrkr_trans_failed();
			break;
		case 1800859: /* IFASTDBRKR_UNEXPECTED_END_OF_STREAM_FILE */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_ifastdbrkr_unexpected_end_of_stream_file();
			break;
		case 1800860: /* IFASTDBRKR_UNKNOWN_ERROR */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_ifastdbrkr_unknown_error();
			break;
		case 1800861: /* IFASTDBRKR_VMREQ_FAILED */
			conditionObj = new CIFast_Infrastructure_ifastdbrkr_ifastdbrkr_vmreq_failed();
			break;
		case 1800873: /* ERR_INVALID_VALUATION_DATE_FOR_FUND_CLASS */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_Invalid_Valuation_Date_For_Fund_Class();
			break;
		case 1800874: /* ERR_ACCOUNT_ALREADY_IN_MAIL_HOUSEHOLD */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_account_already_mail_household();
			break;
		case 1800875: /* ERR_ACCOUNT_NOT_ASSOCIATED */
			conditionObj = new CIFast_IFast_ifastdbrkr_err_account_not_associated();
			break;
        case 1800876: /* ERR_COPY_FAIL_EXPIRED_FEE_MODEL */
            conditionObj = new CIFast_IFast_ifastdbrkr_err_copy_fail_expired_fee_model();
            break;
		case 1900011: /* GUI_AWD_NODATA */
			conditionObj = new CIFast_Infrastructure_ifastgui_gui_awd_nodata();
			break;
		case 1900012: /* GUI_AWD_NOT_LOGGED_ON */
			conditionObj = new CIFast_Infrastructure_ifastgui_gui_awd_not_logged_on();
			break;
		case 1900013: /* GUI_AWD_NOT_SETUP */
			conditionObj = new CIFast_Infrastructure_ifastgui_gui_awd_not_setup();
			break;
		case 1900015: /* GUI_AWD_SYSTEM_CHANGED */
			conditionObj = new CIFast_Infrastructure_ifastgui_gui_awd_system_changed();
			break;
		case 1900016: /* GUI_AWD_SYSTEM_ERROR */
			conditionObj = new CIFast_Infrastructure_ifastgui_gui_awd_system_error();
			break;
		case 1900017: /* GUI_ENCORR_ALREADY_ACTIVE */
			conditionObj = new CIFast_Infrastructure_ifastgui_gui_encorr_already_active();
			break;
		case 1900018: /* GUI_ENCORR_ERROR_MALLOC */
			conditionObj = new CIFast_Infrastructure_ifastgui_gui_encorr_error_malloc();
			break;
		case 1900019: /* GUI_ENCORR_OLE_ERROR */
			conditionObj = new CIFast_Infrastructure_ifastgui_gui_encorr_ole_error();
			break;
		case 1900020: /* GUI_ERR_AWD_PROFILE_REQUIRED */
			conditionObj = new CIFast_Infrastructure_ifastgui_gui_err_awd_profile_required();
			break;
		case 1900021: /* GUI_ERR_COMMAND_NOT_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastgui_gui_err_command_not_found();
			break;
		case 1900023: /* GUI_ERR_DIALOG_CREATE_FAILED */
			conditionObj = new CIFast_Infrastructure_ifastgui_gui_err_dialog_create_failed();
			break;
		case 1900025: /* GUI_ERR_INVALID_FIELD_ENTRY */
			conditionObj = new CIFast_Infrastructure_ifastgui_gui_err_invalid_field_entry();
			break;
		case 1900026: /* GUI_ERR_NOT_PROFILE */
			conditionObj = new CIFast_Infrastructure_ifastgui_gui_err_not_profile();
			break;
		case 1900027: /* GUI_ERR_PROFILE_SELECTION_FAILED */
			conditionObj = new CIFast_Infrastructure_ifastgui_gui_err_profile_selection_failed();
			break;
		case 1900029: /* GUI_FORMS_ALREADY_ACTIVE */
			conditionObj = new CIFast_Infrastructure_ifastgui_gui_forms_already_active();
			break;
		case 1900030: /* GUI_FORMS_ERROR_MALLOC */
			conditionObj = new CIFast_Infrastructure_ifastgui_gui_forms_error_malloc();
			break;
		case 1900031: /* GUI_FORMS_OLE_ERROR */
			conditionObj = new CIFast_Infrastructure_ifastgui_gui_forms_ole_error();
			break;
		case 1900034: /* GUI_MGMTCO_ERR_NO_MANAGEMENT_COMPANIES_FOUND */
			conditionObj = new CIFast_Infrastructure_ifastgui_gui_mgmtco_err_no_management_companies_found();
			break;
		case 1900035: /* GUI_NEW_PASSWORD_CONFIRMATION_NO_MATCH */
			conditionObj = new CIFast_Infrastructure_ifastgui_gui_new_password_confirmation_no_match();
			break;
		case 1900038: /* GUI_NO_ENTITY_IN_LIST */
			conditionObj = new CIFast_Infrastructure_ifastgui_gui_no_entity_in_list();
			break;
		case 1900041: /* GUI_NO_OPERATOR_ID_ENTERED */
			conditionObj = new CIFast_Infrastructure_ifastgui_gui_no_operator_id_entered();
			break;
		case 1900042: /* GUI_NO_PASSWORD_ENTERED */
			conditionObj = new CIFast_Infrastructure_ifastgui_gui_no_password_entered();
			break;
		case 1900043: /* GUI_SEARCH_CRITERIAS_NOT_DEFINED1 */
			conditionObj = new CIFast_Infrastructure_ifastgui_gui_search_criterias_not_defined1();
			break;
		case 1900044: /* GUI_SEARCH_CRITERIAS_NOT_DEFINED2 */
			conditionObj = new CIFast_Infrastructure_ifastgui_gui_search_criterias_not_defined2();
			break;
		case 1900046: /* GUI_SEARCH_ENCORR_DISPATCH */
			conditionObj = new CIFast_Infrastructure_ifastgui_gui_search_encorr_dispatch();
			break;
		case 1900047: /* GUI_SEARCH_ENCORR_NAMES */
			conditionObj = new CIFast_Infrastructure_ifastgui_gui_search_encorr_names();
			break;
		case 1900048: /* GUI_SEARCH_FORMS_CLASS */
			conditionObj = new CIFast_Infrastructure_ifastgui_gui_search_forms_class();
			break;
		case 1900049: /* GUI_SEARCH_FORMS_FACTORY */
			conditionObj = new CIFast_Infrastructure_ifastgui_gui_search_forms_factory();
			break;
		case 1900050: /* GUI_SEARCH_FORMS_ID */
			conditionObj = new CIFast_Infrastructure_ifastgui_gui_search_forms_id();
			break;
		case 1900051: /* GUI_SECURITY_VIOLATION */
			conditionObj = new CIFast_Infrastructure_ifastgui_gui_security_violation();
			break;
		case 1900052: /* GUI_WRAPUP_ERR_MUST_ENTER_BATC */
			conditionObj = new CIFast_Infrastructure_ifastgui_gui_wrapup_err_must_enter_batc();
			break;
		case 1900053: /* GUI_WRAPUP_ERR_MUST_ENTER_STAT */
			conditionObj = new CIFast_Infrastructure_ifastgui_gui_wrapup_err_must_enter_stat();
			break;
		case 1900054: /* GUI_WRAPUP_ERR_MUST_ENTER_UNIT */
			conditionObj = new CIFast_Infrastructure_ifastgui_gui_wrapup_err_must_enter_unit();
			break;
		case 1900055: /* GUI_WRAPUP_ERR_MUST_ENTER_WRKT */
			conditionObj = new CIFast_Infrastructure_ifastgui_gui_wrapup_err_must_enter_wrkt();
			break;
		case 1900056: /* GUI_WRAPUP_ERR_UNIT_CHANGED */
			conditionObj = new CIFast_Infrastructure_ifastgui_gui_wrapup_err_unit_changed();
			break;
		case 2200002: /* ERR_ACTION_UNIDENTIFIABLE */
			conditionObj = new CIFast_Infrastructure_vision_err_action_unidentifiable();
			break;
		case 2200004: /* ERR_MISSING_USER_WK_ID */
			conditionObj = new CIFast_Infrastructure_vision_err_missing_user_wk_id();
			break;
		case 2200005: /* ERR_NO_DATA_FOR_CRT_THREAD */
			conditionObj = new CIFast_Infrastructure_vision_err_no_data_for_crt_thread();
			break;
		case 2200006: /* ERR_NO_DATA_FOUND */
			conditionObj = new CIFast_Infrastructure_vision_err_no_data_found();
			break;
		case 2200007: /* ERR_NO_INITIALIZED_SERVICE */
			conditionObj = new CIFast_Infrastructure_vision_err_no_initialized_service();
			break;
		case 2200008: /* ERR_NO_PASSWORD */
			conditionObj = new CIFast_Infrastructure_vision_err_no_password();
			break;
		case 2200009: /* ERR_NO_SEARCH_CRITERIA */
			conditionObj = new CIFast_Infrastructure_vision_err_no_search_criteria();
			break;
		case 2200010: /* ERR_NO_SEARCH_USING */
			conditionObj = new CIFast_Infrastructure_vision_err_no_search_using();
			break;
		case 2200011: /* ERR_NO_SEARCH_VALUE */
			conditionObj = new CIFast_Infrastructure_vision_err_no_search_value();
			break;
		case 2200012: /* ERR_NO_SERVICE_TO_END */
			conditionObj = new CIFast_Infrastructure_vision_err_no_service_to_end();
			break;
		case 2200013: /* ERR_NO_USER_SESSION */
			conditionObj = new CIFast_Infrastructure_vision_err_no_user_session();
			break;
		case 2200014: /* ERR_NO_WORK_SESSION */
			conditionObj = new CIFast_Infrastructure_vision_err_no_work_session();
			break;
		case 2200015: /* ERR_NOT_ABLE_TO_PERFORM */
			conditionObj = new CIFast_Infrastructure_vision_err_not_able_to_perform();
			break;
		case 2200016: /* ERR_PARSING_ERROR */
			conditionObj = new CIFast_Infrastructure_vision_err_parsing_error();
			break;
		case 2200017: /* ERR_REQUEST_UNIDENTIFIABLE */
			conditionObj = new CIFast_Infrastructure_vision_err_request_unidentifiable();
			break;
		case 2200018: /* ERR_SERVER_RESPONSE */
			conditionObj = new CIFast_Infrastructure_vision_err_server_response();
			break;
		case 2200019: /* ERR_UNKNOWN_SERVICE */
			conditionObj = new CIFast_Infrastructure_vision_err_unknown_service();
			break;
        default:
			//assert(0);
			break;
	}

	return conditionObj;
};

void CConditionBuilder::CheckForOverrides(CConditionObject* pConditionObject, const DString& strDataFolderPath)
{
    DString strConditionName = pConditionObject->GetConditionName();
    DString strConditionFileName = strConditionName + I_(".json");
    DString strConditionFileFullPath = strDataFolderPath + I_("\\") + strConditionFileName;

    std::ifstream conditionFile(strConditionFileFullPath.c_str(), std::ifstream::binary);

    if (conditionFile)
    {
        Json::Value root;   // will contain the root value after parsing.
        Json::Reader reader;

        bool parsingSuccessful = reader.parse(conditionFile, root, false);
        if (parsingSuccessful)
        {
            DString condition_name = root["condition"].get("condition_name", "" ).asString();
            DString client_name = root["condition"].get("client_name", "" ).asString();
            DString market_name = root["condition"].get("market_name", "" ).asString();
            DString group_name = root["condition"].get("group_name", "" ).asString();
            DString module_name = root["condition"].get("module_name", "" ).asString();

            int severity = root["condition"].get("severity", -1 ).asInt();
            int suppress = root["condition"].get("suppress", 0 ).asInt();

            DString message_en_us = root["condition"]["messages"].get("en_us", "" ).asString();
            DString message_fr_fr = root["condition"]["messages"].get("fr_fr", "" ).asString();
            DString message_de_de = root["condition"]["messages"].get("de_de", "" ).asString();
            DString message_es_es = root["condition"]["messages"].get("es_es", "" ).asString();
            DString message_fr_ca = root["condition"]["messages"].get("fr_ca", "" ).asString();
            DString message_nl_nl = root["condition"]["messages"].get("nl_nl", "" ).asString();

            DString action_en_us = root["condition"]["actions"].get("en_us", "" ).asString();
            DString action_fr_fr = root["condition"]["actions"].get("fr_fr", "" ).asString();
            DString action_de_de = root["condition"]["actions"].get("de_de", "" ).asString();
            DString action_es_es = root["condition"]["actions"].get("es_es", "" ).asString();
            DString action_fr_ca = root["condition"]["actions"].get("fr_ca", "" ).asString();
            DString action_nl_nl = root["condition"]["actions"].get("nl_nl", "" ).asString();

            if (condition_name == pConditionObject->GetConditionName() &&
                client_name == pConditionObject->GetClientName() &&
                market_name == pConditionObject->GetMarketName())
            {
                // Set general overrides
                if (severity != -1)
                {
                    pConditionObject->SetSeverityOverride(severity);
                }

                // Set message overrides
                if (message_en_us != I_(""))
                {
                    pConditionObject->SetMessageOverride_EN_US(message_en_us);
                }

                if (message_fr_fr != I_(""))
                {
                    pConditionObject->SetMessageOverride_FR_FR(message_fr_fr);
                }

                if (message_de_de != I_(""))
                {
                    pConditionObject->SetMessageOverride_DE_DE(message_de_de);
                }

                if (message_es_es != I_(""))
                {
                    pConditionObject->SetMessageOverride_ES_ES(message_es_es);
                }

                if (message_fr_ca != I_(""))
                {
                    pConditionObject->SetMessageOverride_FR_CA(message_fr_ca);
                }

                if (message_nl_nl != I_(""))
                {
                    pConditionObject->SetMessageOverride_NL_NL(message_nl_nl);
                }

                // Set action overrides
                if (action_en_us != I_(""))
                {
                    pConditionObject->SetActionOverride_EN_US(action_en_us);
                }

                if (action_fr_fr != I_(""))
                {
                    pConditionObject->SetActionOverride_FR_FR(action_fr_fr);
                }

                if (action_de_de != I_(""))
                {
                    pConditionObject->SetActionOverride_DE_DE(action_de_de);
                }

                if (action_es_es != I_(""))
                {
                    pConditionObject->SetActionOverride_ES_ES(action_es_es);
                }

                if (action_fr_ca != I_(""))
                {
                    pConditionObject->SetActionOverride_FR_CA(action_fr_ca);
                }

                if (action_nl_nl != I_(""))
                {
                    pConditionObject->SetActionOverride_NL_NL(action_nl_nl);
                }
            }
        }
    }
}