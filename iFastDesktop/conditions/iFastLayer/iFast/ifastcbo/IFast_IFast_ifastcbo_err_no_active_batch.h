#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_no_active_batch : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_no_active_batch() { }
		~CIFast_IFast_ifastcbo_err_no_active_batch() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_ACTIVE_BATCH")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Users batch is not active.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Aucun lot actif n'est disponible.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Benutzer hat keinen aktiven Batch.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El usuario no tiene un lote activo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le lot d'utilisateurs est inactif.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is geen actieve batch beschikbaar")); }

        // Actions
	};
}



