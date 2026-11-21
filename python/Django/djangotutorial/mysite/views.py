from django.http import JsonResponse


def health(request):
    """Liveness probe endpoint, e.g. for uptime monitors or a load balancer."""
    return JsonResponse({"status": "ok"})
