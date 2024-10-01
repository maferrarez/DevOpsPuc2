from src.main import *
from unittest_mock import patch

def test_buscarAtivos():
    assert buscarAtivos() > 0

def test_cadastroFidelidade():
    assert cadastroFidelidade() == int

def test_verificaCadastroCPF():
    with patch('random.randint', return_value=12345678910):
        result = verificaCadastroCPF()
    assert result == {"teste": True, "resp": 12345678910}

def test_buscaConfirmaCadastro():
    assert buscaConfirmaCadastro() != 0

