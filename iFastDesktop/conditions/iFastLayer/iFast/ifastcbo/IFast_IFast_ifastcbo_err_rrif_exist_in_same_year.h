#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rrif_exist_in_same_year : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rrif_exist_in_same_year() { }
		~CIFast_IFast_ifastcbo_err_rrif_exist_in_same_year() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RRIF_EXIST_IN_SAME_YEAR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only one RRIF record with Good status is allowed for the same year.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Nur ein RRIF-Eintrag mit \"Gut\"-Status für das gleiche Jahr ist erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Sólo se permite un registro RRIF con estado Válido para el mismo año.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un seul enregistrement FERR avec un statut Bon est autorisé pour la même année.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is slechts één RRIF-record met de status Goed toegestaan voor hetzelfde jaar")); }

        // Actions
	};
}



