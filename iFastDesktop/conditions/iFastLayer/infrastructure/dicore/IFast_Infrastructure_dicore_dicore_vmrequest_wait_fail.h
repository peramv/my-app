#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dicore_dicore_vmrequest_wait_fail : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dicore_dicore_vmrequest_wait_fail() { }
		~CIFast_Infrastructure_dicore_dicore_vmrequest_wait_fail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_VMREQUEST_WAIT_FAIL")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("VmRequest EventSemaphore timed out waiting for host. Lower-level error: %ERROR%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("VmRequest EventSemaphore timed out waiting for host. Lower-level error: %ERROR%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("VmRequest Ereignis-Semaphor –Zeitüberschreitung bei Warten auf Host. Fehler auf niedriger Ebene: %ERROR%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Finalizó el intervalo de espera de VmRequest EventSemaphore esperando al host. Error de nivel inferior: %ERROR%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le sémaphore de l'événement de la demande de gestionnaire de l'affichage a expiré lors de l'attente de l'hôte. Erreur de niveau inférieur : %ERROR%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("VmRequest EventSemaphore verlopen tijdens het wachten op de host.  Fout op lager niveau: %ERROR%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Retry view.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Retry view.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Versuchen Sie erneut, die Ansicht anzuzeigen.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Vuelva a intentar view.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Réessayez l'affichage.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Probeer de view opnieuw")); }
	};
}



