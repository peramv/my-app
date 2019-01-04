﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_wrong_distribution_version : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_wrong_distribution_version() { }
		~CIFast_IFast_ifastdbrkr_err_wrong_distribution_version() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WRONG_DISTRIBUTION_VERSION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Distribution has been updated since inquiry, please refresh and try again.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Distribution has been updated since inquiry, please refresh and try again.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt eine Aktualisierung des Verteilungs-Eintrag seit der Anfrage, bitte aktualisieren Sie und versuchen Sie es erneut.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La distribución se ha actualizado desde la consulta, por favor actualice la pantalla y vuelva a intentarlo")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La distribution a été mise à jour depuis la requête. Veuillez rafraîchir la page et réessayer.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Distributie is bijgewerkt sinds de informatieaanvraag, vernieuw de pagina en probeer het opnieuw")); }

        // Actions
	};
}



