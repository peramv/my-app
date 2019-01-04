#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_connect_lost : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_connect_lost() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_connect_lost() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_CONNECT_LOST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Either Account Number or Shareholder Number must be entered.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Either Account Number or Shareholder Number must be entered.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es muss entweder Kontonummer oder Aktionärs-Nummer eingegeben werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe introducirse el número de cuenta o el número de accionista.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro de compte ou d'actionnaire est requis.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Accoutnummer of aandeelhoudersnummer moet worden ingevoerd")); }

        // Actions
	};
}



