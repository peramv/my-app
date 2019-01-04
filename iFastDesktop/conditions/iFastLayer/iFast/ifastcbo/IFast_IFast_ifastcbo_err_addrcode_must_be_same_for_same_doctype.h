#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_addrcode_must_be_same_for_same_doctype : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_addrcode_must_be_same_for_same_doctype() { }
		~CIFast_IFast_ifastcbo_err_addrcode_must_be_same_for_same_doctype() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ADDRCODE_MUST_BE_SAME_FOR_SAME_DOCTYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Address codes can not be different for the %DOCTYPE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Adresscodes können für %DOCTYPE% nicht verschieden sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Los códigos de dirección no pueden ser diferentes para el %DOCTYPE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les codes d'adresse ne peuvent être différents pour %DOCTYPE%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Adrescodes kunnen niet verschillend zijn voor het documenttype %DOCTYPE%")); }

        // Actions
	};
}



