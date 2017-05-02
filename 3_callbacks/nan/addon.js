const mustache = require('./build/Release/binding.node')
const fs = require('fs')

fs.readFile('bye.jpg', renderMustache);

function renderMustache(err, buffer) {
  if (err) throw err;
  console.log(buffer)
  mustache.renderMustache(buffer, mustacheRendered)
}

function mustacheRendered(data) {
  console.log(data)
  console.log('success!')
}
