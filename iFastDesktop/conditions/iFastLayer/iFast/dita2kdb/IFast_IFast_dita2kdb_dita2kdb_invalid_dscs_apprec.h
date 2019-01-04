#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_invalid_dscs_apprec : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_invalid_dscs_apprec() { }
		~CIFast_IFast_dita2kdb_dita2kdb_invalid_dscs_apprec() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_DSCS_APPREC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("EFT payment details not found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("EFT payment details not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("EFT (Elektronischer Fondstransfer)-Zahlungsdetails nicht gefunden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontraron los detalles de pago EFT")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les détails de paiement TEF sont introuvables.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De EFO-betalingsdetails zijn niet aangetroffen")); }

        // Actions
	};
}



