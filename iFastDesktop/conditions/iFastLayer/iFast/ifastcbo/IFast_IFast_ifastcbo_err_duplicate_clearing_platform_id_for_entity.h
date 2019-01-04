#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_duplicate_clearing_platform_id_for_entity : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_duplicate_clearing_platform_id_for_entity() { }
		~CIFast_IFast_ifastcbo_err_duplicate_clearing_platform_id_for_entity() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DUPLICATE_CLEARING_PLATFORM_ID_FOR_ENTITY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("A Clearing Platform Entity with This Identification Value already exists in the system.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une entité de plateforme de compensation avec cette valeur d'identification existe déjà dans le système.")); }

        // Actions
	};
}



