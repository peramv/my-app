#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_diawdi_diawdi_logon_user_disabled : public CConditionObject
	{
	public:
		CBase_Ifds_diawdi_diawdi_logon_user_disabled() { }
		~CBase_Ifds_diawdi_diawdi_logon_user_disabled() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIAWDI_LOGON_USER_DISABLED")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("diawdi")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Negative record count attribute")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("E-Mail-Format wurde nicht erkannt. E-Mail-Adressen sollten folgendes Format haben „name@domainname.dnssearchorder“, z.B.: \"my.name@mydomain.com\"")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Negative record count attribute")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Attribut compte d'enregistrement négatif")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Negative record count attribute")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check system")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Check system")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Check system")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le système.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Check system")); }
	};
}



