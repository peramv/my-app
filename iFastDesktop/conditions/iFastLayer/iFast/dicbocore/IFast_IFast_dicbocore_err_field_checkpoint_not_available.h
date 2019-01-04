#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicbocore_err_field_checkpoint_not_available : public CConditionObject
	{
	public:
		CIFast_IFast_dicbocore_err_field_checkpoint_not_available() { }
		~CIFast_IFast_dicbocore_err_field_checkpoint_not_available() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FIELD_CHECKPOINT_NOT_AVAILABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This account has purchases and/or PACs stopped. Unable to set up allocation.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("This account has purchases and/or PACs stopped. Unable to set up allocation.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bei diesem Konto sind Käufe und/oder PACs gestoppt. Zuweisung kann nicht erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Esta cuenta ha interrumpido compras y/o PACs. Imposible configurar asignación.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Certains achats ou PAC de ce compte sont arrêtés. Impossible de régler la répartition.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Voor dit account zijn aankopen en/of VGC's beëindigd. Allocatie kon niet worden ingesteld")); }

        // Actions
	};
}



