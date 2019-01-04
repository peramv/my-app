#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_delete_resp_entity : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_delete_resp_entity() { }
		~CIFast_IFast_ifastcbo_err_delete_resp_entity() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DELETE_RESP_ENTITY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Reason Code must be updated before deletion.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Reason Code must be updated before deletion.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Begründungs-Code muss vor dem Löschen aktualisiert werden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código de motivo debe actualizarse antes de la eliminación.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de raison doit être mis à jour avant la suppression.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Redencode moet worden bijgewerkt voor de wisbewerking")); }

        // Actions
	};
}



