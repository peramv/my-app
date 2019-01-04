#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_status_changed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_status_changed() { }
		~CIFast_IFast_ifastcbo_err_status_changed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_STATUS_CHANGED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("An existing pending trade may fail if the status is changed.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Une operation en cours existante peut echouer si le statut est modifie.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ein existierender schwebender Handel könnte fehlschlagen, wenn der Status geändert wird.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Una operación pendiente existente puede fallar si se cambia el estado.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une transaction en suspens existante peut échouer si le statut est changé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Een bestaande in behandeling zijnde transactie kan mislukken als de status wordt gewijzigd")); }

        // Actions
	};
}



