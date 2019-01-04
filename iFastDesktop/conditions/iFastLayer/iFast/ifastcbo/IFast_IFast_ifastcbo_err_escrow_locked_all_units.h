#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_escrow_locked_all_units : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_escrow_locked_all_units() { }
		~CIFast_IFast_ifastcbo_err_escrow_locked_all_units() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ESCROW_LOCKED_ALL_UNITS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("All units of the Fund and Class units have been assigned.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Toutes les unites des unites du Fonds et de la catégorie ont ete affectees.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Alle Anteile der Fonds -und der Klassen-Anteile wurden zugewiesen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se han asignado todas las unidades del fondo y la clase.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Toutes les unités parmi celles du fonds et de la classe ont été mises en garantie.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Alle eenheden van de fonds- en categorie-eenheden zijn toegewezen")); }

        // Actions
	};
}



