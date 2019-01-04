#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_printer_records_avail : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_printer_records_avail() { }
		~CIFast_IFast_ifastdbrkr_err_no_printer_records_avail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_PRINTER_RECORDS_AVAIL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No printer records available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keine Drucker-Einträge verfügbar")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay registros de impresora disponibles.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun enregistrement d'imprimante disponible")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen printerrecords beschikbaar")); }

        // Actions
	};
}



