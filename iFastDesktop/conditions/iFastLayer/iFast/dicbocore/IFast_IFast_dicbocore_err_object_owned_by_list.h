#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicbocore_err_object_owned_by_list : public CConditionObject
	{
	public:
		CIFast_IFast_dicbocore_err_object_owned_by_list() { }
		~CIFast_IFast_dicbocore_err_object_owned_by_list() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_OBJECT_OWNED_BY_LIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This account has redemptions and/or SWPs stopped. Unable to set up allocation.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("This account has redemptions and/or SWPs stopped. Unable to set up allocation.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bei diesem Konto sind Tilgungen und/oder SWPs gestoppt. Zuweisung kann nicht erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Esta cuenta ha interrumpido rescates y/o SWPs. Imposible configurar asignación.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Certains rachats ou PRP de ce compte sont arrêtés. Impossible de régler la répartition.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Voor dit account zijn aflossingen en/of SWP's beëindigd. Allocatie kon niet worden ingesteld")); }

        // Actions
	};
}



