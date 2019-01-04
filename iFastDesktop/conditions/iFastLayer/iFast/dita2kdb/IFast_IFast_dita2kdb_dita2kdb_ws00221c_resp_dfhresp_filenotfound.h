#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_filenotfound : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_filenotfound() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_filenotfound() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_DFHRESP_FILENOTFOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount type must be 'Amount' for Multi-Currrency purchase.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Le type de montant doit être \"Montant\" pour les souscriptions multidevises")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Betragsart muss “Betrag” sein für Mehrfach-Währungskauf.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo de monto debe ser 'Monto' para la compra en varias divisas")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de montant doit être Montant pour un achat multidevises.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bedragtype moet 'Bedrag' zijn voor aankoop van meerdere valuta")); }

        // Actions
	};
}



