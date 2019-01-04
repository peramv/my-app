#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_early_death_date : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_early_death_date() { }
		~CIFast_Infrastructure_ifastcbo_err_early_death_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EARLY_DEATH_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AWD logon was successful.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("AWD logon was successful.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AWD-Anmeldung war erfolgreich.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La conexión con AWD fue exitosa.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Échec d'ouverture de session AWD")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Aanmelden bij AWD is gelukt")); }

        // Actions
	};
}



