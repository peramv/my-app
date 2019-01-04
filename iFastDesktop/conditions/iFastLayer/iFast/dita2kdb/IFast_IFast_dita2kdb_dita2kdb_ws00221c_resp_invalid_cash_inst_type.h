#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_cash_inst_type : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_cash_inst_type() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_cash_inst_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_CASH_INST_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Escrow Representative Entity must be setup for Escrow Account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Escrow Reprezentative Entity must be setup for Escrow Account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Escrow-Repräsentant-Objekt muss für ein Escrow-(Ander)konto erstellt sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe configurarse entidad Representante de custodia para la cuenta de custodia")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le cessionnaire doit être créé pour le compte cédé en garantie.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Eenheid pandvertegenwoordiger moet worden ingesteld voor het pandaccount")); }

        // Actions
	};
}



