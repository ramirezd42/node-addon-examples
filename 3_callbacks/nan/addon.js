const mustache = require('./build/Release/binding.node')
const fs = require('fs')

fs.readFile('bye.jpg', renderMustache);

function renderMustache(err, buffer) {
  if (err) throw err;
  mustache.renderMustache(buffer, mustacheRendered)
}

function mustacheRendered(data) {
  console.log('success!')
}
