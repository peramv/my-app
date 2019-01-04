#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_invalid_entity_type_split_comm : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_invalid_entity_type_split_comm() { }
		~CIFast_IFast_ifastdbrkr_err_invalid_entity_type_split_comm() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_ENTITY_TYPE_SPLIT_COMM")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Entity Type for Split Commission.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiger Objekttyp für geteilte Agenturvergütung")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Tipo de entidad no válida para comisión dividida")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type d'entité invalide pour le partage de commission")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig eenheidstype voor gedeelde commissie")); }

        // Actions
	};
}



