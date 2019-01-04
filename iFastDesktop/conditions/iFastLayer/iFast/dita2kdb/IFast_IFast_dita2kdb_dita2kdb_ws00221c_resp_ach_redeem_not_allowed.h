#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_ach_redeem_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_ach_redeem_not_allowed() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_ach_redeem_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_ACH_REDEEM_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Partial units of the fund and class have been assigned.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Certaines unites du fonds et de la catégorie ont ete attribuees.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Einige Anteile der Fonds -und Klassen-Anteile wurden zugewiesen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se han cedido parte de las unidades del fondo y clase.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les unités partielles du fonds et de la classe ont été mises en garantie.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gedeeltelijke eenheden van het fonds en de categorie zijn toegekend")); }

        // Actions
	};
}



