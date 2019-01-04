#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_adding_transfer_is_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_adding_transfer_is_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_adding_transfer_is_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ADDING_TRANSFER_IS_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Adding a Transfer/Exchange is not allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Hinzufügen eines Transfers / einer Devise ist nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite agregar una transferencia o traspaso.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'ajout d'un transfert/échange n'est pas autorisé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Toevoegen van overdracht/ruil is niet toegestaan")); }

        // Actions
	};
}



