#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_status_is_blank : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_status_is_blank() { }
		~CIFast_IFast_ifastcbo_err_status_is_blank() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_STATUS_IS_BLANK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Blank is not permitted for Status.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Blank is not pernitted for Status.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Status darf nicht leer sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite un campo vacío para estado.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ Statut doit être rempli.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Spatie is niet toegestaan voor status")); }

        // Actions
	};
}



