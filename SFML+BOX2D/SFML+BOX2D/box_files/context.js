!function(e,t,n){function r(t){var r=e[t];return e[t]=n,r}function a(e,t){return r("yandex_"+(t?t+"_":"")+e)}function o(e,t,n){for(var r=0;r<t.length;r++)e[t[r]]=a(t[r],n)}var c=e.Ya=e.Ya||{};if(!c.loaderVer&&(c.loaderVer=1132),!c.codeVer){var i=Math.random();c.codeVer=.05>=i?1132:1130}if(c.confirmVer=1071,c.matchVer=1103,!c.Context){c.Context={_callbacks:[],_asyncIdCounter:0,_asyncModeOn:!1,initTime:Number(new Date),CONFIRM_BY_CLICK:Math.random()<.1},c.Direct={insertInto:function(e,t,n,r){c.Context._asyncModeOn||(c.Context._asyncModeOn=!0),c.Context.AdvManager?c.Context.AdvManager.renderDirect(e,t,n,r):c.Context._callbacks.push(function(){c.Context.AdvManager.renderDirect(e,t,n,r)})}}}for(var _=["yandex_context_callbacks","yandexContextAsyncCallbacks"],l=0;l<_.length;l++){var s=r(_[l]);if(s){c.Context._asyncModeOn||(c.Context._asyncModeOn=!0);for(var d=0;d<s.length;d++)c.Context._callbacks.push(s[d])}}if(e.yandexContextSyncCallbacks)for(var s=r("yandexContextSyncCallbacks"),l=0;l<s.length;l++)c.Context._callbacks.push(s[l]);var x=["ad_format","site_bg_color","font_size","font_family","stat_id","no_sitelinks","search_text","search_page_number","lang"],C=["type","border_type","bg_color","border_radius","border_color","header_bg_color","title_color","text_color","url_color","hover_color","sitelinks_color","links_underline","limit","place","favicon","title_font_size","grab","c11n","geo_lat","geo_long","width","height"];if(e.yandex_ad_format){var f={};o(f,x),o(f,C,f.ad_format);var y=f.place;y&&t.getElementById(y)||(y="Ya_sync_"+c.Context._asyncIdCounter++,t.write('<div id="'+y+'"></div>'));var v=a("partner_id");c.Context._callbacks.push(function(){c.Context.AdvManager.renderDirect(v,y,f)})}var u="an.yandex.ru/resource/context_static_r"+c.codeVer+".js";if(t.getElementById(u)&&c.Context._init)return void c.Context._init();var g="https://"+u;if(c.Context._asyncModeOn){var h=t.createElement("script"),b=t.getElementsByTagName("script")[0];h.id=u,h.src=g,b.parentNode.insertBefore(h,b)}else t.write('<script type="text/javascript" src="'+g+'" id="'+u+'"></script>')}(this,this.document);