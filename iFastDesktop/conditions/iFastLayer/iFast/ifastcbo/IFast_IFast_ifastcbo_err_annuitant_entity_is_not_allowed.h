#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_annuitant_entity_is_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_annuitant_entity_is_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_annuitant_entity_is_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ANNUITANT_ENTITY_IS_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
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



