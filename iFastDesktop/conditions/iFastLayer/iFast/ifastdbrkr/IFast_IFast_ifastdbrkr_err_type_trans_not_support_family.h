#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_type_trans_not_support_family : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_type_trans_not_support_family() { }
		~CIFast_IFast_ifastdbrkr_err_type_trans_not_support_family() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TYPE_TRANS_NOT_SUPPORT_FAMILY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This type of transaction is not supported for Family Plan RESP.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Diese Art von Transaktion wird nicht für Familienplan-RESP verwendet.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("This type of transaction is not supported for Family Plan RESP.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Ce type de transaction n'est pas supporté pour le REEE familial.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Dit type transactie wordt niet ondersteund voor Family Plan RESP")); }

        // Actions
	};
}



