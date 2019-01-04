#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dicbocore_err_unable_to_retrieve_label_data : public CConditionObject
	{
	public:
		CBase_Ifds_dicbocore_err_unable_to_retrieve_label_data() { }
		~CBase_Ifds_dicbocore_err_unable_to_retrieve_label_data() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNABLE_TO_RETRIEVE_LABEL_DATA")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem. Failed to create dialog %DIALOG%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem. Failed to create dialog %DIALOG%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Neues Konto kann mit einem Beendet- oder Gelöscht-Status nicht erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("There is an internal problem. Failed to create dialog %DIALOG%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. Échec de création du dialogue %DIALOG%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem. Dialoog %DIALOG% kon niet worden gemaakt.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht.")); }
	};
}



