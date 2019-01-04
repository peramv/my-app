#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_unable_to_delete_last_address : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_unable_to_delete_last_address() { }
		~CIFast_IFast_ifastdbrkr_err_unable_to_delete_last_address() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNABLE_TO_DELETE_LAST_ADDRESS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to delete last remaining Address for Shareholder.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Unable to delete last remaining Address for Shareholder.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Letzte bleibende Adresse für Aktionär kann nicht gelöscht werden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Imposible eliminar la última dirección que queda para el accionista")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de supprimer la dernière adresse restante pour l'actionnaire.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Verwijderen van het laatste overgebleven adres van aandeelhouder is niet mogelijk")); }

        // Actions
	};
}



