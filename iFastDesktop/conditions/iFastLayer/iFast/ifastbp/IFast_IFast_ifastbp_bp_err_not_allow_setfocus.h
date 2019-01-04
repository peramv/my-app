#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastbp_bp_err_not_allow_setfocus : public CConditionObject
	{
	public:
		CIFast_IFast_ifastbp_bp_err_not_allow_setfocus() { }
		~CIFast_IFast_ifastbp_bp_err_not_allow_setfocus() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_ERR_NOT_ALLOW_SETFOCUS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastbp")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is uncommitted data.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Il reste des donnees non enregistrees.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ungebundene Daten.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay datos no comprometidos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a des données non sauvegardées.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn niet-vastgelegde gegevens")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Commit data and repeat action")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Enregistrez les donnees et reiterez l'action.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Bestätigen Sie die Daten und wiederholen Sie den Vorgang")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Commit data and repeat action")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Sauvegardez les données et répétez l'action.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Voer gegevens in en herhaal de actie")); }
	};
}



