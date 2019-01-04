#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastgui_gui_wrapup_err_must_enter_stat : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastgui_gui_wrapup_err_must_enter_stat() { }
		~CIFast_Infrastructure_ifastgui_gui_wrapup_err_must_enter_stat() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_WRAPUP_ERR_MUST_ENTER_STAT")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Potential duplicate transaction.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Potential duplicate transaction.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Möglicherweise doppelte Transaktion.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Transacción repetida potencial.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Copie potentielle de transaction")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Mogelijke dubbele transactie")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify amount and review pending trades before continuing, or cancel trade.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify amount and review pending trades before continuing, or cancel trade.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie den Betrag und überprüfen Sie den noch ausstehenden Handel, bevor Sie fortfahren, oder brechen Sie den Handel ab.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify amount and review pending trades before continuing, or cancel trade.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le montant et révisez les transactions en suspens avant de continuer, ou annulez la transaction.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het bedrag en herzie de in behandeling zijnde transacties voordat u doorgaat, of annuleer de handel")); }
	};
}



