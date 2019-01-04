#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_split_commission_record_already_exists_for_this_entity : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_split_commission_record_already_exists_for_this_entity() { }
		~CIFast_IFast_ifastdbrkr_err_split_commission_record_already_exists_for_this_entity() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SPLIT_COMMISSION_RECORD_ALREADY_EXISTS_FOR_THIS_ENTITY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Split Commission record already exists for this entity.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Eintrag für verteilte Agenturvergütung existiert bereits für dieses Objekt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Ya existe un registro de comisión dividida para esta entidad")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement de partage de commission existe déjà pour cette entité.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Record gedeelde commissie bestaat al voor deze eenheid")); }

        // Actions
	};
}



