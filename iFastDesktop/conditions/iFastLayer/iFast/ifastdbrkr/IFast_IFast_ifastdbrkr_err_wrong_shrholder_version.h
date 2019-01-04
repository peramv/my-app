#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_wrong_shrholder_version : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_wrong_shrholder_version() { }
		~CIFast_IFast_ifastdbrkr_err_wrong_shrholder_version() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WRONG_SHRHOLDER_VERSION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Shareholder record has been updated since inquiry, please refresh and try again.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("L'enregistrement de l'actionnaire a ete mis a jour depuis la consultation, veuillez rafraichir et reessayer.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt eine Aktualisierung des Aktionär-Eintrags seit der Anfrage. Führen Sie bitte eine Aktualisierung durch und versuchen Sie es erneut.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El registro de accionista se ha actualizado desde la consulta, por favor actualice la pantalla y vuelva a intentarlo")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement de l'actionnaire a été mis à jour depuis la requête. Veuillez rafraîchir la page et réessayer.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Aandeelhouderrecord is bijgewerkt sinds de informatieaanvraag, vernieuw de pagina en probeer het opnieuw")); }

        // Actions
	};
}



