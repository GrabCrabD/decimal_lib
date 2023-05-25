#!/bin/bash
rm -rf ~/Library/Containers/com.docker.docker
mkdir -p ~/goinfre/Docker/Data
ln -s ~/goinfre/Docker ~/Library/Containers/com.docker.docker
​
rm -rf ~/Library/Caches
rm -rf ~/Library/Application\ Support/Code/Cache
rm -rf ~/Library/Application\ Support/Code/CachedData
rm -rf ~/Library/Application\ Support/Code/CachedExtension
rm -rf ~/Library/Application\ Support/Code/CachedExtensions
rm -rf ~/Library/Application\ Support/Code/CachedExtensionVSIXs
rm -rf ~/Library/Application\ Support/Code/Code\ Cache
rm -rf ~/Library/Application\ Support/Slack/Cache
rm -rf ~/Library/Application\ Support/Slack/Code\ Cache
rm -rf ~/Library/Application\ Support/Slack/Service\ Worker/CacheStorage
rm -rf ~/Library/Application\ Support/Spotify/PersistentCache
rm -rf ~/Library/Application\ Support/Code/User/workspaceStorage/*
rm -rf ~/Library/Application\ Support/Code/User/workspaceStorage
rm -rf ~/Library/Containers/com.apple.Safari
rm -rf ~/Library/Containers/com.apple.Safari/Data/Library/Caches/
yes Y | rm -rf ~/Library/Application\ Support/Google/Chrome/Default/Service\ Worker/CacheStorage/*
​
find ~/ -name ".DS_Store" -print -delete 2> /dev/null
find ~/ -name "**.42_cache_bak**" -print -delete 2> /dev/null
rm -rf ~/.zcompdump*
rm -rf ~/Library/Caches/*
rm -rf ~/Library/42_cache
rm -rf ~/Library/Caches/*
rm -rf ~/Library/42_cache
rm -rf ~/Library/Developer/CoreSimulator/Caches/
rm -rf ~/Library/Developer/CoreSimulator/Devices/
rm -rf ~/Library/Logs/
rm -rf ~/Library/Google/GoogleSoftwareUpdate/
rm -rf ~/Library/Application\ Support/Slack/logs
rm -rf ~/Library/Application\ Support/zoom.us/AutoUpdater
rm -rf ~/Library/Application\ Support/Google/Chrome/BrowserMetrics/.
rm -rf ~/Library/Application\ Support/Google/Chrome/BrowserMetrics-spare.pma
rm -rf ~/Library/Application\ Support/Google/Chrome/GrShaderCache/GPUCache/
rm -rf ~/Library/Application\ Support/Google/Chrome/Default/Local\ Extension Settings/cjpalhdlnbpafiamejdnhcphjbkeiagm/lost
rm -rf ~/Library/Application\ Support/Google/Chrome/Default/Service\ Worker/CacheStorage/
rm -rf  ~/Library/Application\ Support/Google/Chrome/Default/Service\ Worker/ScriptCache/
rm -rf ~/Library/Application\ Support/Google/Chrome/ShaderCache/GPUCache/
rm -rf ~/Library/Application\ Support/Code/logs/
rm -rf ~/Library/Application\ Support/Code/Service\ Worker/CacheStorage/
rm -rf ~/Library/Application\ Support/Code/Service\ Worker/ScriptCache/
rm -rf ~/.Trash/
rm -rf ~/Library/Application Support/Google/Chrome/OptimizationGuidePredictionModels
rm -rf ./OptimizationGuidePredictionModels
​
#brew cleanup && echo "clean complete"
echo "clean complete"
