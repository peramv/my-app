#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_entity_whereuse_already_exist : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_entity_whereuse_already_exist() { }
		~CIFast_IFast_ifastdbrkr_err_entity_whereuse_already_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ENTITY_WHEREUSE_ALREADY_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to add a record, Entity Where Use already exists")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Unable to add a record, Entity Where Use already exists")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible d'ajouter un enregistrement, les contrats associés de l'entité existent déjà.")); }

        // Actions
	};
}



