#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_bfbase_err_unknown_exception : public CConditionObject
	{
	public:
		CBase_Ifds_bfbase_err_unknown_exception() { }
		~CBase_Ifds_bfbase_err_unknown_exception() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNKNOWN_EXCEPTION")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("bfbase")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem. Unknown exception caught.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Probleme interne. Exception inconnue identifiee.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fonds %FUNDNAME% ist nicht wirksam. Bitte wählen Sie einen anderen Fonds.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Unable to parse request -- possible invalid encoding declaration.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. Une exception inconnue a été détectée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Unable to parse request -- possible invalid encoding declaration.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Contact a support representative and report this message.")); }
	};
}



