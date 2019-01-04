#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_entity_type_empty : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_entity_type_empty() { }
		~CIFast_IFast_ifastcbo_err_entity_type_empty() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ENTITY_TYPE_EMPTY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Entity Type should not be empty.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Objektart sollte nicht leer sein. Bitte wählen Sie eine Objektart aus der Liste.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo de entidad no debe estar vacío. Por favor seleccione un tipo de entidad de la lista.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ Type d'entité devrait être rempli.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Eenheidstype mag niet leeg zijn. Selecteer een eenheidstype uit de lijst")); }

        // Actions
	};
}



