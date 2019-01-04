#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_bank_acct_nbr : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_bank_acct_nbr() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_bank_acct_nbr() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_BANK_ACCT_NBR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Annuitant Entity is not allowed for this tax type.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Annuitant Entity is not allowed for this tax type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Rentenempfänger-Objekt ist nicht zugelassen für diese Steuerart.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite la entidad Titular de anualidad para este tipo tributario")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le crédirentier n'est pas autorisé pour ce type d'imposition.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Eenheid lijfrentetrekker is niet toegestaan voor dit belastingtype")); }

        // Actions
	};
}



