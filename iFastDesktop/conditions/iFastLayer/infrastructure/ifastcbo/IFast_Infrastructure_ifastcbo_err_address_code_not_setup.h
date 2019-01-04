#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_address_code_not_setup : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_address_code_not_setup() { }
		~CIFast_Infrastructure_ifastcbo_err_address_code_not_setup() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ADDRESS_CODE_NOT_SETUP")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There are no additional repeat records available.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There are no additional repeat records available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt keine zusätzlichen Wiederholungseinträge.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay registros repetidos adicionales disponibles.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il n'y a aucun enregistrement de répétition supplémentaire disponible.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen extra herhalingsrecords beschikbaar")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



