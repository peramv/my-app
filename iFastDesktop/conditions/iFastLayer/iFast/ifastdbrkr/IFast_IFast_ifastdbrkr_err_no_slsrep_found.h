#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_slsrep_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_slsrep_found() { }
		~CIFast_IFast_ifastdbrkr_err_no_slsrep_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_SLSREP_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Sales Representative Code does not exist.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Aucun conseiller financier exist avec les co-ordonnées que vous avez spécifié")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Verkaufsvertreter-Code existiert nicht. Bitte geben Sie neu ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código de representante de ventas no existe. Por favor vuelva a introducir los datos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de représentant des ventes inexistant")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Vertegenwoordigerscode bestaat niet. Vul opnieuw in")); }

        // Actions
	};
}



