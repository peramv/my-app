#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_vision_err_no_data_for_crt_thread : public CConditionObject
	{
	public:
		CIFast_IFast_vision_err_no_data_for_crt_thread() { }
		~CIFast_IFast_vision_err_no_data_for_crt_thread() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_DATA_FOR_CRT_THREAD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("vision")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Current thread doesn't have an entry in the map")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Current thread doesn't have an entry in the map")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der aktuelle Thread hat keinen Map-Eintrag.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La secuencia actual no tiene una entrada en el mapa")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'unité d'exécution actuelle n'a pas d'entrée dans l'application.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Huidige thread staat niet in de folder")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assistance technique.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker")); }
	};
}



