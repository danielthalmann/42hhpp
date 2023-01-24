#include "Response.hpp"

hhpp::Response::Response() {}

hhpp::Response::~Response() {}

void hhpp::Response::setStatus(int status) {
	_status = status;
}

std::string hhpp::Response::getBlob() {
	return(NULL);
}

//request
//GET /danielthalmann/42hhpp/blob/sandbox/doc/sandbox/srv.cpp HTTP/2
//*Host: github.com
//User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:107.0) Gecko/20100101 Firefox/107.0
//*Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8
//Accept-Language: fr,fr-FR;q=0.8,en-US;q=0.5,en;q=0.3
//Accept-Encoding: gzip, deflate, br
//Connection: keep-alive
//Cookie: _octo=GH1.1.2064806961.1674550506; logged_in=no; _gh_sess=%2BhcNf6dQEwOogb1jXOCaqcJey2DVm0HpR2r8jGYOYnVybCRymPTtYSmQt5GJ2QRKsy%2F8sD2S4lBgT%2FADeWRDBpnUsMLbMs5f5ofQZmtGatyQpdtBXxaIQA8FNJqtom5hALpmUf5wT5KXKhqM0lMOcSiAyPNybstMH8HSCBbWsleshfEWcpV5ImG4INbkxN681LFuBNdlwbo1huO7q6DDrRfir2sebVK%2BFMmT6IOj2yiZ5HTjVOKpE%2BQ%2FM3HLv0ZGw0nXkt%2BD1oAYAekphA6wBw%3D%3D--wNmI871UEWIl7swR--4yXWSLCwEgoL1ZlUHzclyg%3D%3D; preferred_color_mode=dark; tz=Europe%2FZurich
//Upgrade-Insecure-Requests: 1
//Sec-Fetch-Dest: document
//Sec-Fetch-Mode: navigate
//Sec-Fetch-Site: none
//Sec-Fetch-User: ?1
//TE: trailers

//response
//HTTP/2 200 OK
//server: GitHub.com
//date: Tue, 24 Jan 2023 16:37:59 GMT
//content-type: text/html; charset=utf-8
//vary: X-PJAX, X-PJAX-Container, Turbo-Visit, Turbo-Frame, Accept-Encoding, Accept, X-Requested-With
//etag: W/"2e4f2fa8cc6c3acc810571afc6c9c47c"
//cache-control: max-age=0, private, must-revalidate
//strict-transport-security: max-age=31536000; includeSubdomains; preload
//x-frame-options: deny
//x-content-type-options: nosniff
//x-xss-protection: 0
//referrer-policy: no-referrer-when-downgrade
//content-security-policy: default-src 'none'; base-uri 'self'; block-all-mixed-content; child-src github.com/assets-cdn/worker/ gist.github.com/assets-cdn/worker/; connect-src 'self' uploads.github.com objects-origin.githubusercontent.com www.githubstatus.com collector.github.com raw.githubusercontent.com api.github.com github-cloud.s3.amazonaws.com github-production-repository-file-5c1aeb.s3.amazonaws.com github-production-upload-manifest-file-7fdce7.s3.amazonaws.com github-production-user-asset-6210df.s3.amazonaws.com cdn.optimizely.com logx.optimizely.com/v1/events *.actions.githubusercontent.com wss://*.actions.githubusercontent.com online.visualstudio.com/api/v1/locations github-production-repository-image-32fea6.s3.amazonaws.com github-production-release-asset-2e65be.s3.amazonaws.com insights.github.com wss://alive.github.com; font-src github.githubassets.com; form-action 'self' github.com gist.github.com objects-origin.githubusercontent.com; frame-ancestors 'none'; frame-src viewscreen.githubusercontent.com notebooks.githubusercontent.com; img-src 'self' data: github.githubassets.com media.githubusercontent.com camo.githubusercontent.com identicons.github.com avatars.githubusercontent.com github-cloud.s3.amazonaws.com objects.githubusercontent.com objects-origin.githubusercontent.com secured-user-images.githubusercontent.com/ opengraph.githubassets.com github-production-user-asset-6210df.s3.amazonaws.com customer-stories-feed.github.com spotlights-feed.github.com *.githubusercontent.com; manifest-src 'self'; media-src github.com user-images.githubusercontent.com/ secured-user-images.githubusercontent.com/; script-src github.githubassets.com; style-src 'unsafe-inline' github.githubassets.com; worker-src github.com/assets-cdn/worker/ gist.github.com/assets-cdn/worker/
//content-encoding: gzip
//accept-ranges: bytes
//x-github-request-id: 1352:7B51:FB51B9:101DAFD:63D008EC
//X-Firefox-Spdy: h2

void hhpp::Response::setResponse(Request& request) {
	request.getHttpVersion();
}

hhpp::Header& hhpp::Response::getHeaders() {
	return(_header);
}
