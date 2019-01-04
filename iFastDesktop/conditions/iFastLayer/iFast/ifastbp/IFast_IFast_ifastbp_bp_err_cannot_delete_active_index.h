#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastbp_bp_err_cannot_delete_active_index : public CConditionObject
	{
	public:
		CIFast_IFast_ifastbp_bp_err_cannot_delete_active_index() { }
		~CIFast_IFast_ifastbp_bp_err_cannot_delete_active_index() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_ERR_CANNOT_DELETE_ACTIVE_INDEX")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastbp")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Active Index cannot be deleted.  Change the End Date to Current Day to Stop Index.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Aktiver Index darf nicht gelöscht werden.  Ändern Sie das Enddatum auf Heutiger Tag im Stopp-Index.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El índice activo no puede eliminarse.  Cambie la fecha de terminación al día actual para detener el índice.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'indexation active ne peut être supprimé. Changez la date de fin pour la date actuelle afin d'arrêter l'indexation.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Actieve index kan niet worden gewist.  Wijzig de einddatum in huidige dag om de index te beëindigen")); }

        // Actions
	};
}



