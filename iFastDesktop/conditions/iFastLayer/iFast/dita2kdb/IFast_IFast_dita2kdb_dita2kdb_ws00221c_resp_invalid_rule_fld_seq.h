#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_rule_fld_seq : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_rule_fld_seq() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_rule_fld_seq() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_RULE_FLD_SEQ")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Federal is not valid as a tax jurisdiction.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Federal is not valid as a tax jurisdiction.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("\"Bundes..\" ist als Steuerzuständigkeit nicht gültig.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Federal no es válido como jurisdicción tributaria")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Fédérale n'est pas une juridiction fiscale valide.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Federaal is niet geldig als belastingrechtsgebied")); }

        // Actions
	};
}



