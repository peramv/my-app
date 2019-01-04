#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_alloc_type_is_blank : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_alloc_type_is_blank() { }
		~CIFast_IFast_ifastcbo_err_alloc_type_is_blank() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ALLOC_TYPE_IS_BLANK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Allocation Type cannot be blank.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zuweisungsart darf nicht leer sein. Wählen Sie einen Zuweisungstyp.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo de asignación no puede estar en blanco. Por favor seleccione un tipo de asignación.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ Type de répartition doit être rempli.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Allocatietype kan niet leeg zijn. Selecteer een allocatietype")); }

        // Actions
	};
}



