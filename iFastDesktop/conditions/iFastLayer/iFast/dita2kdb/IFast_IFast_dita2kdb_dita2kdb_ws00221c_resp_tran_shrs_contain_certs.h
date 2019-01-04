#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_tran_shrs_contain_certs : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_tran_shrs_contain_certs() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_tran_shrs_contain_certs() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_TRAN_SHRS_CONTAIN_CERTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount Type must be Dollars for full Transfers.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Amount Type must be Dollars for full Transfers.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Betragstyp für volle Transfers muss Dollars sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo de monto debe ser dólares para transacciones totales")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de montant doit être Dollars pour les transferts totaux.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bedragtype moet Dollar zijn voor volledige overdrachten")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("please re-select")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("please re-select")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Bitte wählen Sie neu aus.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("please re-select")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez recommencer la sélection.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("selecteer opnieuw")); }
	};
}



