import React from 'react';
import { Box, Button, Heading, Nav } from 'grommet';

export default function AppBar() {
  return (
    <Box
      tag="header"
      direction="row"
      align="center"
      justify="between"
      background="red"
      pad={{ left: 'medium', right: 'small', vertical: 'small' }}
      elevation="medium"
      style={{ zIndex: 1 }}
    >
      <Heading level="2" margin="none">Pokemon Hex Generator</Heading>
      <Box flex direction="row" align="center" justify="end">
        <Nav>
          <Button
            hoverIndicator
            plain
            href="https://paypal.me/pleebz"
          >
            Donate
          </Button>
        </Nav>
      </Box>
    </Box>
  );
}
