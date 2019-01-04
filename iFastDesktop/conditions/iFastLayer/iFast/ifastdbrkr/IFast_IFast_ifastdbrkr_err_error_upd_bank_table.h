#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_error_upd_bank_table : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_error_upd_bank_table() { }
		~CIFast_IFast_ifastdbrkr_err_error_upd_bank_table() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ERROR_UPD_BANK_TABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Error occured updating bank table.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Error occured updating bank table.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Beim Aktualisieren der Banktabelle ist ein Fehler aufgetreten.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se produjo un error al actualizar la tabla de bancos")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une erreur s'est produite lors de la mise à jour de la table bancaire.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een fout opgetreden bij het bijwerken van de banktabel")); }

        // Actions
	};
}



